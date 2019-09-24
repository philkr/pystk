cmake_minimum_required(VERSION 3.0)

if(POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif()

# root CMakeLists for the SuperTuxKart project
project(SuperTuxKart VERSION 1.0)
set(PROJECT_VERSION "git")
add_definitions( -DSUPERTUXKART_VERSION="${PROJECT_VERSION}" )

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
include(CMakeDependentOption)

include(BuildTypeSTKRelease)
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to STKRelease")
    set(CMAKE_BUILD_TYPE "STKRelease")
endif()

option(SERVER_ONLY "Create a server only (i.e. no graphics or sound)" OFF)
option(CHECK_ASSETS "Check if assets are installed in ../stk-assets" ON)
option(USE_SYSTEM_ANGELSCRIPT "Use system angelscript instead of built-in angelscript. If you enable this option, make sure to use a compatible version." OFF)

set(STK_SOURCE_DIR "src")
set(STK_DATA_DIR "${PROJECT_SOURCE_DIR}/data")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

# Define install paths
set(STK_INSTALL_BINARY_DIR "bin" CACHE
    STRING "Install executable to this directory, absolute or relative to CMAKE_INSTALL_PREFIX")
set(STK_INSTALL_DATA_DIR "share/supertuxkart" CACHE
    STRING "Install data folder to this directory, absolute or relative to CMAKE_INSTALL_PREFIX")

# Define dependencies path
if(MSVC)
    set(DEPENDENCIES "dependencies-vs")
elseif(MINGW)
    set(DEPENDENCIES "dependencies-mingw")
else()
    set(DEPENDENCIES "dependencies")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(DEPENDENCIES "${DEPENDENCIES}-64bit")
endif()

if(WIN32 AND FALSE)
    if(NOT IS_DIRECTORY "${PROJECT_SOURCE_DIR}/${DEPENDENCIES}")
        set(DEPENDENCIES "dependencies")
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(DEPENDENCIES "${DEPENDENCIES}-64bit")
        endif()
    endif()

    if(NOT IS_DIRECTORY "${PROJECT_SOURCE_DIR}/${DEPENDENCIES}")
        message(FATAL_ERROR "Dependencies directory not found.")
    endif()

# These variables enable MSVC to find libraries located in "dependencies"
    set(ENV{PATH} "$ENV{PATH};${PROJECT_SOURCE_DIR}/${DEPENDENCIES}/include")
    set(ENV{LIB} ${PROJECT_SOURCE_DIR}/${DEPENDENCIES}/lib)
    set(ENV{OPENALDIR} ${PROJECT_SOURCE_DIR}/${DEPENDENCIES})
    add_definitions(-D_IRR_STATIC_LIB_)
    add_definitions(-DNO_IRR_COMPILE_WITH_X11_)
    include_directories(${PROJECT_SOURCE_DIR}/${DEPENDENCIES}/include)
endif()

if(USE_GLES2)
    add_definitions(-DUSE_GLES2)
    add_definitions(-D_IRR_COMPILE_WITH_OGLES2_ -DNO_IRR_COMPILE_WITH_OPENGL_)
endif()

if(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)

    if(NOT PKGCONFIG_FOUND)
        message(FATAL_ERROR "Pkg-config not found.")
    endif()
endif()

# PyBind11
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/pybind11")
include_directories("${PYBIND11_INCLUDE_DIR}")

# Build the Bullet physics library
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/bullet")
include_directories("${PROJECT_SOURCE_DIR}/lib/bullet/src")

# Build FreeType
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/freetype")
include_directories(${FREETYPE_INCLUDES} "${PROJECT_SOURCE_DIR}/lib/freetype/include")

add_subdirectory("${PROJECT_SOURCE_DIR}/lib/glew")
include_directories("${PROJECT_SOURCE_DIR}/lib/glew/include")
set(GLEW_LIBRARIES "glew")

add_subdirectory("${PROJECT_SOURCE_DIR}/lib/zlib")
include_directories("${PROJECT_SOURCE_DIR}/lib/zlib")

set(ZLIB_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/zlib" "${PROJECT_BINARY_DIR}/lib/zlib/")
set(ZLIB_LIBRARY zlibstatic)

if (NOT SERVER_ONLY)
	set(SKIP_INSTALL_ALL TRUE)
	set(PNG_STATIC TRUE CACHE BOOL "Build static lib")
	set(PNG_TESTS FALSE CACHE BOOL "Build libpng tests")
	set(PNG_SHARED FALSE CACHE BOOL "Build shared lib")
	add_subdirectory("${PROJECT_SOURCE_DIR}/lib/libpng")
	include_directories("${PROJECT_SOURCE_DIR}/lib/libpng")

	set(PNG_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/libpng/")
	set(PNG_LIBRARY png_static)
	
	add_subdirectory("${PROJECT_SOURCE_DIR}/lib/jpeglib")
	include_directories("${PROJECT_SOURCE_DIR}/lib/jpeglib")
	set(JPEG_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/jpeglib/")
	set(JPEG_LIBRARY jpeglib)
	
    add_subdirectory("${PROJECT_SOURCE_DIR}/lib/graphics_utils")
    include_directories("${PROJECT_SOURCE_DIR}/lib/graphics_utils")

	add_subdirectory("${PROJECT_SOURCE_DIR}/lib/libsquish")
	include_directories("${PROJECT_SOURCE_DIR}/lib/libsquish")
	SET(SQUISH_LIBRARY squish)
endif()

# Build the irrlicht library
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/irrlicht")
include_directories("${PROJECT_SOURCE_DIR}/lib/irrlicht/include")

# Set include paths
include_directories(${STK_SOURCE_DIR})

if(APPLE AND NOT IOS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -arch x86_64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch x86_64 -F/Library/Frameworks")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")   # Enable multi-processor compilation (faster)
endif()

# Angel script
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/angelscript/projects/cmake")
include_directories("${PROJECT_SOURCE_DIR}/lib/angelscript/include")
set(Angelscript_LIBRARIES angelscript)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

if(WIN32)
    # By default windows.h has macros defined for min and max that screw up everything
    add_definitions(-DNOMINMAX)

    # And shut up about unsafe stuff
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)

    # Avoid timespec structure redeclaration on Visual Studio 2015
    if (NOT (MSVC_VERSION LESS 1900))
        add_definitions(-DHAVE_STRUCT_TIMESPEC)
    endif()
endif()


if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG -fno-default-inline)
else()
    add_definitions(-DNDEBUG)
endif()

# Provides list of source and header files (STK_SOURCES and STK_HEADERS)
include(sources.cmake)

# Generate source groups useful for MSVC project explorer
include(cmake/SourceGroupFunctions.cmake)
source_group_hierarchy(STK_SOURCES STK_HEADERS)
LIST(REMOVE_ITEM STK_SOURCES "src/main.cpp")

if(APPLE)
    add_library(stk ${STK_SOURCES} ${STK_RESOURCES} ${STK_HEADERS})

    # build the executable and create an app bundle
#    add_executable(supertuxkart MACOSX_BUNDLE ${STK_SOURCES})

#    find_library(IOKIT_LIBRARY IOKit)
#    find_library(COCOA_LIBRARY Cocoa)

#    target_link_libraries(supertuxkart
#         ${IOKIT_LIBRARY}
#         ${COCOA_LIBRARY})
else()
#    if(MSVC)
#        set(PTHREAD_NAMES pthreadVC2)
#    elseif(MINGW)
#        set(PTHREAD_NAMES "winpthread-1" "libwinpthread-1" "pthreadGC2")
#    endif()
#    find_library(PTHREAD_LIBRARY NAMES pthread ${PTHREAD_NAMES} PATHS ${PROJECT_SOURCE_DIR}/${DEPENDENCIES}/lib)
#    mark_as_advanced(PTHREAD_LIBRARY)

    # Set data dir (absolute or relative to CMAKE_INSTALL_PREFIX)
    if(NOT STK_INSTALL_DATA_DIR_ABSOLUTE)
        get_filename_component(STK_INSTALL_DATA_DIR_ABSOLUTE ${STK_INSTALL_DATA_DIR} ABSOLUTE)
        if(${STK_INSTALL_DATA_DIR_ABSOLUTE} STREQUAL ${STK_INSTALL_DATA_DIR})
            add_definitions(-DSUPERTUXKART_DATADIR=\"${STK_INSTALL_DATA_DIR_ABSOLUTE}\")
        else()
            add_definitions(-DSUPERTUXKART_DATADIR=\"${CMAKE_INSTALL_PREFIX}/${STK_INSTALL_DATA_DIR}\")
        endif()
    else()
        add_definitions(-DSUPERTUXKART_DATADIR=\"${STK_INSTALL_DATA_DIR_ABSOLUTE}\")
    endif()

    # Build the final executable

    add_library(stk ${STK_SOURCES} ${STK_RESOURCES} ${STK_HEADERS})
#    target_link_libraries(stk ${PTHREAD_LIBRARY})
endif()

# Common library dependencies
target_link_libraries(stk
    bulletdynamics
    bulletcollision
    bulletmath
#     ${ENET_LIBRARIES}
    stkirrlicht
    ${Angelscript_LIBRARIES}
    )

if(NOT SERVER_ONLY)
	target_link_libraries(stk ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES})

    target_link_libraries(stk
       ${SQUISH_LIBRARY}
       freetype
       ${JPEG_LIBRARIES}
        graphics_utils)

endif()

add_executable(supertuxkart src/main.cpp )
target_link_libraries(supertuxkart stk)
pybind11_add_module(pystk pystk_cpp/binding.cpp pystk_cpp/pystk.cpp pystk_cpp/util.cpp pystk_cpp/state.cpp pystk_cpp/pickle.cpp)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(pystk PUBLIC RENDERDOC)
endif()
target_link_libraries(pystk PRIVATE pybind11::module stk)
set_target_properties(pystk PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}" SUFFIX "${PYTHON_MODULE_EXTENSION}")
add_custom_command(TARGET pystk POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:pystk> ${PROJECT_SOURCE_DIR}/ )


if(APPLE)
   target_link_libraries(pystk PRIVATE "-framework CoreFoundation -framework Cocoa")
   target_link_libraries(supertuxkart "-framework CoreFoundation -framework Cocoa")
endif()

# ==== Checking if data folder exists ====
if(NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data)
  message( FATAL_ERROR "${CMAKE_CURRENT_SOURCE_DIR}/data folder doesn't exist" )
endif()

# ==== Checking if stk-assets folder exists ====
if(CHECK_ASSETS)
  if((IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/karts) AND
       (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/library) AND
       (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/music) AND
       (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/sfx) AND
       (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/textures) AND
       (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data/tracks))
    message(STATUS "Assets found in data directory")
  elseif(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/stk-assets)
    set(STK_ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/stk-assets/)
    message(STATUS "Assets found")
  elseif(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../stk-assets)
    set(STK_ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../stk-assets/)
    message(STATUS "Assets found")
  elseif(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../supertuxkart-assets)
    set(STK_ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../supertuxkart-assets/)
    message(STATUS "Assets found")
  else()
    set (CUR_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    get_filename_component(PARENT_DIR ${CUR_DIR} PATH)
    message( FATAL_ERROR "${PARENT_DIR}/stk-assets folder doesn't exist. "
      "Please download the stk-assets, or disable this test with -DCHECK_ASSETS=off." )
  endif()
endif()

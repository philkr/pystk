cmake_minimum_required(VERSION 3.0)

if(POLICY CMP0072)
  cmake_policy(SET CMP0072 NEW)
endif()
if(POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif()
if(NOT PYSTK_VERSION)
    set(PYSTK_VERSION "0.0.0")
endif()

# root CMakeLists for the SuperTuxKart project
project(SuperTuxKart VERSION "${PYSTK_VERSION}")
set(PROJECT_VERSION "${PYSTK_VERSION}")
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

option(NO_GRAPHICS "Turn off graphics" OFF)
option(USE_SYSTEM_ANGELSCRIPT "Use system angelscript instead of built-in angelscript. If you enable this option, make sure to use a compatible version." OFF)

set(STK_SOURCE_DIR "src")
set(STK_DATA_DIR "${PROJECT_SOURCE_DIR}/data")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

# Define install paths
set(STK_INSTALL_BINARY_DIR "bin" CACHE
    STRING "Install executable to this directory, absolute or relative to CMAKE_INSTALL_PREFIX")
set(STK_INSTALL_DATA_DIR "share/supertuxkart" CACHE
   STRING "Install data folder to this directory, absolute or relative to CMAKE_INSTALL_PREFIX")

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(DEPENDENCIES "${DEPENDENCIES}-64bit")
endif()

#if(UNIX AND NOT APPLE)
#    find_package(PkgConfig REQUIRED)
#
#    if(NOT PKGCONFIG_FOUND)
#        message(FATAL_ERROR "Pkg-config not found.")
#    endif()
#endif()

# PyBind11
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/pybind11")
include_directories("${PYBIND11_INCLUDE_DIR}")

# Build the Bullet physics library
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/bullet")
include_directories("${PROJECT_SOURCE_DIR}/lib/bullet/src")

# Build FreeType
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/freetype")
include_directories(${FREETYPE_INCLUDES} "${PROJECT_SOURCE_DIR}/lib/freetype/include")


add_subdirectory("${PROJECT_SOURCE_DIR}/lib/zlib")
include_directories("${PROJECT_SOURCE_DIR}/lib/zlib")

set(ZLIB_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/zlib" "${PROJECT_BINARY_DIR}/lib/zlib/")
set(ZLIB_LIBRARY zlibstatic)

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

# Build the irrlicht library
if(NO_GRAPHICS)
    set(IRR_NO_GRAPHICS TRUE)
endif()
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/irrlicht")
include_directories("${PROJECT_SOURCE_DIR}/lib/irrlicht/include")

if (IRR_NO_GRAPHICS)
    add_definitions(-DSERVER_ONLY)
else()
    add_definitions(-DGLEW_NO_GLU)
    add_subdirectory("${PROJECT_SOURCE_DIR}/lib/glew")
    include_directories("${PROJECT_SOURCE_DIR}/lib/glew/include")
    set(GLEW_LIBRARIES "glew")

    add_subdirectory("${PROJECT_SOURCE_DIR}/lib/graphics_utils")
    include_directories("${PROJECT_SOURCE_DIR}/lib/graphics_utils")

	add_subdirectory("${PROJECT_SOURCE_DIR}/lib/libsquish")
	include_directories("${PROJECT_SOURCE_DIR}/lib/libsquish")
	SET(SQUISH_LIBRARY squish)

    # OpenGL
    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})
endif()

# Set include paths
include_directories(${STK_SOURCE_DIR})

if(APPLE AND NOT IOS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -F/Library/Frameworks")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")   # Enable multi-processor compilation (faster)
endif()

# Angel script
add_subdirectory("${PROJECT_SOURCE_DIR}/lib/angelscript/projects/cmake")
include_directories("${PROJECT_SOURCE_DIR}/lib/angelscript/include")
set(Angelscript_LIBRARIES angelscript)

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
    add_definitions(-DDEBUG)
    if(NOT WIN32)
        add_definitions( -fno-default-inline)
    endif()
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
else()
    add_library(stk ${STK_SOURCES} ${STK_RESOURCES} ${STK_HEADERS})
endif()

# Common library dependencies
target_link_libraries(stk
    bulletdynamics
    bulletcollision
    bulletmath
    stkirrlicht
    ${Angelscript_LIBRARIES}
    )

if(NOT IRR_NO_GRAPHICS)
	target_link_libraries(stk ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES})

    target_link_libraries(stk
       ${SQUISH_LIBRARY}
       freetype
       ${JPEG_LIBRARIES}
        graphics_utils)

endif()

pybind11_add_module(pystk pystk_cpp/binding.cpp pystk_cpp/buffer.cpp pystk_cpp/pystk.cpp pystk_cpp/util.cpp pystk_cpp/state.cpp pystk_cpp/pickle.cpp)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(pystk PUBLIC RENDERDOC)
endif()
target_link_libraries(pystk PRIVATE pybind11::module stk)
set_target_properties(pystk PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}" SUFFIX "${PYTHON_MODULE_EXTENSION}")
add_custom_command(TARGET pystk POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:pystk> ${PROJECT_SOURCE_DIR}/ )


if(APPLE)
   target_link_libraries(pystk PRIVATE "-framework CoreFoundation -framework Cocoa")
endif()

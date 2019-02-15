cmake_minimum_required (VERSION 3.0)

project (GLproxy VERSION 1.3.2 LANGUAGES C)
set (GLPROXY_TARGET_NAME glproxy)
set (TARGET_VER 1.3.2)
set (TARGET_ABI_VER 0)

include (GNUInstallDirs)
include (CMakeDependentOption)

set (COMPILER_ID_MSVC MSVC)
set (COMPILER_ID_GCC GNU)
set (COMPILER_ID_CLANG Clang)

if ((CMAKE_C_COMPILER_ID STREQUAL COMPILER_ID_GCC) OR (CMAKE_C_COMPILER_ID STREQUAL COMPILER_ID_CLANG))
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
elseif (NOT CMAKE_VERSION VERSION_LESS "3.1")
    set (CMAKE_C_STANDARD_REQUIRED TRUE)
    set (CMAKE_C_STANDARD "99")
endif ()

if ((CMAKE_C_COMPILER_ID STREQUAL COMPILER_ID_GCC) OR (CMAKE_C_COMPILER_ID STREQUAL COMPILER_ID_CLANG))
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-strict-aliasing -Wall -Wextra")
elseif (CMAKE_C_COMPILER_ID STREQUAL COMPILER_ID_MSVC)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W3")
endif ()

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package (X11)
if (WIN32)
set (EGL_FOUND TRUE)
set (GLES_V1_FOUND FALSE)
set (GLES_V2_FOUND TRUE)
else()
find_package (EGL)
find_package (GLESv1)
find_package (GLESv2)
endif()
find_package (OpenGL)

option (GLPROXY_REBUILD_FROM_SPECS "Rebuild the auto-generated sources and headers from the specs" FALSE)
if (GLPROXY_REBUILD_FROM_SPECS AND NOT PYTHONINTERP_FOUND)
    message (FATAL_ERROR "You've set \"GLPROXY_REBUILD_FROM_SPECS\" to \"TRUE\", which requires a python interpreter, but one couldn't be found.")
endif ()

option (GLPROXY_SUPPORT_EGL "Build with EGL support" ON)
cmake_dependent_option (GLPROXY_SUPPORT_WGL "Build with WGL support" ON WIN32 OFF)

if (X11_FOUND AND OPENGL_FOUND)
    set (GLPROXY_GLX_FOUND TRUE)
else ()
    set (GLPROXY_GLX_FOUND FALSE)
endif ()
cmake_dependent_option (GLPROXY_SUPPORT_GLX "Build with GLX support"
                        "${GLPROXY_GLX_FOUND}" "NOT (WIN32 OR ANDROID)" OFF)

option (GLPROXY_BUILD_SHARED "Build a shared library" ON)

if (DEFINED CMAKE_TOOLCHAIN_FILE)
    set (GLPROXY_BUILD_TESTS_DEFAULT FALSE)
else ()
    set (GLPROXY_BUILD_TESTS_DEFAULT TRUE)
endif ()
option (GLPROXY_BUILD_TESTS "Build tests" "FALSE")

cmake_dependent_option (GLPROXY_MSVC_USE_RUNTIME_LIBRARY_DLL "Link with MSVC Runtime Library DLL" ON
                        "CMAKE_C_COMPILER_ID STREQUAL COMPILER_ID_MSVC" OFF)


set (GLPROXY_INCLUDE_DIRS  "${CMAKE_CURRENT_SOURCE_DIR}/include"
                         "${CMAKE_CURRENT_BINARY_DIR}/include"
                         "${CMAKE_CURRENT_SOURCE_DIR}/src")

if (CMAKE_C_COMPILER_ID STREQUAL COMPILER_ID_MSVC
    AND NOT GLPROXY_MSVC_USE_RUNTIME_LIBRARY_DLL)
    foreach (flags CMAKE_C_FLAGS
                   CMAKE_C_FLAGS_DEBUG
                   CMAKE_C_FLAGS_RELEASE
                   CMAKE_C_FLAGS_MINSIZEREL
                   CMAKE_C_FLAGS_RELWITHDEBINFO)
        string (REGEX REPLACE "/MDd" "/MTd" ${flags} "${${flags}}")
        string (REGEX REPLACE "/MD"  "/MT"  ${flags} "${${flags}}")
    endforeach ()
endif ()

add_subdirectory (src)

if (GLPROXY_BUILD_TESTS)
    enable_testing ()
    add_subdirectory (test)
endif ()

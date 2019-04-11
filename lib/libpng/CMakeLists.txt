# CMakeLists.txt

# Copyright (C) 2007,2009-2016 Glenn Randers-Pehrson
# Written by Christian Ehrlicher, 2007
# Revised by Roger Lowman, 2009-2010
# Revised by Clifford Yapp, 2011-2012
# Revised by Roger Leigh, 2016

# This code is released under the libpng license.
# For conditions of distribution and use, see the disclaimer
# and license in png.h

cmake_minimum_required(VERSION 2.8.3)
cmake_policy(VERSION 2.8.3)

# Set MacOSX @rpath usage globally.
if (POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif(POLICY CMP0020)
if (POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif(POLICY CMP0042)
# Use new variable expansion policy.
if (POLICY CMP0053)
  cmake_policy(SET CMP0053 NEW)
endif(POLICY CMP0053)
if (POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif(POLICY CMP0054)

if(NOT WIN32)
  find_library(M_LIBRARY
    NAMES m
    PATHS /usr/lib /usr/local/lib
  )
  if(NOT M_LIBRARY)
    message(STATUS "math lib 'libm' not found; floating point support disabled")
    set(M_LIBRARY "")
  endif()
else()
  # not needed on windows
  set(M_LIBRARY "")
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/scripts/pnglibconf.h.prebuilt
               ${CMAKE_CURRENT_BINARY_DIR}/pnglibconf.h)

# OUR SOURCES
set(libpng_public_hdrs
  png.h
  pngconf.h
  "${CMAKE_CURRENT_BINARY_DIR}/pnglibconf.h"
)
set(libpng_private_hdrs
  pngpriv.h
  pngdebug.h
  pnginfo.h
  pngstruct.h
)
set(libpng_sources
  ${libpng_public_hdrs}
  ${libpng_private_hdrs}
  png.c
  pngerror.c
  pngget.c
  pngmem.c
  pngpread.c
  pngread.c
  pngrio.c
  pngrtran.c
  pngrutil.c
  pngset.c
  pngtrans.c
  pngwio.c
  pngwrite.c
  pngwtran.c
  pngwutil.c
)

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
endif(MSVC)

# NOW BUILD OUR TARGET
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${ZLIB_INCLUDE_DIR})

unset(PNG_LIB_TARGETS)

# does not work without changing name
set(PNG_LIB_NAME_STATIC png_static)
add_library(png_static STATIC ${libpng_sources})
add_dependencies(png_static genfiles)
# MSVC doesn't use a different file extension for shared vs. static
# libs.  We are able to change OUTPUT_NAME to remove the _static
# for all other platforms.
if(NOT MSVC)
  set_target_properties(png_static PROPERTIES
    OUTPUT_NAME "${PNG_LIB_NAME}"
    CLEAN_DIRECT_OUTPUT 1)
else()
  set_target_properties(png_static PROPERTIES
    OUTPUT_NAME "${PNG_LIB_NAME}_static"
    CLEAN_DIRECT_OUTPUT 1)
endif()
list(APPEND PNG_LIB_TARGETS png_static)
if(MSVC)
  # msvc does not append 'lib' - do it here to have consistent name
  set_target_properties(png_static PROPERTIES PREFIX "lib")
endif()
target_link_libraries(png_static ${ZLIB_LIBRARY} ${M_LIBRARY})


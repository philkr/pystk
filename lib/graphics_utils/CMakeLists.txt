cmake_minimum_required(VERSION 3.0)
if (UNIX OR MINGW)
    add_definitions(-O3)
endif()
add_library(graphics_utils STATIC
    mipmap/cpusimd.c
    mipmap/imgresize.c
)

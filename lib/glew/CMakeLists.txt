# CMakeLists.txt - glew

if (NOT SERVER_ONLY)
include_directories("include")

if(APPLE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -F/Library/Frameworks")
endif()

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

add_definitions(-DGLEW_STATIC)

add_library(glew STATIC
    src/glew.c
    src/glewinfo.c
)

target_link_libraries(glew ${OPENGL_gl_LIBRARY})

endif()

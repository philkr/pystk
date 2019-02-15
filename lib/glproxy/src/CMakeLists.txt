set (HEADERS "../include/glproxy/_common.h"
             "../include/glproxy/gl.h"
             "../include/glproxy/khrplatform.h"
             "dispatch_common.h")
set (SOURCES
  dispatch_common.c
  dispatch_generated.c
)

list (APPEND HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/../include/glproxy/gl_generated.h")

set (GLPROXY_COMPILE_DEFS PRIVATE GLPROXY_BUILDING_LIB)
if (CMAKE_C_COMPILER_ID STREQUAL COMPILER_ID_MSVC)
    set (GLPROXY_COMPILE_DEFS ${GLPROXY_COMPILE_DEFS} "inline=__inline")
endif ()
set (GLPROXY_TARGET_CODE ${SOURCES} ${HEADERS})

if (GLPROXY_BUILD_SHARED)
    add_library ("${GLPROXY_TARGET_NAME}" SHARED ${GLPROXY_TARGET_CODE})
else ()
    add_library ("${GLPROXY_TARGET_NAME}" STATIC ${GLPROXY_TARGET_CODE})
endif ()
set (GLPROXY_DL_LIBS ${CMAKE_DL_LIBS})
if (NOT WIN32) 
  list (APPEND GLPROXY_DL_LIBS "pthread")
endif()

target_link_libraries ("${GLPROXY_TARGET_NAME}" ${GLPROXY_DL_LIBS})
if (WIN32 OR ANDROID)
    set_target_properties ("${GLPROXY_TARGET_NAME}" PROPERTIES
                           OUTPUT_NAME "${GLPROXY_TARGET_NAME}_${TARGET_ABI_VER}")
else ()
    set_target_properties ("${GLPROXY_TARGET_NAME}" PROPERTIES
                           OUTPUT_NAME "${GLPROXY_TARGET_NAME}")
endif ()
if (NOT ANDROID)
    set_target_properties("${GLPROXY_TARGET_NAME}" PROPERTIES
                          VERSION    "${TARGET_VER}"
                          SOVERSION  "${TARGET_ABI_VER}")
endif ()
target_include_directories ("${GLPROXY_TARGET_NAME}" PUBLIC ${GLPROXY_INCLUDE_DIRS})
target_compile_definitions ("${GLPROXY_TARGET_NAME}" PRIVATE ${GLPROXY_COMPILE_DEFS})
set_target_properties ("${GLPROXY_TARGET_NAME}" PROPERTIES C_VISIBILITY_PRESET hidden)
if (CMAKE_C_COMPILER_ID STREQUAL COMPILER_ID_MSVC)
  target_compile_options ("${GLPROXY_TARGET_NAME}" PRIVATE "-wd4996")
endif ()

install (FILES ${HEADERS} DESTINATION "include/glproxy")
install (TARGETS ${GLPROXY_TARGET_FINAL_NAME}
           RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
           LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
           ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}")
if (CMAKE_C_COMPILER_ID STREQUAL COMPILER_ID_MSVC)
    install (FILES "${CMAKE_CURRENT_BINARY_DIR}/Debug/${GLPROXY_TARGET_NAME}_${TARGET_ABI_VER}.pdb"
             DESTINATION lib  CONFIGURATIONS Debug)
endif ()

if (GLPROXY_BUILD_TESTS)
    if (GLPROXY_SUPPORT_EGL)
        if (EGL_FOUND)
            set (GLPROXY_BUILD_EGL_TESTS TRUE)
            set (GLPROXY_EGL_TESTS_COMMON egl_common.c egl_common.h)
        else ()
            set (GLPROXY_BUILD_EGL_TESTS FALSE)
            message (WARNING "EGL not found - EGL tests will not be built!")
        endif ()
    endif ()
    if (GLPROXY_SUPPORT_GLX)
        set (GLPROXY_GLX_TESTS_COMMON glx_common.c glx_common.h)
    endif ()
    if (GLPROXY_SUPPORT_WGL)
        set (GLPROXY_WGL_TESTS_COMMON wgl_common.c wgl_common.h)
    endif ()

    set (GLPROXY_LINKAGE_TYPE_SHARED SHARED)
    set (GLPROXY_LINKAGE_TYPE_STATIC STATIC)
    
    function (glproxy_add_test GLPROXY_TEST_NAME GLPROXY_TEST_CODE)
      # Additional optional arguments: "GLPROXY_TEST_DEPS GLPROXY_TEST_COMPILE_DEFS GLPROXY_TEST_LINK_FLAGS"
      #                                "GLPROXY_LINKAGE_TYPE"
      
        if (ARGC GREATER 2)
            set (GLPROXY_TEST_DEPS "${ARGV2}")
        else ()
            set (GLPROXY_TEST_DEPS "")
        endif ()
        if (ARGC GREATER 3)
            set (GLPROXY_TEST_COMPILE_DEFS "${ARGV3}")
        else ()
            set (GLPROXY_TEST_COMPILE_DEFS "")
        endif ()
        if (ARGC GREATER 4)
            set (GLPROXY_TEST_LINK_FLAGS "${ARGV4}")
        else ()
            set (GLPROXY_TEST_LINK_FLAGS "")
        endif ()
        if (ARGC GREATER 5)
            set (GLPROXY_TEST_LINKAGE_TYPE "${ARGV5}")
        else ()
            set (GLPROXY_TEST_LINKAGE_TYPE BOTH)
        endif ()
        
        if (NOT GLPROXY_TEST_LINKAGE_TYPE STREQUAL GLPROXY_LINKAGE_TYPE_STATIC)
            set (GLPROXY_TEST_TARGET_NAME "test_shared_${GLPROXY_TEST_NAME}")
            add_executable (${GLPROXY_TEST_TARGET_NAME} ${GLPROXY_TEST_CODE})
            target_link_libraries (${GLPROXY_TEST_TARGET_NAME} "${GLPROXY_TARGET_NAME}" ${GLPROXY_TEST_DEPS})
            target_compile_definitions (${GLPROXY_TEST_TARGET_NAME} PRIVATE
                                        ${GLPROXY_TEST_COMPILE_DEFS})
            target_include_directories (${GLPROXY_TEST_TARGET_NAME} PRIVATE ${GLPROXY_INCLUDE_DIRS})
            set_target_properties (${GLPROXY_TEST_TARGET_NAME} PROPERTIES
                                   LINK_FLAGS "${GLPROXY_TEST_LINK_FLAGS}")
           if (CMAKE_C_COMPILER_ID STREQUAL COMPILER_ID_MSVC)
              target_compile_options(${GLPROXY_TEST_TARGET_NAME} PRIVATE -wd4996)
            endif ()
            add_test (NAME "${GLPROXY_TEST_TARGET_NAME}"
                      COMMAND "${CMAKE_COMMAND}"
                          "-DGLPROXY_TEST_CMD=$<TARGET_FILE:${GLPROXY_TEST_TARGET_NAME}>"
                          "-DGLPROXY_SHARED_LIB=$<TARGET_FILE:${GLPROXY_TARGET_NAME}>"
                          "-P" "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/glproxy_run_test_wrapper.cmake")
        endif ()
        
        
    endfunction ()

    if (GLPROXY_BUILD_EGL_TESTS AND X11_FOUND)

        glproxy_add_test (egl_has_extension_nocontext "${GLPROXY_EGL_TESTS_COMMON};egl_has_extension_nocontext.c"
                        "${X11_LIBRARIES}")
        glproxy_add_test (egl_gl "${GLPROXY_EGL_TESTS_COMMON};egl_gl.c" "${X11_LIBRARIES}")
        if (GLES_V1_FOUND)
            glproxy_add_test (egl_gles1_without_glx "${GLPROXY_EGL_TESTS_COMMON};egl_without_glx.c" "${X11_LIBRARIES}"
                            "GLES_VERSION=1")
        endif ()
        if (GLES_V2_FOUND)
            glproxy_add_test (egl_gles2_without_glx "${GLPROXY_EGL_TESTS_COMMON};egl_without_glx.c" "${X11_LIBRARIES}"
                            "GLES_VERSION=2")
        endif ()
    endif()
    if (GLPROXY_BUILD_EGL_TESTS AND WIN32)
        glproxy_add_test (egl_has_extension_nocontext "${GLPROXY_EGL_TESTS_COMMON};egl_has_extension_nocontext.c"
                        "${X11_LIBRARIES}")
        glproxy_add_test (egl_gles2_without_glx "${GLPROXY_EGL_TESTS_COMMON};egl_without_glx.c" "${X11_LIBRARIES}"
                "GLES_VERSION=2")
    endif()
    
    if (GLPROXY_BUILD_EGL_TESTS AND GLPROXY_SUPPORT_GLX AND NOT APPLE)
    
        #glproxy_add_test (egl_and_glx_different_pointers "${GLPROXY_EGL_TESTS_COMMON};${GLPROXY_GLX_TESTS_COMMON};egl_and_glx_different_pointers.c;dlwrap.c;dlwrap.h" "${X11_LIBRARIES}" "USE_EGL;USE_GLX" "-rdynamic")
        glproxy_add_test (egl_different_pointers
          "${GLPROXY_EGL_TESTS_COMMON};${GLPROXY_GLX_TESTS_COMMON};egl_and_glx_different_pointers.c;dlwrap.c;dlwrap.h"
          "${X11_LIBRARIES}" "USE_EGL" "-rdynamic")
        glproxy_add_test (glx_different_pointers
          "${GLPROXY_EGL_TESTS_COMMON};${GLPROXY_GLX_TESTS_COMMON};egl_and_glx_different_pointers.c;dlwrap.c;dlwrap.h"
          "${X11_LIBRARIES}" "USE_GLX" "-rdynamic")
    endif ()

    if (GLPROXY_SUPPORT_GLX)
    
        if (NOT APPLE)
            glproxy_add_test (glx_alias_prefer_same_name
              "${GLPROXY_GLX_TESTS_COMMON};glx_alias_prefer_same_name.c;dlwrap.c;dlwrap.h" "${X11_LIBRARIES}"
              "" "-rdynamic")
            if (GLES_V2_FOUND)
                glproxy_add_test (test_glx_gles2
                  "${GLPROXY_GLX_TESTS_COMMON};glx_gles2.c;dlwrap.c;dlwrap.h" "${X11_LIBRARIES}" "" "-rdynamic")
            endif ()
        endif ()
        
        glproxy_add_test (test_glx_beginend "${GLPROXY_GLX_TESTS_COMMON};glx_beginend.c"
                        "${OPENGL_gl_LIBRARY};${X11_LIBRARIES}")
        glproxy_add_test (glx_public_api "${GLPROXY_GLX_TESTS_COMMON};glx_public_api.c" "${X11_LIBRARIES}")
        glproxy_add_test (glx_public_api_core "${GLPROXY_GLX_TESTS_COMMON};glx_public_api_core.c" "${X11_LIBRARIES}")
        glproxy_add_test (glx_getprocaddress_nocontext
          "${GLPROXY_GLX_TESTS_COMMON};glx_glxgetprocaddress_nocontext.c" "${X11_LIBRARIES}")
        glproxy_add_test (glx_has_extension_nocontext "${GLPROXY_GLX_TESTS_COMMON};glx_has_extension_nocontext.c"
                        "${X11_LIBRARIES}")

        glproxy_add_test (glx_shared_znow "${GLPROXY_GLX_TESTS_COMMON};glx_static.c"
                        "${X11_LIBRARIES}" "" "-Wl,-z,now" SHARED)
        glproxy_add_test (glx_static "${GLPROXY_GLX_TESTS_COMMON};glx_static.c"
                        "${X11_LIBRARIES}" "NEEDS_TO_BE_STATIC" "" STATIC)
    endif ()

	glproxy_add_test (headerguards headerguards.c)
	glproxy_add_test (miscdefines miscdefines.c)

    if (GLPROXY_SUPPORT_WGL)
        glproxy_add_test (wgl_core_and_exts "${GLPROXY_WGL_TESTS_COMMON};wgl_core_and_exts.c")
		glproxy_add_test (wgl_per_context_funcptrs "${GLPROXY_WGL_TESTS_COMMON};wgl_per_context_funcptrs.c")
		glproxy_add_test (wgl_usefontbitmaps_ascii "${GLPROXY_WGL_TESTS_COMMON};wgl_usefontbitmaps.c")
		glproxy_add_test (wgl_usefontbitmaps_unicode "${GLPROXY_WGL_TESTS_COMMON};wgl_usefontbitmaps.c"
                                "" "_UNICODE;UNICODE")
	endif ()

endif ()

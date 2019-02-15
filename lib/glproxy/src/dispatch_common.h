/*
 * Copyright © 2013 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#pragma once
#ifndef _DISPATCH_COMMON_H
#define _DISPATCH_COMMON_H

#define PLATFORM_HAS_GL 1
#define PLATFORM_HAS_EGL 1

#ifdef _WIN32
#define PLATFORM_HAS_CGL 0
#define PLATFORM_HAS_WGL 1
#define PLATFORM_HAS_GLX 0
#elif defined(__APPLE__)
#define PLATFORM_HAS_CGL 1
#define PLATFORM_HAS_WGL 0
#define PLATFORM_HAS_GLX 1
#elif defined(ANDROID)
#define PLATFORM_HAS_CGL 0
#define PLATFORM_HAS_WGL 0
#define PLATFORM_HAS_GLX 1
#else
#define PLATFORM_HAS_CGL 0
#define PLATFORM_HAS_WGL 0
#define PLATFORM_HAS_GLX 1
#endif

#if PLATFORM_HAS_WGL
#include "glproxy/wgl.h"
#endif
#if PLATFORM_HAS_GLX
#include "glproxy/glx.h"
#endif

#include "glproxy/egl.h"
#include "glproxy/gl.h"

#if defined(__GNUC__)
#define PACKED __attribute__((__packed__))
#else
#define PACKED
#endif

#include "wgl_generated_dispatch_table_type.inc"
#include "glx_generated_dispatch_table_type.inc"
#include "gl_generated_dispatch_table_type.inc"
#include "egl_generated_dispatch_table_type.inc"

#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#include <err.h>
#include <pthread.h>
#endif
#ifdef __GNUC__
#define GLOBAL_STAIC_FUNCTION(construct, destruct) \
static void construct ## _constructor(void) __attribute__((constructor)); \
static void construct ## _constructor(void) { construct(); } \
static void destruct ## _destructor(void) __attribute__((destructor)); \
static void destruct ## _destructor(void) { destruct(); }

#elif defined (_MSC_VER) && (_MSC_VER >= 1500)

// Refer to http://stackoverflow.com/questions/36841629/visual-c-2015-gl-whole-program-optimization-and-optref-optimize-referenc
#ifdef _M_X64
#define INCLUDE_SYM(s) comment(linker, "/include:" #s)
#else
#define INCLUDE_SYM(s) comment(linker, "/include:_" #s)
#endif

#define GLOBAL_STAIC_FUNCTION(construct, destruct) \
static void destruct ## _destructor(void) { destruct(); } \
static int construct ## _constructor(void) { \
    construct(); \
    atexit(destruct ## _destructor); \
    return 0; } \
__pragma(section(".CRT$XCU",read)) \
__declspec(allocate(".CRT$XCU")) \
int (*construct ## _array)(void) = construct ## _constructor; \
__pragma(INCLUDE_SYM(construct ## _array))

#else

#define GLOBAL_STAIC_FUNCTION(construct, destruct)
//#message "You will need constructor support for your compiler"
#endif

#ifdef __GNUC__
#define GLPROXY_NOINLINE __attribute__((noinline))
#elif defined (_MSC_VER) && _MSC_VER >= 1500
#define GLPROXY_NOINLINE __declspec(noinline)
#else
#define GLPROXY_NOINLINE
#endif

#define GEN_THUNK(target, name, args, passthrough, offset, func_type)          \
    GLPROXY_IMPORTEXPORT void GLPROXY_CALLSPEC                                 \
    name args                                                                  \
    {                                                                          \
        func_type func_symbol = target##_resolve(offset);                      \
        func_symbol passthrough;                                               \
    }

#define GEN_THUNK_RET(target, ret, name, args, passthrough, offset, func_type) \
    GLPROXY_IMPORTEXPORT ret GLPROXY_CALLSPEC                                  \
    name args                                                                  \
    {                                                                          \
        func_type func_symbol = target##_resolve(offset);                      \
        return func_symbol passthrough;                                        \
    }

enum DISPATCH_OPENGL_TYPE {
    DISPATCH_OPENGL_UNKNOW = 0,
    DISPATCH_OPENGL_CGL_DESKTOP,
    DISPATCH_OPENGL_WGL_DESKTOP,
    DISPATCH_OPENGL_GLX_DESKTOP,
    DISPATCH_OPENGL_EGL_DESKTOP,
    DISPATCH_OPENGL_ES, /* Only comes from EGL or EAGL*/
} PACKED;

enum DISPATCH_RESOLVE_TYPE {
    DISPATCH_RESOLVE_DIRECT = 0,
    DISPATCH_RESOLVE_VERSION = 1,
    DISPATCH_RESOLVE_EXTENSION = 2,
    DISPATCH_RESOLVE_TERMINATOR = 3,
} PACKED;

struct dispatch_resolve_info {
    khronos_uint8_t resolve_type;
    khronos_uint8_t identity;
    khronos_uint16_t condition;
    khronos_uint32_t name_offset;
} PACKED;

struct dispatch_metadata {
    const char* extension_enum_strings;
    const khronos_uint16_t *extension_offsets;
    const char* entrypoint_strings;
    const struct dispatch_resolve_info *resolve_info_table;
    khronos_uint16_t *resolve_offsets;
    khronos_uint32_t *method_name_offsets;
    khronos_uint16_t extensions_count;
    khronos_uint16_t method_count;
    bool inited;
};

struct dispatch_common_tls {
#if PLATFORM_HAS_WGL
    struct wgl_dispatch_table wgl_dispatch_table;
    struct dispatch_metadata wgl_metadata;
    PFNWGLGETPROCADDRESSPROC wgl_get_proc;
#endif

#if PLATFORM_HAS_GLX
    struct glx_dispatch_table glx_dispatch_table;
    struct dispatch_metadata glx_metadata;
    PFNGLXGETPROCADDRESSPROC glx_get_proc;
    PFNGLXGETPROCADDRESSARBPROC glx_get_proc_arb;

#endif

    struct gl_dispatch_table gl_dispatch_table;
    struct dispatch_metadata gl_metadata;
    khronos_uint32_t gl_extension_bitmap[GL_EXTENSIONS_BITMAP_COUNT];

    struct egl_dispatch_table egl_dispatch_table;
    struct dispatch_metadata egl_metadata;

    bool has_parameters;
    struct glproxy_gl_context param_context;
    struct glproxy_gl_context context;
    void* gl_handle;
    void* gles_handle;
    PFNEGLGETPROCADDRESSPROC egl_get_proc;
    bool gl_called;
    enum DISPATCH_OPENGL_TYPE open_gl_type;
    int gl_version;

    bool handles_opened;
};

typedef struct dispatch_common_tls *tls_ptr;

#if defined(_WIN32)
#define TLS_TYPE DWORD
#else
#define TLS_TYPE pthread_key_t
#endif

extern TLS_TYPE glproxy_dispatch_common_tls_index;

static inline tls_ptr get_tls_by_index(TLS_TYPE index) {
#if defined(_WIN32)
    return (void*)TlsGetValue(index);
#else
    return (void*)pthread_getspecific(index);
#endif
}

static inline void set_tls_by_index(TLS_TYPE index, tls_ptr value) {
#if defined(_WIN32)
    TlsSetValue(index, (LPVOID)value);
#else
    pthread_setspecific(index, (void*)value);
#endif
}

void glproxy_context_handles_open(tls_ptr tls);
void glproxy_context_handles_close(tls_ptr tls);

#if PLATFORM_HAS_WGL
void wgl_glproxy_resolve_init(tls_ptr tls);
void wgl_glproxy_resolve_direct(tls_ptr tls, const char* name, void**ptr);
void wgl_glproxy_resolve_extension(tls_ptr tls, const char* name, void**ptr, khronos_uint16_t offset);
#endif

#if PLATFORM_HAS_GLX
void glx_glproxy_resolve_init(tls_ptr tls);
void glx_glproxy_resolve_direct(tls_ptr tls, const char* name, void**ptr);
void glx_glproxy_resolve_extension(tls_ptr tls, const char* name, void**ptr, khronos_uint16_t offset);
#endif

void gl_glproxy_resolve_init(tls_ptr tls);
void gl_glproxy_resolve_direct(tls_ptr tls, const char* name, void**ptr);
void gl_glproxy_resolve_version(tls_ptr tls, const char* name, void**ptr, khronos_uint16_t version);
void gl_glproxy_resolve_extension(tls_ptr tls, const char* name, void**ptr, khronos_uint16_t offset);

void egl_glproxy_resolve_init(tls_ptr tls);
void egl_glproxy_resolve_direct(tls_ptr tls, const char* name, void**ptr);
void egl_glproxy_resolve_version(tls_ptr tls, const char* name, void**ptr, khronos_uint16_t version);
void egl_glproxy_resolve_extension(tls_ptr tls, const char* name, void**ptr, khronos_uint16_t offset);

void glproxy_dispatch_common_tls_init(tls_ptr tls, bool glproxy_inited);

#endif /* _DISPATCH_COMMON_H */
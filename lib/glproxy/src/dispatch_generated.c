
#include "dispatch_common.h"
#include <stdio.h>

static void init_dispatch_metadata_metadata(struct dispatch_metadata *data) {
    const struct dispatch_resolve_info *iter = NULL;
    khronos_uint16_t offset = 0;
    khronos_uint16_t pos = 0;
    khronos_uint8_t prev_identity = -1;
    for (iter = data->resolve_info_table; iter->resolve_type != DISPATCH_RESOLVE_TERMINATOR; ++iter,++offset) {
        if (iter->identity != prev_identity) {
            prev_identity = iter->identity;
            data->resolve_offsets[pos] = offset;
            data->method_name_offsets[pos] = iter->name_offset;
            ++pos;
        }
    }
}

#include "wgl_generated_dispatch_thunks.inc"
#include "glx_generated_dispatch_thunks.inc"
#include "gl_generated_dispatch_thunks.inc"
#include "egl_generated_dispatch_thunks.inc"

void glproxy_dispatch_common_tls_init(tls_ptr tls, bool glproxy_inited) {
    tls->open_gl_type = DISPATCH_OPENGL_UNKNOW;
#ifndef NDEBUG
    // fprintf(stderr, "sizeof dispatch_resolve_info :%d\n", (int)sizeof(struct dispatch_resolve_info));
#endif

#if PLATFORM_HAS_WGL
    wgl_glproxy_dispatch_metadata_init(&(tls->wgl_metadata), glproxy_inited);
#endif
#if PLATFORM_HAS_GLX
    glx_glproxy_dispatch_metadata_init(&(tls->glx_metadata), glproxy_inited);
#endif

    gl_glproxy_dispatch_metadata_init(&(tls->gl_metadata), glproxy_inited);

#if PLATFORM_HAS_EGL
    egl_glproxy_dispatch_metadata_init(&(tls->egl_metadata), glproxy_inited);
#endif
}

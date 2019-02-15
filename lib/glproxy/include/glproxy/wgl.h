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

/** @file wgl.h
 *
 * Provides an implementation of a WGL dispatch layer using a hidden
 * vtable.
 */

#ifndef GLPROXY_WGL_H
#define GLPROXY_WGL_H

#if defined(__wglxext_h_)
#error "glproxy/wgl.h" must be included before (or in place of) "wglext.h"
#endif

#define __wglxext_h_

#include "glproxy/gl.h"

#ifdef __cplusplus
extern "C" {
#endif

#undef wglUseFontBitmaps
#undef wglUseFontOutlines

#if defined(_UNICODE) || defined(UNICODE)
#define wglUseFontBitmaps wglUseFontBitmapsW
#else
#define wglUseFontBitmaps wglUseFontBitmapsA
#endif

#include "glproxy/wgl_generated.h"

GLPROXY_IMPORTEXPORT bool glproxy_has_wgl_extension(HDC hdc, const char *extension);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* GLPROXY_WGL_H */

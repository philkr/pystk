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

/** @file common.h
 *
 * Provides basic definitions for GLproxy. Included by all other GLproxy files.
 */

#ifndef GLPROXY_GL_H
#error "glproxy/_common.h" must be included by glproxy/gl.h directly, do not include it outside
#endif

#ifndef GLPROXY_COMMON_H
#define GLPROXY_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined _WIN32 || defined __CYGWIN__
    #if defined(GLPROXY_IMPORTEXPORT)
        #undef GLPROXY_IMPORTEXPORT
        #define GLPROXY_STATIC_LIB
    #endif

    #if defined(GLPROXY_STATIC_LIB)
        #define GLPROXY_IMPORTEXPORT
    #else
        #if defined GLPROXY_BUILDING_LIB
            #ifdef __GNUC__
                #define GLPROXY_IMPORTEXPORT __attribute__((dllexport))
            #else
                #define GLPROXY_IMPORTEXPORT __declspec(dllexport)
            #endif
        #else
            #ifdef __GNUC__
                #define GLPROXY_IMPORTEXPORT __attribute__((dllimport))
            #else
                #define GLPROXY_IMPORTEXPORT __declspec(dllimport)
            #endif
        #endif
    #endif
#elif defined __ANDROID__
    #include <sys/cdefs.h>
    #define GLPROXY_IMPORTEXPORT __attribute__((visibility("default"))) __NDK_FPABI__
#elif (defined __GNUC__ && __GNUC__ >= 4)  ||  (defined __SUNPRO_C && __SUNPRO_C >= 0x590)
    #define GLPROXY_IMPORTEXPORT __attribute__((visibility("default")))
#else
    #define GLPROXY_IMPORTEXPORT
#endif

// Prevent "unused variable/parameter" warnings.
#define GLPROXY_UNUSED(var) ((void)var)

#ifdef __cplusplus
}
#endif

#endif /* GLPROXY_COMMON_H */

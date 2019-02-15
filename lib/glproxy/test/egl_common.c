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

#include <glproxy/egl.h>
#include <stdio.h>
#include "egl_common.h"
#ifndef _WIN32
#include <err.h>
#include <X11/Xlib.h>
#endif

#ifdef _WIN32

static LRESULT CALLBACK
window_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message) {
    case WM_CREATE: {
        CREATESTRUCT *creat_info = (CREATESTRUCT*)lparam;
        bool *finished_ptr = creat_info->lpCreateParams;
        *finished_ptr = TRUE;
        return 0;
    }
    default:
        return DefWindowProc(hwnd, message, wparam, lparam);
    }
}

HDC
make_window_and_test(void** nativeWindow)
{
    LPCTSTR class_name = TEXT("glproxy");
    LPCTSTR window_name = TEXT("glproxy");
    int width = 150;
    int height = 150;
    HWND hwnd;
    HINSTANCE hcurrentinst = NULL;
    WNDCLASS window_class;
    bool finished = 0;
    bool *ptr = &finished;
    HDC hdc;

    memset(&window_class, 0, sizeof(window_class));
    window_class.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.lpfnWndProc = window_proc;
    window_class.hInstance = hcurrentinst;
    window_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
    window_class.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    window_class.lpszMenuName = NULL;
    window_class.lpszClassName = class_name;
    if (!RegisterClass(&window_class)) {
        fprintf(stderr, "Failed to register window class\n");
        exit(1);
    }
    /* create window */
    hwnd = CreateWindowEx(0, class_name, window_name,
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
        0, 0, width, height,
        NULL, NULL, hcurrentinst, ptr);
    if (nativeWindow) {
        *nativeWindow = hwnd;
    }
    hdc = GetDC(hwnd);
    return hdc;
}

#endif

void *glproxy_context = NULL;

/**
 * Do whatever it takes to get us an EGL display for the system.
 *
 * This needs to be ported to other window systems.
 */
EGLDisplay 
get_egl_display_or_skip(void** nativeWindow)
{
#ifdef _WIN32
    HDC dpy = make_window_and_test(nativeWindow);
#else
    Display *dpy = XOpenDisplay(NULL);
#endif
    EGLint major, minor;
    EGLDisplay edpy;
    bool ok;
    struct glproxy_gl_context params = { 0 };
    if (!dpy)
        fprintf(stderr, "couldn't open display\n");
    //params.gles_names.egl = "libEGLd.dll";
    //params.gles_names.gles2 = "libGLESv2d.dll";
    //glproxy_context = glproxy_context_create(&params);
    //glproxy_context_set(glproxy_context);
    edpy = eglGetDisplay((EGLNativeDisplayType)dpy);
    if (edpy == EGL_NO_DISPLAY)
        fprintf(stderr, "Couldn't get EGL display for X11 Display.\n");

    ok = eglInitialize(edpy, &major, &minor);
    if (!ok)
        fprintf(stderr, "eglInitialize() failed\n");

    return edpy;
}


void get_egl_display_finish() {
    //glproxy_context_destroy(glproxy_context);
}

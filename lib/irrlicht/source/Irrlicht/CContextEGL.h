//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2016-2017 SuperTuxKart-Team
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef CONTEXT_EGL_HPP
#define CONTEXT_EGL_HPP

#include "IrrCompileConfig.h"

#if defined(_IRR_COMPILE_WITH_EGL_)

#include <EGL/egl.h>

#ifndef EGL_CONTEXT_MAJOR_VERSION
#define EGL_CONTEXT_MAJOR_VERSION 0x3098
#endif
#ifndef EGL_CONTEXT_MINOR_VERSION
#define EGL_CONTEXT_MINOR_VERSION 0x30FB
#endif
#ifndef EGL_GL_COLORSPACE
#define EGL_GL_COLORSPACE 0x309D
#endif
#ifndef EGL_GL_COLORSPACE_SRGB
#define EGL_GL_COLORSPACE_SRGB 0x3089
#endif
#ifndef EGL_GL_COLORSPACE_LINEAR
#define EGL_GL_COLORSPACE_LINEAR 0x308A
#endif
#ifndef EGL_PLATFORM_ANDROID
#define EGL_PLATFORM_ANDROID 0x3141
#endif
#ifndef EGL_PLATFORM_GBM
#define EGL_PLATFORM_GBM 0x31D7
#endif
#ifndef EGL_PLATFORM_WAYLAND
#define EGL_PLATFORM_WAYLAND 0x31D8
#endif
#ifndef EGL_PLATFORM_X11
#define EGL_PLATFORM_X11 0x31D5
#endif
#ifndef EGL_PLATFORM_DEVICE
#define EGL_PLATFORM_DEVICE 0x313F
#endif

enum ContextEGLOpenGLAPI
{
    CEGL_API_OPENGL,
    CEGL_API_OPENGL_ES
};

enum ContextEGLSurfaceType
{
    CEGL_SURFACE_WINDOW,
    CEGL_SURFACE_PBUFFER
};

enum ContextEGLPlatform
{
    CEGL_PLATFORM_ANDROID,
    CEGL_PLATFORM_GBM,
    CEGL_PLATFORM_WAYLAND,
    CEGL_PLATFORM_X11,
    CEGL_PLATFORM_DEVICE,
    CEGL_PLATFORM_DEFAULT
};

struct ContextEGLParams
{
    ContextEGLOpenGLAPI opengl_api = CEGL_API_OPENGL;
    ContextEGLSurfaceType surface_type = CEGL_SURFACE_WINDOW;
    ContextEGLPlatform platform = CEGL_PLATFORM_DEFAULT;
    EGLNativeWindowType window = 0;
    EGLNativeDisplayType display = 0;
    int device_id = 0;
    bool force_legacy_device = false;
    bool handle_srgb = false;
    bool with_alpha_channel = false;
    bool vsync_enabled = false;
    int pbuffer_width = 0;
    int pbuffer_height = 0;
    bool debug = false;
};


class ContextManagerEGL
{
private:
    EGLNativeWindowType m_egl_window;
    EGLDisplay m_egl_display;
    EGLSurface m_egl_surface;
    EGLContext m_egl_context;
    EGLConfig m_egl_config;

    ContextEGLParams m_creation_params;
    bool m_is_legacy_device;
    bool m_initialized;
    int m_egl_version;

    typedef EGLDisplay (*eglGetPlatformDisplay_t) (EGLenum, void*, const EGLint*);
    typedef EGLDisplay (*eglQueryDevices_t) (EGLint, void*, EGLint*);
    typedef const char * (*eglQueryDeviceString_t) (void*, EGLint);
    eglGetPlatformDisplay_t eglGetPlatformDisplay;
    eglQueryDevices_t eglQueryDevices;
    eglQueryDeviceString_t eglQueryDeviceString;
    
    bool initExtensions();
    bool initDisplay();
    bool chooseConfig();
    bool createSurface();
    bool createContext();
    bool hasEGLExtension(const char* extension);
    bool checkEGLError();

public:
    ContextManagerEGL();
    ~ContextManagerEGL();

    bool init(const ContextEGLParams& params);
    void close();

    void reloadEGLSurface(void* window);
    bool swapBuffers();
    bool makeCurrent();
    bool isLegacyDevice() {return m_is_legacy_device;}
    bool getSurfaceDimensions(int* width, int* height);
};

#endif

#endif

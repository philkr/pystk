//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2014-2015 SuperTuxKart-Team
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

#ifndef SERVER_ONLY

#include "graphics/glwrap.hpp"

#include "config/hardware_stats.hpp"
#include "config/user_config.hpp"
#include "graphics/central_settings.hpp"
#include "graphics/irr_driver.hpp"
#include "graphics/shaders.hpp"
#include "graphics/sp/sp_base.hpp"
#include "utils/profiler.hpp"
#include "utils/cpp2011.hpp"
#include "utils/string_utils.hpp"

#include <fstream>
#include <string>
#include <sstream>

#ifdef DEBUG
#if !defined(__APPLE__) && !defined(ANDROID)
#define ARB_DEBUG_OUTPUT
#endif
#endif

#if defined(USE_GLES2)
#ifndef __APPLE__
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

#ifdef ARB_DEBUG_OUTPUT
#define GL_DEBUG_SEVERITY_HIGH_ARB            GL_DEBUG_SEVERITY_HIGH_KHR
#define GL_DEBUG_SEVERITY_LOW_ARB             GL_DEBUG_SEVERITY_LOW_KHR
#define GL_DEBUG_SEVERITY_MEDIUM_ARB          GL_DEBUG_SEVERITY_MEDIUM_KHR
#define GL_DEBUG_SOURCE_API_ARB               GL_DEBUG_SOURCE_API_KHR
#define GL_DEBUG_SOURCE_APPLICATION_ARB       GL_DEBUG_SOURCE_APPLICATION_KHR
#define GL_DEBUG_SOURCE_OTHER_ARB             GL_DEBUG_SOURCE_OTHER_KHR
#define GL_DEBUG_SOURCE_SHADER_COMPILER_ARB   GL_DEBUG_SOURCE_SHADER_COMPILER_KHR
#define GL_DEBUG_SOURCE_THIRD_PARTY_ARB       GL_DEBUG_SOURCE_THIRD_PARTY_KHR
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB     GL_DEBUG_SOURCE_WINDOW_SYSTEM_KHR
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR
#define GL_DEBUG_TYPE_ERROR_ARB               GL_DEBUG_TYPE_ERROR_KHR
#define GL_DEBUG_TYPE_OTHER_ARB               GL_DEBUG_TYPE_OTHER_KHR
#define GL_DEBUG_TYPE_PERFORMANCE_ARB         GL_DEBUG_TYPE_PERFORMANCE_KHR
#define GL_DEBUG_TYPE_PORTABILITY_ARB         GL_DEBUG_TYPE_PORTABILITY_KHR
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB  GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR

#define GLDEBUGPROCARB GLDEBUGPROCKHR
PFNGLDEBUGMESSAGECALLBACKKHRPROC pglDebugMessageCallbackKHR;
#define glDebugMessageCallbackARB pglDebugMessageCallbackKHR
#endif
#endif

static bool is_gl_init = false;

#if DEBUG
bool GLContextDebugBit = true;
#else
bool GLContextDebugBit = false;
#endif

#ifdef ARB_DEBUG_OUTPUT
static void
#ifdef WIN32
CALLBACK
#endif
debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
              const GLchar* msg, const void *userparam)
{
#ifdef GL_DEBUG_SEVERITY_NOTIFICATION
    // ignore minor notifications sent by some drivers (notably the nvidia one)
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
        return;
#endif

    // suppress minor performance warnings (emitted mostly by nvidia drivers)
    if ((severity == GL_DEBUG_SEVERITY_MEDIUM_ARB || severity == GL_DEBUG_SEVERITY_LOW_ARB) &&
        type == GL_DEBUG_TYPE_PERFORMANCE_ARB)
    {
        return;
    }

    switch(source)
    {
    case GL_DEBUG_SOURCE_API_ARB:
        Log::warn("GLWrap", "OpenGL debug callback - API");
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:
        Log::warn("GLWrap", "OpenGL debug callback - WINDOW_SYSTEM");
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB:
        Log::warn("GLWrap", "OpenGL debug callback - SHADER_COMPILER");
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:
        Log::warn("GLWrap", "OpenGL debug callback - THIRD_PARTY");
        break;
    case GL_DEBUG_SOURCE_APPLICATION_ARB:
        Log::warn("GLWrap", "OpenGL debug callback - APPLICATION");
        break;
    case GL_DEBUG_SOURCE_OTHER_ARB:
        Log::warn("GLWrap", "OpenGL debug callback - OTHER");
        break;
    }

    switch(type)
    {
    case GL_DEBUG_TYPE_ERROR_ARB:
        Log::warn("GLWrap", "    Error type : ERROR");
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB:
        Log::warn("GLWrap", "    Error type : DEPRECATED_BEHAVIOR");
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:
        Log::warn("GLWrap", "    Error type : UNDEFINED_BEHAVIOR");
        break;
    case GL_DEBUG_TYPE_PORTABILITY_ARB:
        Log::warn("GLWrap", "    Error type : PORTABILITY");
        break;
    case GL_DEBUG_TYPE_PERFORMANCE_ARB:
        Log::warn("GLWrap", "    Error type : PERFORMANCE");
        break;
    case GL_DEBUG_TYPE_OTHER_ARB:
        Log::warn("GLWrap", "    Error type : OTHER");
        break;
    }

    switch(severity)
    {
    case GL_DEBUG_SEVERITY_HIGH_ARB:
        Log::warn("GLWrap", "    Severity : HIGH");
        break;
    case GL_DEBUG_SEVERITY_MEDIUM_ARB:
        Log::warn("GLWrap", "    Severity : MEDIUM");
        break;
    case GL_DEBUG_SEVERITY_LOW_ARB:
        Log::warn("GLWrap", "    Severity : LOW");
        break;
    }
    
    if (msg)
        Log::warn("GLWrap", "    Message : %s", msg);
}
#endif

#ifdef USE_GLES2
#ifndef IOS_STK
GL_APICALL void(*GL_APIENTRY glDebugMessageControl)(GLenum source, GLenum type,
    GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
GL_APICALL void(*GL_APIENTRY glDebugMessageInsert)(GLenum source, GLenum type,
    GLuint id, GLenum severity, GLsizei length, const char *message);
#endif

#define GL_DEBUG_SOURCE_APPLICATION 0x824A
#define GL_DEBUG_TYPE_MARKER 0x8268
#define GL_DEBUG_SEVERITY_NOTIFICATION 0x826B
#endif

void initGL()
{
    if (is_gl_init)
        return;
        
    is_gl_init = true;
    // For Mesa extension reporting
#if !defined(USE_GLES2)
#ifndef WIN32
    glewExperimental = GL_TRUE;
#endif
    GLenum err = glewInit();
    
    if (err == GLEW_ERROR_NO_GLX_DISPLAY)
    {
//         Log::info("GLEW", "Glew couldn't open glx display.");
    }
    else if (err != GLEW_OK)
    {
        Log::fatal("GLEW", "Glew initialization failed with error %s", glewGetErrorString(err));
    }
#else
#ifdef ARB_DEBUG_OUTPUT
    glDebugMessageCallbackARB = (PFNGLDEBUGMESSAGECALLBACKKHRPROC)eglGetProcAddress("glDebugMessageCallbackKHR");
#endif
#endif

#ifdef ARB_DEBUG_OUTPUT
    if (glDebugMessageCallbackARB)
        glDebugMessageCallbackARB((GLDEBUGPROCARB)debugCallback, NULL);
#endif

#ifndef ANDROID
    if (SP::sp_apitrace && hasGLExtension("GL_KHR_debug"))
    {
#ifndef IOS_STK
#ifdef USE_GLES2
        glDebugMessageControl = (void(GL_APIENTRY*)(GLenum, GLenum, GLenum, GLsizei,
            const GLuint*, GLboolean))eglGetProcAddress("glDebugMessageControlKHR");
        glDebugMessageInsert = (void(GL_APIENTRY*)(GLenum, GLenum, GLuint, GLenum,
            GLsizei, const char*))eglGetProcAddress("glDebugMessageInsertKHR");
        assert(glDebugMessageControl && glDebugMessageInsert);
#endif
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
#endif
    }
    else
    {
        SP::sp_apitrace = false;
    }
#endif
}

ScopedGPUTimer::ScopedGPUTimer(GPUTimer &t) : timer(t)
{
}
ScopedGPUTimer::~ScopedGPUTimer() {
}

GPUTimer::GPUTimer(const char* name)
        : m_name(name)
{
    reset();
}

unsigned GPUTimer::elapsedTimeus()
{
    if (!initialised)
        return 0;
    GLuint result;
    glGetQueryObjectuiv(query, GL_QUERY_RESULT_AVAILABLE, &result);
    if (result == GL_FALSE)
        return lastResult;
    glGetQueryObjectuiv(query, GL_QUERY_RESULT, &result);
    lastResult = result / 1000;
    canSubmitQuery = true;
    return result / 1000;
}

void draw3DLine(const core::vector3df& start,
                const core::vector3df& end, irr::video::SColor color)
{
    if (!CVS->isGLSL()) {
        irr_driver->getVideoDriver()->draw3DLine(start, end, color);
        return;
    }

    float vertex[6] = {
        start.X, start.Y, start.Z,
        end.X, end.Y, end.Z
    };

    Shaders::ColoredLine *line = Shaders::ColoredLine::getInstance();
    line->bindVertexArray();
    line->bindBuffer();
    glBufferSubData(GL_ARRAY_BUFFER, 0, 6 * sizeof(float), vertex);

    line->use();
    line->setUniforms(color);
    glDrawArrays(GL_LINES, 0, 2);

    glGetError();
}

bool hasGLExtension(const char* extension) 
{
#if !defined(USE_GLES2)
    if (glGetStringi != NULL)
    {
        GLint numExtensions = 0;
        glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);
        for (GLint i = 0; i < numExtensions; i++)
        {
            const char* foundExtension =
                (const char*) glGetStringi(GL_EXTENSIONS, i);
            if (foundExtension && strcmp(foundExtension, extension) == 0)
            {
                return true;
            }
        }
    }
    else
#endif
    {
        const char* extensions = (const char*) glGetString(GL_EXTENSIONS);
        static std::vector<std::string> all_extensions;
        if (all_extensions.empty())
        {
            all_extensions = StringUtils::split(std::string(extensions), ' ');
        }
        for (unsigned i = 0; i < all_extensions.size(); i++)
        {
            if (all_extensions[i] == extension)
            {
                return true;
            }
        }
    }
    return false;
}   // hasGLExtension

// ----------------------------------------------------------------------------
/** Returns a space-separated list of all GL extensions. Used for hardware
 *  reporting.
 */
const std::string getGLExtensions()
{
    std::string result;
#if !defined(USE_GLES2)
    if (glGetStringi != NULL)
    {
        GLint num_extensions = 0;
        glGetIntegerv(GL_NUM_EXTENSIONS, &num_extensions);
        for (GLint i = 0; i < num_extensions; i++)
        {
            const char* extension = (const char*)glGetStringi(GL_EXTENSIONS, i);
            if(result.size()>0)
                result += " ";
            result += extension;
        }
    }
    else
#endif
    {
        const char* extensions = (const char*) glGetString(GL_EXTENSIONS);
        result = extensions;
    }

    return result;
}   // getGLExtensions

// ----------------------------------------------------------------------------
/** Executes glGetError and prints error to the console
 * \return True if error ocurred
 */
bool _checkGLError(const char * fn, int ln)
{
    GLenum err = glGetError();
    std::string nfo = std::string(fn) + ":" + std::to_string(ln);
    
    switch (err)
    {
    case GL_NO_ERROR:
        break;
    case GL_INVALID_ENUM:
        Log::warn(nfo.c_str(), "glGetError: GL_INVALID_ENUM");
        break;
    case GL_INVALID_VALUE:
        Log::warn(nfo.c_str(), "glGetError: GL_INVALID_VALUE");
        break;
    case GL_INVALID_OPERATION:
        Log::warn(nfo.c_str(), "glGetError: GL_INVALID_OPERATION");
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        Log::warn(nfo.c_str(), "glGetError: GL_INVALID_FRAMEBUFFER_OPERATION");
        break;
    case GL_OUT_OF_MEMORY:
        Log::warn(nfo.c_str(), "glGetError: GL_OUT_OF_MEMORY");
        break;
#if !defined(USE_GLES2)
    case GL_STACK_UNDERFLOW:
        Log::warn(nfo.c_str(), "glGetError: GL_STACK_UNDERFLOW");
        break;
    case GL_STACK_OVERFLOW:
        Log::warn(nfo.c_str(), "glGetError: GL_STACK_OVERFLOW");
        break;
#endif
    default:
        Log::warn(nfo.c_str(), "glGetError: %i", (int)err);
        break;
    }
    
    return err != GL_NO_ERROR;
}

#ifdef WIN32
// Tell system that it should use nvidia on optimus devices
extern "C" {
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
}
#endif

#endif   // !SERVER_ONLY


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

#include "IrrCompileConfig.h"

#include "CContextEGL.h"

#if defined(_IRR_POSIX_API_)

#include <cstring>
#include <string>
#include <vector>
#include <dlfcn.h>

#include "os.h"

using namespace irr;

struct EGL {
protected:
    static bool is_init, has_egl;
public:
    // EGL types
    typedef int32_t INT;
    typedef uint32_t UINT;
    typedef unsigned int ENUM;
    typedef unsigned int Boolean;
    typedef void *Display;
    typedef void *Config;
    typedef void *Surface;
    typedef void *Context;
    typedef void *NativeDisplayType;
    typedef void (*generic_func_ptr)(void);

    // EGL function types
    typedef generic_func_ptr (*GetProcAddress_t) (const char *);
    typedef Boolean (*BindAPI_t) (ENUM api);
    typedef Boolean (*ChooseConfig_t) (Display dpy, const INT *attrib_list, Config *configs, INT config_size, INT *num_config);
    typedef Context (*CreateContext_t) (Display dpy, Config config, Context share_context, const INT *attrib_list);
    typedef Surface (*CreatePbufferSurface_t) (Display dpy, Config config, const INT *attrib_list);
    typedef Boolean (*DestroyContext_t) (Display dpy, Context ctx);
    typedef Boolean (*DestroySurface_t) (Display dpy, Surface surface);
    typedef Display (*GetDisplay_t) (NativeDisplayType display_id);
    typedef INT (*GetError_t) (void);
    typedef Boolean (*Initialize_t) (Display dpy, INT *major, INT *minor);
    typedef Boolean (*MakeCurrent_t) (Display dpy, Surface draw, Surface read, Context ctx);
    typedef Display (*QueryDevices_t) (INT, void*, INT*);
    typedef const char *(*QueryString_t) (Display dpy, INT name);
    typedef Boolean (*ReleaseThread_t) (void);
    typedef Boolean (*SwapInterval_t) (Display dpy, INT interval);
    typedef Boolean (*Terminate_t) (Display dpy);

#define _APPLY_ALL_EGL(F) F(BindAPI)\
F(ChooseConfig)\
F(CreateContext)\
F(CreatePbufferSurface)\
F(DestroyContext)\
F(DestroySurface)\
F(GetDisplay)\
F(GetError)\
F(Initialize)\
F(MakeCurrent)\
F(QueryString)\
F(ReleaseThread)\
F(SwapInterval)\
F(Terminate)

    // EGL functions
    static GetProcAddress_t GetProcAddress;
#define _STATIC_DEC(x) static x##_t x;
    _APPLY_ALL_EGL(_STATIC_DEC);
#undef _STATIC_DEC

    // EGL constants
    enum {
        ALPHA_SIZE              = 0x3021,
        BAD_ACCESS              = 0x3002,
        BAD_ALLOC               = 0x3003,
        BAD_ATTRIBUTE           = 0x3004,
        BAD_CONFIG              = 0x3005,
        BAD_CONTEXT             = 0x3006,
        BAD_CURRENT_SURFACE     = 0x3007,
        BAD_DISPLAY             = 0x3008,
        BAD_MATCH               = 0x3009,
        BAD_NATIVE_PIXMAP       = 0x300A,
        BAD_NATIVE_WINDOW       = 0x300B,
        BAD_PARAMETER           = 0x300C,
        BAD_SURFACE             = 0x300D,
        BLUE_SIZE               = 0x3022,
        BUFFER_SIZE             = 0x3020,
        CONFIG_CAVEAT           = 0x3027,
        CONFIG_ID               = 0x3028,
        CORE_NATIVE_ENGINE      = 0x305B,
        DEPTH_SIZE              = 0x3025,
        DONT_CARE               = (INT)-1,
        DRAW                    = 0x3059,
        EXTENSIONS              = 0x3055,
        FALSE                   = 0,
        GREEN_SIZE              = 0x3023,
        HEIGHT                  = 0x3056,
        LARGEST_PBUFFER         = 0x3058,
        LEVEL                   = 0x3029,
        MAX_PBUFFER_HEIGHT      = 0x302A,
        MAX_PBUFFER_PIXELS      = 0x302B,
        MAX_PBUFFER_WIDTH       = 0x302C,
        NATIVE_RENDERABLE       = 0x302D,
        NATIVE_VISUAL_ID        = 0x302E,
        NATIVE_VISUAL_TYPE      = 0x302F,
        NONE                    = 0x3038,
        NON_CONFORMANT_CONFIG   = 0x3051,
        NOT_INITIALIZED         = 0x3001,
        PBUFFER_BIT             = 0x0001,
        PIXMAP_BIT              = 0x0002,
        READ                    = 0x305A,
        RED_SIZE                = 0x3024,
        SAMPLES                 = 0x3031,
        SAMPLE_BUFFERS          = 0x3032,
        SLOW_CONFIG             = 0x3050,
        STENCIL_SIZE            = 0x3026,
        SUCCESS                 = 0x3000,
        SURFACE_TYPE            = 0x3033,
        TRANSPARENT_BLUE_VALUE  = 0x3035,
        TRANSPARENT_GREEN_VALUE = 0x3036,
        TRANSPARENT_RED_VALUE   = 0x3037,
        TRANSPARENT_RGB         = 0x3052,
        TRANSPARENT_TYPE        = 0x3034,
        TRUE                    = 1,
        VENDOR                  = 0x3053,
        VERSION                 = 0x3054,
        WIDTH                   = 0x3057,
        WINDOW_BIT              = 0x0004,
        BACK_BUFFER             = 0x3084,
        BIND_TO_TEXTURE_RGB     = 0x3039,
        BIND_TO_TEXTURE_RGBA    = 0x303A,
        CONTEXT_LOST            = 0x300E,
        MIN_SWAP_INTERVAL       = 0x303B,
        MAX_SWAP_INTERVAL       = 0x303C,
        MIPMAP_TEXTURE          = 0x3082,
        MIPMAP_LEVEL            = 0x3083,
        NO_TEXTURE              = 0x305C,
        TEXTURE_2D              = 0x305F,
        TEXTURE_FORMAT          = 0x3080,
        TEXTURE_RGB             = 0x305D,
        TEXTURE_RGBA            = 0x305E,
        TEXTURE_TARGET          = 0x3081,
        ALPHA_FORMAT            = 0x3088,
        ALPHA_FORMAT_NONPRE     = 0x308B,
        ALPHA_FORMAT_PRE        = 0x308C,
        ALPHA_MASK_SIZE         = 0x303E,
        BUFFER_PRESERVED        = 0x3094,
        BUFFER_DESTROYED        = 0x3095,
        CLIENT_APIS             = 0x308D,
        COLORSPACE              = 0x3087,
        COLORSPACE_sRGB         = 0x3089,
        COLORSPACE_LINEAR       = 0x308A,
        COLOR_BUFFER_TYPE       = 0x303F,
        CONTEXT_CLIENT_TYPE     = 0x3097,
        DISPLAY_SCALING         = 10000,
        HORIZONTAL_RESOLUTION   = 0x3090,
        LUMINANCE_BUFFER        = 0x308F,
        LUMINANCE_SIZE          = 0x303D,
        OPENGL_ES_BIT           = 0x0001,
        OPENVG_BIT              = 0x0002,
        OPENGL_ES_API           = 0x30A0,
        OPENVG_API              = 0x30A1,
        OPENVG_IMAGE            = 0x3096,
        PIXEL_ASPECT_RATIO      = 0x3092,
        RENDERABLE_TYPE         = 0x3040,
        RENDER_BUFFER           = 0x3086,
        RGB_BUFFER              = 0x308E,
        SINGLE_BUFFER           = 0x3085,
        SWAP_BEHAVIOR           = 0x3093,
        UNKNOWN                 = (INT)-1,
        VERTICAL_RESOLUTION     = 0x3091,
        CONFORMANT              = 0x3042,
        CONTEXT_CLIENT_VERSION  = 0x3098,
        MATCH_NATIVE_PIXMAP     = 0x3041,
        OPENGL_ES2_BIT          = 0x0004,
        VG_ALPHA_FORMAT         = 0x3088,
        VG_ALPHA_FORMAT_NONPRE  = 0x308B,
        VG_ALPHA_FORMAT_PRE     = 0x308C,
        VG_ALPHA_FORMAT_PRE_BIT = 0x0040,
        VG_COLORSPACE           = 0x3087,
        VG_COLORSPACE_sRGB      = 0x3089,
        VG_COLORSPACE_LINEAR    = 0x308A,
        VG_COLORSPACE_LINEAR_BIT = 0x0020,
        MULTISAMPLE_RESOLVE_BOX_BIT = 0x0200,
        MULTISAMPLE_RESOLVE     = 0x3099,
        MULTISAMPLE_RESOLVE_DEFAULT = 0x309A,
        MULTISAMPLE_RESOLVE_BOX = 0x309B,
        OPENGL_API              = 0x30A2,
        OPENGL_BIT              = 0x0008,
        SWAP_BEHAVIOR_PRESERVED_BIT = 0x0400,

        CONTEXT_MAJOR_VERSION   = 0x3098,
        CONTEXT_MINOR_VERSION   = 0x30FB,
        GL_COLORSPACE           = 0x309D,
        GL_COLORSPACE_SRGB      = 0x3089,
        GL_COLORSPACE_LINEAR    = 0x308A,
        PLATFORM_DEVICE         = 0x313F,
        };
    static constexpr Context NO_CONTEXT = nullptr;
    static constexpr Display NO_DISPLAY = nullptr;
    static constexpr Surface NO_SURFACE = nullptr;
    static constexpr NativeDisplayType DEFAULT_DISPLAY = nullptr;

    static bool init();
};
bool EGL::is_init = false;
bool EGL::has_egl = false;
EGL::GetProcAddress_t EGL::GetProcAddress = nullptr;
#define _STATIC_DEF(x) EGL::x##_t EGL::x = nullptr;
_APPLY_ALL_EGL(_STATIC_DEF);
#undef _STATIC_DEF

bool EGL::init() {

    if (is_init) return has_egl;
    is_init = true;
    has_egl = false;

    void* handle = dlopen("libEGL.so", RTLD_LAZY);
    if (!handle) {
        // TODO: try fallback locations
    }
    if (!handle) {
        return false;
    }
    GetProcAddress = (GetProcAddress_t)dlsym(handle, "eglGetProcAddress");
    if (!GetProcAddress){
        dlclose(handle);
        return false;
    }
#define _LOAD(x) x = (x##_t)GetProcAddress("egl" #x); \
    if (!x) {                                         \
        dlclose(handle);                              \
        return false;                                 \
    }
    _APPLY_ALL_EGL(_LOAD);
#undef _LOAD

    return has_egl = true;
}


class ContextManagerEGL: public ContextManager
{
private:
    EGL::Display m_egl_display;
    EGL::Surface m_egl_surface;
    EGL::Context m_egl_context;
    EGL::Config m_egl_config;

    ContextParams m_creation_params;
    bool m_initialized;
    int m_egl_version;

    typedef EGL::Display (*QueryDevices_t) (EGL::INT, void*, EGL::INT*);
    QueryDevices_t QueryDevices;

    bool initExtensions();
    bool initDisplay();
    bool chooseConfig();
    bool createSurface();
    bool createContext();
    bool hasEGLExtension(const char* extension);
    bool checkEGLError();

public:
    ContextManagerEGL(const ContextParams& params);
    virtual ~ContextManagerEGL();

    virtual bool makeCurrent();

    bool init();
    void close();
};

ContextManagerEGL::ContextManagerEGL(const ContextParams& params): ContextManager(params), m_creation_params(params)
{
    m_egl_display = EGL::NO_DISPLAY;
    m_egl_surface = EGL::NO_SURFACE;
    m_egl_context = EGL::NO_CONTEXT;
    m_egl_config = 0;
    m_egl_version = 0;
    m_initialized = false;
    QueryDevices = NULL;
}


ContextManagerEGL::~ContextManagerEGL()
{
    close();
}


bool ContextManagerEGL::init()
{
    if (m_initialized)
        return false;

    bool success = initExtensions();

    if (!success)
    {
        os::Printer::log("Error: Could not initialize EGL extensions.\n");
        close();
        return false;
    }

    success = initDisplay();

    if (!success)
    {
        os::Printer::log("Error: Could not initialize EGL display.\n");
        close();
        return false;
    }

    if (!hasEGLExtension("EGL_KHR_create_context") && m_egl_version < 150)
    {
        os::Printer::log("Error: EGL version is too old.\n");
        close();
        return false;
    }
    EGL::BindAPI(EGL::OPENGL_API);

    success = chooseConfig();

    if (!success)
    {
        os::Printer::log("Error: Couldn't get EGL config.\n");
        close();
        return false;
    }

    success = createSurface();

    if (!success)
    {
        os::Printer::log("Error: Couldn't create EGL surface.\n");
        close();
        return false;
    }

    success = createContext();

    if (!success)
    {
        os::Printer::log("Error: Couldn't create OpenGL context.\n");
        close();
        return false;
    }

    success = EGL::MakeCurrent(m_egl_display, m_egl_surface, m_egl_surface, m_egl_context);

    if (!success)
    {
        checkEGLError();
        os::Printer::log("Error: Couldn't make context current for EGL display.\n");
        close();
        return false;
    }

    EGL::SwapInterval(m_egl_display, 0);

    m_initialized = true;
    return true;
}


bool ContextManagerEGL::initExtensions()
{
    if (hasEGLExtension("EGL_KHR_platform_base"))
    {
        QueryDevices = (QueryDevices_t)EGL::GetProcAddress("eglQueryDevices");
    }
    else if (hasEGLExtension("EGL_EXT_platform_base"))
    {
        QueryDevices = (QueryDevices_t)EGL::GetProcAddress("eglQueryDevicesEXT");
    }
    
    return true;
}


bool ContextManagerEGL::initDisplay()
{
    EGL::NativeDisplayType display = EGL::DEFAULT_DISPLAY;
    EGL::ENUM platform = EGL::PLATFORM_DEVICE;
    
    if (QueryDevices != NULL) {
        EGL::INT num_devices = 0;
        QueryDevices(0, NULL, &num_devices);
        std::vector<void*> devices(num_devices+1);
        QueryDevices(num_devices, devices.data(), &num_devices);
        if (m_creation_params.device_id < num_devices)
            display = (EGL::NativeDisplayType)devices[m_creation_params.device_id];
    }

    if (m_egl_display == EGL::NO_DISPLAY)
    {
        m_egl_display = EGL::GetDisplay(display);
    }

    if (m_egl_display == EGL::NO_DISPLAY && display != EGL::DEFAULT_DISPLAY)
    {
        m_egl_display = EGL::GetDisplay(EGL::DEFAULT_DISPLAY);
    }

    if (m_egl_display == EGL::NO_DISPLAY)
    {
        return false;
    }

    int version_major = 0;
    int version_minor = 0;

    bool success = EGL::Initialize(m_egl_display, &version_major, &version_minor);

    if (success)
    {
        m_egl_version = 100 * version_major + 10 * version_minor;
    }

    return success;
}


bool ContextManagerEGL::chooseConfig()
{
    std::vector<EGL::INT> config_attribs;
    config_attribs.push_back(EGL::RED_SIZE);
    config_attribs.push_back(8);
    config_attribs.push_back(EGL::GREEN_SIZE);
    config_attribs.push_back(8);
    config_attribs.push_back(EGL::BLUE_SIZE);
    config_attribs.push_back(8);
    config_attribs.push_back(EGL::ALPHA_SIZE);
    config_attribs.push_back(m_creation_params.with_alpha_channel ? 8 : 0);
    config_attribs.push_back(EGL::DEPTH_SIZE);
    config_attribs.push_back(16);
    // config_attribs.push_back(EGL::BUFFER_SIZE);
    // config_attribs.push_back(24);
    // config_attribs.push_back(EGL::STENCIL_SIZE);
    // config_attribs.push_back(stencil_buffer);
    // config_attribs.push_back(EGL::SAMPLE_BUFFERS);
    // config_attribs.push_back(antialias ? 1 : 0);
    // config_attribs.push_back(EGL::SAMPLES);
    // config_attribs.push_back(antialias);

    config_attribs.push_back(EGL::RENDERABLE_TYPE);
    config_attribs.push_back(EGL::OPENGL_BIT);
    config_attribs.push_back(EGL::SURFACE_TYPE);
    config_attribs.push_back(EGL::PBUFFER_BIT);
    config_attribs.push_back(EGL::NONE);
    config_attribs.push_back(0);

    EGL::INT num_configs = 0;

    bool success = EGL::ChooseConfig(m_egl_display, &config_attribs[0], &m_egl_config, 1, &num_configs);

    if (!success || m_egl_config == NULL || num_configs < 1)
    {
        config_attribs[1] = 5; //EGL::RED_SIZE
        config_attribs[3] = 6; //EGL::GREEN_SIZE
        config_attribs[5] = 5; //EGL::BLUE_SIZE
        config_attribs[7] = 0; //EGL::ALPHA_SIZE
        config_attribs[9] = 1; //EGL::DEPTH_SIZE
        
        success = EGL::ChooseConfig(m_egl_display, &config_attribs[0], &m_egl_config, 1, &num_configs);
    }

    if (!success || m_egl_config == NULL || num_configs < 1)
    {
        return false;
    }

    return true;
}


bool ContextManagerEGL::createSurface()
{
    unsigned int colorspace_attr_pos = 0;
    unsigned int largest_pbuffer_attr_pos = 0;
    
    std::vector<EGL::INT> attribs;

    {
        attribs.push_back(EGL::WIDTH);
        attribs.push_back(m_creation_params.pbuffer_width);
        attribs.push_back(EGL::HEIGHT);
        attribs.push_back(m_creation_params.pbuffer_height);
        attribs.push_back(EGL::LARGEST_PBUFFER);
        attribs.push_back(EGL::FALSE);
        largest_pbuffer_attr_pos = attribs.size() - 1;
    }
    
    attribs.push_back(EGL::NONE);
    attribs.push_back(0);
    
    if (m_egl_surface == EGL::NO_SURFACE)
    {
        m_egl_surface = EGL::CreatePbufferSurface(m_egl_display, m_egl_config, &attribs[0]);
    }
        
    if (m_egl_surface == EGL::NO_SURFACE && colorspace_attr_pos > 0)
    {
        attribs[colorspace_attr_pos] = EGL::GL_COLORSPACE_LINEAR;
        m_egl_surface = EGL::CreatePbufferSurface(m_egl_display, m_egl_config, &attribs[0]);
    }
    
    if (m_egl_surface == EGL::NO_SURFACE && largest_pbuffer_attr_pos > 0)
    {
        attribs[largest_pbuffer_attr_pos] = EGL::TRUE;
        m_egl_surface = EGL::CreatePbufferSurface(m_egl_display, m_egl_config, &attribs[0]);
    }

    return m_egl_surface != EGL::NO_SURFACE;
}


bool ContextManagerEGL::createContext()
{
    std::pair<int, int> versions[] = {{4,3}, {3,3}, {3,1}, {2,1}};
    for (auto v: versions) {
        if (m_egl_context == EGL::NO_CONTEXT)
        {
            std::vector<EGL::INT> context_attribs;
            context_attribs.push_back(EGL::CONTEXT_MAJOR_VERSION);
            context_attribs.push_back(v.first);
            context_attribs.push_back(EGL::CONTEXT_MINOR_VERSION);
            context_attribs.push_back(v.second);
            if (m_creation_params.debug) {
                context_attribs.push_back(0x30FC);
                context_attribs.push_back(1);
            }
            context_attribs.push_back(EGL::NONE);
            context_attribs.push_back(0);

            m_egl_context = EGL::CreateContext(m_egl_display, m_egl_config, EGL::NO_CONTEXT, &context_attribs[0]);
        }
    }
    return m_egl_context != EGL::NO_CONTEXT;
}


void ContextManagerEGL::close()
{
    if (m_egl_display != EGL::NO_DISPLAY)
    {
        EGL::MakeCurrent(m_egl_display, EGL::NO_SURFACE, EGL::NO_SURFACE, EGL::NO_CONTEXT);
    }

    if (m_egl_context != EGL::NO_CONTEXT)
    {
        EGL::DestroyContext(m_egl_display, m_egl_context);
        m_egl_context = EGL::NO_CONTEXT;
    }

    if (m_egl_surface != EGL::NO_SURFACE)
    {
        EGL::DestroySurface(m_egl_display, m_egl_surface);
        m_egl_surface = EGL::NO_SURFACE;
    }

    if (m_egl_display != EGL::NO_DISPLAY)
    {
        EGL::Terminate(m_egl_display);
        m_egl_display = EGL::NO_DISPLAY;
    }
    
    EGL::ReleaseThread();
}

bool ContextManagerEGL::makeCurrent()
{
    return EGL::MakeCurrent(m_egl_display, m_egl_surface, m_egl_surface, m_egl_context);
}

bool ContextManagerEGL::hasEGLExtension(const char* extension)
{
    const char* extensions = EGL::QueryString(m_egl_display, EGL::EXTENSIONS);
    return extensions && strstr(extensions, extension) != NULL;
}


bool ContextManagerEGL::checkEGLError()
{
    bool result = true;

    switch (EGL::GetError())
    {
        case EGL::SUCCESS:
            result = false;
            break;
        case EGL::NOT_INITIALIZED:
            os::Printer::log("Error: EGL::NOT_INITIALIZED\n");
            break;
        case EGL::BAD_ACCESS:
            os::Printer::log("Error: EGL::BAD_ACCESS\n");
            break;
        case EGL::BAD_ALLOC:
            os::Printer::log("Error: EGL::BAD_ALLOC\n");
            break;
        case EGL::BAD_ATTRIBUTE:
            os::Printer::log("Error: EGL::BAD_ATTRIBUTE\n");
            break;
        case EGL::BAD_CONTEXT:
            os::Printer::log("Error: EGL::BAD_CONTEXT\n");
            break;
        case EGL::BAD_CONFIG:
            os::Printer::log("Error: EGL::BAD_CONFIG\n");
            break;
        case EGL::BAD_CURRENT_SURFACE:
            os::Printer::log("Error: EGL::BAD_CURRENT_SURFACE\n");
            break;
        case EGL::BAD_DISPLAY:
            os::Printer::log("Error: EGL::BAD_DISPLAY\n");
            break;
        case EGL::BAD_SURFACE:
            os::Printer::log("Error: EGL::BAD_SURFACE\n");
            break;
        case EGL::BAD_MATCH:
            os::Printer::log("Error: EGL::BAD_MATCH\n");
            break;
        case EGL::BAD_PARAMETER:
            os::Printer::log("Error: EGL::BAD_PARAMETER\n");
            break;
        case EGL::BAD_NATIVE_PIXMAP:
            os::Printer::log("Error: EGL::BAD_NATIVE_PIXMAP\n");
            break;
        case EGL::BAD_NATIVE_WINDOW:
            os::Printer::log("Error: EGL::BAD_NATIVE_WINDOW\n");
            break;
        case EGL::CONTEXT_LOST:
            os::Printer::log("Error: EGL::CONTEXT_LOST\n");
            break;
        default:
            os::Printer::log("Error: Unknown EGL error.\n");
            break;
    };

    return result;
}

ContextManager * new_egl_context_manager(const ContextParams & params) {
    if (EGL::init()) {

    }
    ContextManagerEGL * manager = new ContextManagerEGL(params);
    if (!manager->init()) {
        delete manager;
        return nullptr;
    }
    return manager;
}
#else
ContextManager * new_egl_context_manager(const ContextParams & params) {
    return nullptr;
}
#endif

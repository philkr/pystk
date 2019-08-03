// Copyright (C) 2002-2012 Nikolaus Gebhardt
// Copyright (C) 2014-2015 Dawid Gan
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

extern bool GLContextDebugBit;

#include "CIrrDeviceOffScreen.h"

#ifdef _IRR_COMPILE_WITH_OFF_SCREEN_DEVICE_

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <time.h>
#include <locale.h>
#include "IEventReceiver.h"
#include "ISceneManager.h"
#include "IGUIEnvironment.h"
#include "os.h"
#include "CTimer.h"
#include "irrString.h"
#include "Keycodes.h"
#include "CContextEGL.h"
#include "COSOperator.h"
#include "CColorConverter.h"
#include "SIrrCreationParameters.h"
#include "IGUISpriteBank.h"


namespace irr
{
    namespace video
    {
        extern bool useCoreContext;
        IVideoDriver* createOpenGLDriver(const SIrrlichtCreationParameters& params,
                io::IFileSystem* io, CIrrDeviceOffScreen* device);
        IVideoDriver* createOGLES2Driver(const SIrrlichtCreationParameters& params,
            video::SExposedVideoData& data, io::IFileSystem* io);
    }
} // end namespace irr

namespace irr
{

//! Implementation of the linux cursor control
class DummyCursorControl : public gui::ICursorControl
{
public:

    DummyCursorControl(): IsVisible(true) {
    }
    virtual void setVisible(bool visible) {
        IsVisible = visible;
    }
    virtual bool isVisible() const {
        return IsVisible;
    }
    virtual void setPosition(const core::position2d<f32> &pos) {
        setPosition(pos.X, pos.Y);
    }
    virtual void setPosition(f32 x, f32 y) {
        setPosition((s32)(x), (s32)(y));
    }
    virtual void setPosition(const core::position2d<s32> &pos) {
        setPosition(pos.X, pos.Y);
    }
    virtual void setPosition(s32 x, s32 y) {
        CursorPos.X = x;
        CursorPos.Y = y;
    }
    virtual const core::position2d<s32>& getPosition() {
        return CursorPos;
    }
    virtual core::position2d<f32> getRelativePosition()
    {
        return core::position2d<f32>(0, 0);
    }

    virtual void setReferenceRect(core::rect<s32>* rect=0) { }

private:
    core::position2d<s32> CursorPos;
    bool IsVisible;
};

//! constructor
CIrrDeviceOffScreen::CIrrDeviceOffScreen(const SIrrlichtCreationParameters& params)
 : CIrrDeviceStub(params), m_egl_context(0)
{
    // create cursor control
    CursorControl = new DummyCursorControl();

    bool success = initEGL();
    if (!success)
        return;
    
    // create driver
    createDriver();

    if (!VideoDriver)
        return;

    createGUIAndScene();
}



//! destructor
CIrrDeviceOffScreen::~CIrrDeviceOffScreen()
{
    delete m_egl_context;
}


bool CIrrDeviceOffScreen::initEGL()
{
    m_egl_context = new ContextManagerEGL();

    ContextEGLParams egl_params;

    if (CreationParams.DriverType == video::EDT_OGLES2)
    {
        egl_params.opengl_api = CEGL_API_OPENGL_ES;
    }
    else
    {
        egl_params.opengl_api = CEGL_API_OPENGL;
    }

    egl_params.surface_type = CEGL_SURFACE_PBUFFER;
    egl_params.pbuffer_width = CreationParams.WindowSize.Width;
    egl_params.pbuffer_height = CreationParams.WindowSize.Height;
    egl_params.force_legacy_device = CreationParams.ForceLegacyDevice;
    egl_params.handle_srgb = CreationParams.HandleSRGB;
    egl_params.with_alpha_channel = CreationParams.WithAlphaChannel;
    egl_params.vsync_enabled = CreationParams.Vsync;
    egl_params.platform = CEGL_PLATFORM_DEVICE;
    egl_params.device_id = 0;
    if (getenv("EGL_DEVICE"))
        egl_params.device_id = atoi(getenv("EGL_DEVICE"));
#ifdef NDEBUG
    egl_params.debug = true;
#else
    egl_params.debug = true;
#endif

    bool success = m_egl_context->init(egl_params);

    if (!success)
        return false;
    return true;
}

//! create the driver
void CIrrDeviceOffScreen::createDriver()
{
    switch(CreationParams.DriverType)
    {
    case video::EDT_OPENGL:
        #ifdef _IRR_COMPILE_WITH_OPENGL_
        VideoDriver = video::createOpenGLDriver(CreationParams, FileSystem, this);
        #else
        os::Printer::log("No OpenGL support compiled in.", ELL_ERROR);
        #endif
        break;
    case video::EDT_OGLES2:
        #ifdef _IRR_COMPILE_WITH_OGLES2_
        VideoDriver = video::createOGLES2Driver(CreationParams, FileSystem, this);
        #else
        os::Printer::log("No OpenGL ES 2.0 support compiled in.", ELL_ERROR);
        #endif
        break;
    default:
        VideoDriver = video::createNullDriver(FileSystem, CreationParams.WindowSize);
        break;
    }
}


//! runs the device. Returns false if device wants to be deleted
bool CIrrDeviceOffScreen::run()
{
    os::Timer::tick();
    return !Close;
}


//! Pause the current process for the minimum time allowed only to allow other processes to execute
void CIrrDeviceOffScreen::yield()
{
    struct timespec ts = {0,0};
    nanosleep(&ts, NULL);
}


//! Pause execution and let other processes to run for a specified amount of time.
void CIrrDeviceOffScreen::sleep(u32 timeMs, bool pauseTimer=false)
{
    bool wasStopped = Timer ? Timer->isStopped() : true;

    struct timespec ts;
    ts.tv_sec = (time_t) (timeMs / 1000);
    ts.tv_nsec = (long) (timeMs % 1000) * 1000000;

    if (pauseTimer && !wasStopped)
        Timer->stop();

    nanosleep(&ts, NULL);

    if (pauseTimer && !wasStopped)
        Timer->start();
}


//! presents a surface in the client area
bool CIrrDeviceOffScreen::present(video::IImage* image, void* windowId, core::rect<s32>* src )
{
    return true;
}


//! notifies the device that it should close itself
void CIrrDeviceOffScreen::closeDevice()
{
    Close = true;
}


//! returns if window is active. if not, nothing need to be drawn
bool CIrrDeviceOffScreen::isWindowActive() const
{
    return true;
}


//! returns if window has focus
bool CIrrDeviceOffScreen::isWindowFocused() const
{
    return true;
}


//! returns if window is minimized
bool CIrrDeviceOffScreen::isWindowMinimized() const
{
    return false;
}


//! sets the caption of the window
void CIrrDeviceOffScreen::setWindowCaption(const wchar_t* text)
{
}


//! Sets if the window should be resizeable in windowed mode.
void CIrrDeviceOffScreen::setResizable(bool resize)
{
}


//! Minimizes window
void CIrrDeviceOffScreen::minimizeWindow()
{
}


//! Maximizes window
void CIrrDeviceOffScreen::maximizeWindow()
{
}


//! Restores original window size
void CIrrDeviceOffScreen::restoreWindow()
{
}


//! Returns the type of this device
E_DEVICE_TYPE CIrrDeviceOffScreen::getType() const
{
    return EIDT_OFFSCREEN;
}


} // end namespace

#endif // _IRR_COMPILE_WITH_OFF_SCREEN_DEVICE_


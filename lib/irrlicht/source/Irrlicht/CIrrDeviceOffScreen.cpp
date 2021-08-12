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
#include "os.h"
#include "CTimer.h"
#include "irrString.h"
#include "Keycodes.h"
#include "CContextEGL.h"
#include "COSOperator.h"
#include "CColorConverter.h"
#include "SIrrCreationParameters.h"


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

//! constructor
CIrrDeviceOffScreen::CIrrDeviceOffScreen(const SIrrlichtCreationParameters& params)
 : CIrrDeviceStub(params), m_egl_context(0)
{
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

    egl_params.surface_type = CEGL_SURFACE_PBUFFER;
    // TODO: FIX ME
//    egl_params.pbuffer_width = CreationParams.WindowSize.Width;
//    egl_params.pbuffer_height = CreationParams.WindowSize.Height
    egl_params.platform = CEGL_PLATFORM_DEVICE;
    egl_params.device_id = CreationParams.DisplayAdapter;
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
    VideoDriver = video::createOpenGLDriver(CreationParams, FileSystem, this);
}


//! runs the device. Returns false if device wants to be deleted
bool CIrrDeviceOffScreen::run()
{
    os::Timer::tick();
    return !Close;
}


//! notifies the device that it should close itself
void CIrrDeviceOffScreen::closeDevice()
{
    Close = true;
}

} // end namespace

#endif // _IRR_COMPILE_WITH_OFF_SCREEN_DEVICE_


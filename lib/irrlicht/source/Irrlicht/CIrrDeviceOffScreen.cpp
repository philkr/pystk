// Copyright (C) 2002-2012 Nikolaus Gebhardt
// Copyright (C) 2014-2015 Dawid Gan
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

extern bool GLContextDebugBit;

#include "CIrrDeviceOffScreen.h"

#ifdef _IRR_COMPILE_WITH_OFF_SCREEN_DEVICE_

#include <stdlib.h>
#include "ISceneManager.h"
#include "os.h"
#include "irrString.h"
#include "CContextEGL.h"
#include "SIrrCreationParameters.h"


namespace irr
{
    namespace video
    {
        extern bool useCoreContext;
        IVideoDriver* createOpenGLDriver(const SIrrlichtCreationParameters& params,
                io::IFileSystem* io, CIrrDeviceOffScreen* device);
    }
} // end namespace irr

namespace irr
{

//! constructor
CIrrDeviceOffScreen::CIrrDeviceOffScreen(const SIrrlichtCreationParameters& params)
 : CIrrDeviceStub(params), m_context(0)
{
    bool success = initContext();
    if (!success) {
        os::Printer::log("CIrrDeviceOffScreen failed to create OpenGL context. Consider using a NO_GRAPHICS build.", ELL_ERROR);
        return;
    }
    
    // create driver
    createDriver();

    if (!VideoDriver)
        return;

    createGUIAndScene();
}



//! destructor
CIrrDeviceOffScreen::~CIrrDeviceOffScreen()
{
    delete m_context;
}


bool CIrrDeviceOffScreen::initContext()
{
    ContextParams ctx_params;

    // TODO: FIX ME
//    egl_params.pbuffer_width = CreationParams.WindowSize.Width;
//    egl_params.pbuffer_height = CreationParams.WindowSize.Height
ctx_params.device_id = CreationParams.DisplayAdapter;
    if (getenv("EGL_DEVICE"))
        ctx_params.device_id = atoi(getenv("EGL_DEVICE"));
#ifdef NDEBUG
    ctx_params.debug = true;
#else
    egl_params.debug = true;
#endif
    m_context = new_egl_context_manager(ctx_params);
    if (!m_context)
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


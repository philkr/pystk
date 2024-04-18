// Copyright (C) 2002-2012 Nikolaus Gebhardt
// Copyright (C) 2014-2015 Dawid Gan
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

extern bool GLContextDebugBit;

#include "CIrrDeviceOffScreenMacOSX.h"

#ifdef _IRR_COMPILE_WITH_OFF_SCREEN_OSX_DEVICE_

#define GL_SILENCE_DEPRECATION

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
#include "CColorConverter.h"
#include "SIrrCreationParameters.h"

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>


namespace irr
{
	namespace video
	{
		extern bool useCoreContext;
		IVideoDriver* createOpenGLDriver(const SIrrlichtCreationParameters& params,
				io::IFileSystem* io, CIrrDeviceOffScreenMacOSX* device);
	}
} // end namespace irr

namespace irr
{

class ContextManagerCGL {
protected:
	CGLContextObj context_ = 0;
public:
	ContextManagerCGL() {
	}
	~ContextManagerCGL() {
		close();
	}
	bool init() {
		CGLPixelFormatAttribute attributes[] = {
    	  kCGLPFAAccelerated,
		  kCGLPFAOpenGLProfile, (CGLPixelFormatAttribute) kCGLOGLPVersion_3_2_Core,
		  kCGLPFAColorSize, (CGLPixelFormatAttribute)24,
    	  kCGLPFADepthSize, (CGLPixelFormatAttribute)16,
    	  kCGLPFAAlphaSize, (CGLPixelFormatAttribute)8,
    	  (CGLPixelFormatAttribute)0
		};
		
		CGLPixelFormatObj pxlfmt;
		GLint numPixelFormats;
 
		if (CGLError e = CGLChoosePixelFormat (attributes, &pxlfmt, &numPixelFormats)) {
			os::Printer::log("Error: Couldn't create Pixel Format.");
			os::Printer::log(CGLErrorString(e));
 			CGLDestroyPixelFormat(pxlfmt);
 			return false;
		}
 		
 		if (CGLError e = CGLCreateContext(pxlfmt, nullptr, &context_)) {
			os::Printer::log("Error: Couldn't create CGL context.");
			os::Printer::log(CGLErrorString(e));
 			CGLDestroyPixelFormat(pxlfmt);
 			return false;
		}
 		CGLDestroyPixelFormat(pxlfmt);
 		
		makeCurrent();
		return true;
	}
    void close() {
		if (context_) {
			CGLSetCurrentContext( NULL );
			CGLDestroyContext( context_ );
			context_ = 0;
		}
    }

    bool makeCurrent() {
	    return !CGLSetCurrentContext( context_ );
    }
};



//! constructor
CIrrDeviceOffScreenMacOSX::CIrrDeviceOffScreenMacOSX(const SIrrlichtCreationParameters& params)
 : CIrrDeviceStub(params), m_cgl_context(0)
{
	bool success = initCGL();
	if (!success)
		return;
	
	// create driver
	createDriver();

	if (!VideoDriver)
		return;

	createGUIAndScene();
}



//! destructor
CIrrDeviceOffScreenMacOSX::~CIrrDeviceOffScreenMacOSX()
{
	if (m_cgl_context)
		delete m_cgl_context;
}

bool CIrrDeviceOffScreenMacOSX::initCGL()
{
    m_cgl_context = new ContextManagerCGL();

    bool success = m_cgl_context->init();

    if (!success)
        return false;
	return true;
}

//! create the driver
void CIrrDeviceOffScreenMacOSX::createDriver()
{
    #ifdef _IRR_COMPILE_WITH_OPENGL_
    VideoDriver = video::createOpenGLDriver(CreationParams, FileSystem, this);
    #else
    os::Printer::log("No OpenGL support compiled in.", ELL_ERROR);
    #endif
}


bool CIrrDeviceOffScreenMacOSX::makeCurrent() {
	if (m_cgl_context) return m_cgl_context->makeCurrent();
	return false;
}
//! runs the device. Returns false if device wants to be deleted
bool CIrrDeviceOffScreenMacOSX::run()
{
	os::Timer::tick();
	return !Close;
}

//! notifies the device that it should close itself
void CIrrDeviceOffScreenMacOSX::closeDevice()
{
	Close = true;
}

} // end namespace

#endif // _IRR_COMPILE_WITH_OFF_SCREEN_OSX_DEVICE_


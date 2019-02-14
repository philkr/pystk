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

//! Implementation of the linux cursor control
class DummyCursorControlMac : public gui::ICursorControl
{
public:

	DummyCursorControlMac(): IsVisible(true) {
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

class ContextManagerCGL {
protected:
	CGLContextObj context_ = 0;
public:
	ContextManagerCGL() {
	}
	~ContextManagerCGL() {
		close();
	}
	bool init(int width, int height, bool srgb, bool alpha) {
		CGLPixelFormatAttribute attributes[] = {
    	  kCGLPFAAccelerated,
		  kCGLPFAOpenGLProfile, (CGLPixelFormatAttribute) kCGLOGLPVersion_3_2_Core,
		  kCGLPFAColorSize, (CGLPixelFormatAttribute)24,
    	  kCGLPFADepthSize, (CGLPixelFormatAttribute)16,
    	  kCGLPFAAlphaSize, alpha ? (CGLPixelFormatAttribute)8 : (CGLPixelFormatAttribute)1,
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
	// create cursor control
	CursorControl = new DummyCursorControlMac();

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

    bool success = m_cgl_context->init(CreationParams.WindowSize.Width, CreationParams.WindowSize.Height, CreationParams.HandleSRGB, CreationParams.WithAlphaChannel);

    if (!success)
        return false;
	return true;
}

//! create the driver
void CIrrDeviceOffScreenMacOSX::createDriver()
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
	default:
		VideoDriver = video::createNullDriver(FileSystem, CreationParams.WindowSize);
		break;
	}
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


//! Pause the current process for the minimum time allowed only to allow other processes to execute
void CIrrDeviceOffScreenMacOSX::yield()
{
	struct timespec ts = {0,0};
	nanosleep(&ts, NULL);
}


//! Pause execution and let other processes to run for a specified amount of time.
void CIrrDeviceOffScreenMacOSX::sleep(u32 timeMs, bool pauseTimer=false)
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
bool CIrrDeviceOffScreenMacOSX::present(video::IImage* image, void* windowId, core::rect<s32>* src )
{
	return true;
}


//! notifies the device that it should close itself
void CIrrDeviceOffScreenMacOSX::closeDevice()
{
	Close = true;
}


//! returns if window is active. if not, nothing need to be drawn
bool CIrrDeviceOffScreenMacOSX::isWindowActive() const
{
	return true;
}


//! returns if window has focus
bool CIrrDeviceOffScreenMacOSX::isWindowFocused() const
{
	return true;
}


//! returns if window is minimized
bool CIrrDeviceOffScreenMacOSX::isWindowMinimized() const
{
	return false;
}


//! sets the caption of the window
void CIrrDeviceOffScreenMacOSX::setWindowCaption(const wchar_t* text)
{
}


//! Sets if the window should be resizeable in windowed mode.
void CIrrDeviceOffScreenMacOSX::setResizable(bool resize)
{
}


//! Minimizes window
void CIrrDeviceOffScreenMacOSX::minimizeWindow()
{
}


//! Maximizes window
void CIrrDeviceOffScreenMacOSX::maximizeWindow()
{
}


//! Restores original window size
void CIrrDeviceOffScreenMacOSX::restoreWindow()
{
}


//! Returns the type of this device
E_DEVICE_TYPE CIrrDeviceOffScreenMacOSX::getType() const
{
	return EIDT_OFFSCREEN;
}


} // end namespace

#endif // _IRR_COMPILE_WITH_OFF_SCREEN_OSX_DEVICE_


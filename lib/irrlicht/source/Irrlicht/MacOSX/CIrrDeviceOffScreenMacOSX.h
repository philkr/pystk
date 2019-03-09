// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_IRR_DEVICE_OFF_SCREEN_MACOSX_H_INCLUDED__
#define __C_IRR_DEVICE_OFF_SCREEN_MACOSX_H_INCLUDED__

#include "IrrCompileConfig.h"

#ifdef _IRR_COMPILE_WITH_OFF_SCREEN_OSX_DEVICE_

#include "CIrrDeviceStub.h"
#include "IrrlichtDevice.h"
#include "IImagePresenter.h"
#include "ICursorControl.h"
#include "os.h"

namespace irr
{
	
	class ContextManagerCGL;
	class CIrrDeviceOffScreenMacOSX : public CIrrDeviceStub, public video::IImagePresenter
	{
	public:

		//! constructor
		CIrrDeviceOffScreenMacOSX(const SIrrlichtCreationParameters& param);

		//! destructor
		virtual ~CIrrDeviceOffScreenMacOSX();//! runs the device. Returns false if device wants to be deleted
		virtual bool run() _IRR_OVERRIDE_;

		//! Cause the device to temporarily pause execution and let other processes to run
		// This should bring down processor usage without major performance loss for Irrlicht
		virtual void yield() _IRR_OVERRIDE_;

		//! Pause execution and let other processes to run for a specified amount of time.
		virtual void sleep(u32 timeMs, bool pauseTimer) _IRR_OVERRIDE_;

		//! sets the caption of the window
		virtual void setWindowCaption(const wchar_t* text) _IRR_OVERRIDE_;

		//! returns if window is active. if not, nothing need to be drawn
		virtual bool isWindowActive() const _IRR_OVERRIDE_;

		//! returns if window has focus
		virtual bool isWindowFocused() const _IRR_OVERRIDE_;

		//! returns if window is minimized
		virtual bool isWindowMinimized() const _IRR_OVERRIDE_;

		//! Minimizes window
		virtual void minimizeWindow() _IRR_OVERRIDE_;

		//! Maximizes window
		virtual void maximizeWindow() _IRR_OVERRIDE_;

		//! Restores original window size
		virtual void restoreWindow() _IRR_OVERRIDE_;

		virtual void setWindowClass(const char* text) _IRR_OVERRIDE_ {}
		
		//! Move window to requested position
		virtual bool moveWindow(int x, int y) _IRR_OVERRIDE_ {return false;}

		//! Get current window position.
		virtual bool getWindowPosition(int* x, int* y) _IRR_OVERRIDE_ {return *x = *y = 0;}

		//! presents a surface in the client area
		virtual bool present(video::IImage* surface, void* windowId = 0, core::rect<s32>* src=0 ) _IRR_OVERRIDE_;

		//! notifies the device that it should close itself
		virtual void closeDevice() _IRR_OVERRIDE_;

		//! Sets if the window should be resizeable in windowed mode.
		virtual void setResizable(bool resize=false) _IRR_OVERRIDE_;

		//! Returns the type of this device
		virtual E_DEVICE_TYPE getType() const _IRR_OVERRIDE_;
		
		bool makeCurrent();
	private:

		//! create the driver
		void createDriver();
		
		bool initCGL();
		
		ContextManagerCGL * m_cgl_context;
	};


} // end namespace irr

#endif // _IRR_COMPILE_WITH_OFF_SCREEN_OSX_DEVICE_
#endif // __C_IRR_DEVICE_OFF_SCREEN_MACOSX_H_INCLUDED__


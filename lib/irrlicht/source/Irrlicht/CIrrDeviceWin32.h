// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_IRR_DEVICE_WIN32_H_INCLUDED__
#define __C_IRR_DEVICE_WIN32_H_INCLUDED__

#include "IrrCompileConfig.h"
#ifdef _IRR_COMPILE_WITH_WINDOWS_DEVICE_

#include "CIrrDeviceStub.h"
#include "IrrlichtDevice.h"

#define WIN32_LEAN_AND_MEAN
#if !defined(_IRR_XBOX_PLATFORM_)
	#include <windows.h>
	#include <mmsystem.h> // For JOYCAPS
	#include <windowsx.h>
#endif
#if !defined(GET_X_LPARAM)
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
#endif

namespace irr
{
	struct SJoystickWin32Control;

	class CIrrDeviceWin32 : public CIrrDeviceStub
	{
	friend struct SJoystickWin32Control;
	public:

		//! constructor
		CIrrDeviceWin32(const SIrrlichtCreationParameters& params, bool offscreen = false);

		//! destructor
		virtual ~CIrrDeviceWin32();

		//! runs the device. Returns false if device wants to be deleted
		virtual bool run();

		//! Cause the device to temporarily pause execution and let other processes to run
		// This should bring down processor usage without major performance loss for Irrlicht
		virtual void yield();

		//! Pause execution and let other processes to run for a specified amount of time.
		virtual void sleep(u32 timeMs, bool pauseTimer);

		//! sets the caption of the window
		virtual void setWindowCaption(const wchar_t* text);

		//! sets the class of the window
		virtual void setWindowClass(const char* text) {}

		//! returns if window is active. if not, nothing need to be drawn
		virtual bool isWindowActive() const;

		//! returns if window has focus
		virtual bool isWindowFocused() const;

		//! returns if window is minimized
		virtual bool isWindowMinimized() const;

		//! presents a surface in the client area
		virtual bool present(video::IImage* surface, void* windowId=0, core::rect<s32>* src=0);

		//! notifies the device that it should close itself
		virtual void closeDevice();

		//! \return Returns a pointer to a list with all video modes
		//! supported by the gfx adapter.
		video::IVideoModeList* getVideoModeList();

		//! Notifies the device, that it has been resized
		void OnResized();

		//! Sets if the window should be resizable in windowed mode.
		virtual void setResizable(bool resize=false);

		//! Minimizes the window.
		virtual void minimizeWindow();

		//! Maximizes the window.
		virtual void maximizeWindow();

		//! Restores the window size.
		virtual void restoreWindow();
		
		//! Move window to requested position
		virtual bool moveWindow(int x, int y);

		//! Get current window position.
		virtual bool getWindowPosition(int* x, int* y);

		//! Activate any joysticks, and generate events for them.
		virtual bool activateJoysticks(core::array<SJoystickInfo> & joystickInfo);

		//! Set the current Gamma Value for the Display
		virtual bool setGammaRamp( f32 red, f32 green, f32 blue, f32 brightness, f32 contrast );

		//! Get the current Gamma Value for the Display
		virtual bool getGammaRamp( f32 &red, f32 &green, f32 &blue, f32 &brightness, f32 &contrast );

		//! Remove all messages pending in the system message loop
		virtual void clearSystemMessages();

		//! Get the device type
		virtual E_DEVICE_TYPE getType() const
		{
				return EIDT_WIN32;
		}

		//! Compares to the last call of this function to return double and triple clicks.
		//! \return Returns only 1,2 or 3. A 4th click will start with 1 again.
		virtual u32 checkSuccessiveClicks(s32 mouseX, s32 mouseY, EMOUSE_INPUT_EVENT inputEvent )
		{
			// we just have to make it public
			return CIrrDeviceStub::checkSuccessiveClicks(mouseX, mouseY, inputEvent );
		}

		//! switchs to fullscreen
		bool switchToFullScreen(bool reset=false);

		//! Check for and show last Windows API error to help internal debugging.
		//! Does call GetLastError and on errors formats the errortext and displays it in a messagebox.
		static void ReportLastWinApiError();

		// convert an Irrlicht texture to a windows cursor
		HCURSOR TextureToCursor(HWND hwnd, irr::video::ITexture * tex, const core::rect<s32>& sourceRect, const core::position2d<s32> &hotspot);

		HWND getHandle() const { return HWnd; }

		bool isIMEComposingStarted() const { return m_ime_composing_started; }

		void setIMEComposingStarted(bool started) { m_ime_composing_started = started; }

	private:

		//! create the driver
		void createDriver();

		//! Process system events
		void handleSystemMessages();

		void getWindowsVersion(core::stringc& version);

		void resizeIfNecessary();

		bool m_ime_composing_started;
		HWND HWnd;

		bool ChangedToFullScreen;
		bool Resized;
		bool offscreen;
		bool ExternalWindow;
		CCursorControl* Win32CursorControl;
		DEVMODE DesktopMode;

		SJoystickWin32Control* JoyControl;
	};

} // end namespace irr

#endif // _IRR_COMPILE_WITH_WINDOWS_DEVICE_
#endif // __C_IRR_DEVICE_WIN32_H_INCLUDED__

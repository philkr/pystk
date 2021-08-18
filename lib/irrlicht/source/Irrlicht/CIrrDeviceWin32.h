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
	#include <windowsx.h>
#endif
#if !defined(GET_X_LPARAM)
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
#endif

namespace irr
{
	class CIrrDeviceWin32 : public CIrrDeviceStub
	{
	public:

		//! constructor
		CIrrDeviceWin32(const SIrrlichtCreationParameters& params);

		//! destructor
		virtual ~CIrrDeviceWin32();

		//! Active the current rendering context
		virtual bool makeCurrent();

		//! runs the device. Returns false if device wants to be deleted
		virtual bool run();

		//! notifies the device that it should close itself
		virtual void closeDevice();

		//! Remove all messages pending in the system message loop
		virtual void clearSystemMessages();

		//! Check for and show last Windows API error to help internal debugging.
		//! Does call GetLastError and on errors formats the errortext and displays it in a messagebox.
		static void ReportLastWinApiError();

		HWND getHandle() const { return HWnd; }
	private:

		//! create the driver
		void createDriver();

		//! Process system events
		void handleSystemMessages();

		HWND HWnd;
		HDC HDc;
		HGLRC HRc;
	};

} // end namespace irr

#endif // _IRR_COMPILE_WITH_WINDOWS_DEVICE_
#endif // __C_IRR_DEVICE_WIN32_H_INCLUDED__

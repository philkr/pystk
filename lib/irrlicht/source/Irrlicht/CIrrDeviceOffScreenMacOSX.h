// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_IRR_DEVICE_OFF_SCREEN_MACOSX_H_INCLUDED__
#define __C_IRR_DEVICE_OFF_SCREEN_MACOSX_H_INCLUDED__

#include "IrrCompileConfig.h"

#ifdef _IRR_COMPILE_WITH_OFF_SCREEN_OSX_DEVICE_

#include "CIrrDeviceStub.h"
#include "IrrlichtDevice.h"
#include "os.h"

namespace irr
{
	
	class ContextManagerCGL;
	class CIrrDeviceOffScreenMacOSX : public CIrrDeviceStub
	{
	public:

		//! constructor
		CIrrDeviceOffScreenMacOSX(const SIrrlichtCreationParameters& param);

		//! destructor
		virtual ~CIrrDeviceOffScreenMacOSX();//! runs the device. Returns false if device wants to be deleted
		virtual bool run() _IRR_OVERRIDE_;

		//! notifies the device that it should close itself
		virtual void closeDevice() _IRR_OVERRIDE_;

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


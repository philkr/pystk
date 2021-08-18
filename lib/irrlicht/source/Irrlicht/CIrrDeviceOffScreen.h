// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_IRR_DEVICE_OFF_SCREEN_H_INCLUDED__
#define __C_IRR_DEVICE_OFF_SCREEN_H_INCLUDED__

#include "IrrCompileConfig.h"

#ifdef _IRR_COMPILE_WITH_OFF_SCREEN_DEVICE_

#include "CIrrDeviceStub.h"
#include "IrrlichtDevice.h"
#include "os.h"

class ContextManager;
namespace irr
{
	
	class CIrrDeviceOffScreen : public CIrrDeviceStub
	{
	public:

		//! constructor
		CIrrDeviceOffScreen(const SIrrlichtCreationParameters& param);

		//! destructor
		virtual ~CIrrDeviceOffScreen();//! runs the device. Returns false if device wants to be deleted
		virtual bool run() _IRR_OVERRIDE_;

		//! notifies the device that it should close itself
		virtual void closeDevice() _IRR_OVERRIDE_;
		
		ContextManager* getContext() {return m_context;}

	private:

		//! create the driver
		void createDriver();
		
		bool initContext();
		
		ContextManager * m_context;
	};


} // end namespace irr

#endif // _IRR_COMPILE_WITH_OFF_SCREEN_DEVICE_
#endif // __C_IRR_DEVICE_OFF_SCREEN_H_INCLUDED__


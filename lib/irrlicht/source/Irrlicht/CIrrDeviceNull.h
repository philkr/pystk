// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_IRR_DEVICE_NULL_H_INCLUDED__
#define __C_IRR_DEVICE_NULL_H_INCLUDED__

#include "IrrCompileConfig.h"

#include "CIrrDeviceStub.h"
#include "IrrlichtDevice.h"
#include "os.h"

class ContextManagerEGL;
namespace irr
{
	
	class CIrrDeviceNull : public CIrrDeviceStub
	{
	public:

		//! constructor
		CIrrDeviceNull(const SIrrlichtCreationParameters& param);

		//! destructor
		virtual ~CIrrDeviceNull();//! runs the device. Returns false if device wants to be deleted
		virtual bool run() _IRR_OVERRIDE_;

		//! notifies the device that it should close itself
		virtual void closeDevice() _IRR_OVERRIDE_;

	private:

		//! create the driver
		void createDriver();
	};


} // end namespace irr

#endif // __C_IRR_DEVICE_NULL_H_INCLUDED__


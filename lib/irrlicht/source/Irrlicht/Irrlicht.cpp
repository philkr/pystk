// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "IrrCompileConfig.h"

//static const char* const copyright = "Irrlicht Engine (c) 2002-2012 Nikolaus Gebhardt";

#ifdef _IRR_WINDOWS_
	#include <windows.h>
	#if defined(_DEBUG) && !defined(__GNUWIN32__) && !defined(_WIN32_WCE)
		#include <crtdbg.h>
	#endif // _DEBUG
#endif

#include "irrlicht.h"
#include "CIrrDeviceNull.h"

#ifdef _IRR_COMPILE_WITH_WINDOWS_DEVICE_
#include "CIrrDeviceWin32.h"
#endif

#ifdef _IRR_COMPILE_WITH_OFF_SCREEN_DEVICE_
#include "CIrrDeviceOffScreen.h"
#endif

#ifdef _IRR_COMPILE_WITH_OFF_SCREEN_OSX_DEVICE_
#include "CIrrDeviceOffScreenMacOSX.h"
#endif

#include <stdio.h>

namespace irr
{
	//! stub for calling createDeviceEx
	IRRLICHT_API IrrlichtDevice* IRRCALLCONV createDevice(IEventReceiver* res, io::IFileSystem *file_system)
	{
		SIrrlichtCreationParameters p;
		p.EventReceiver = res;
        p.FileSystem = file_system;

		return createDeviceEx(p);
	}

	extern "C" IRRLICHT_API IrrlichtDevice* IRRCALLCONV createDeviceEx(const SIrrlichtCreationParameters& params)
	{

		IrrlichtDevice* dev = 0;
		
		SIrrlichtCreationParameters creation_params = params;

#ifdef _IRR_COMPILE_WITH_OFF_SCREEN_DEVICE_
		dev = new CIrrDeviceOffScreen(creation_params);
#endif
#ifdef _IRR_COMPILE_WITH_OFF_SCREEN_OSX_DEVICE_
		dev = new CIrrDeviceOffScreenMacOSX(creation_params);
#endif
#ifdef _IRR_COMPILE_WITH_WINDOWS_DEVICE_
		dev = new CIrrDeviceWin32(creation_params);
#endif
		if (!dev)
		    dev = new CIrrDeviceNull(creation_params);

		if (dev && !dev->getVideoDriver())
		{
			dev->closeDevice(); // destroy window
			dev->run(); // consume quit message
			dev->drop();
			dev = 0;
		}

		return dev;
	}

namespace core
{
	const matrix4 IdentityMatrix(matrix4::EM4CONST_IDENTITY);
	irr::core::stringc LOCALE_DECIMAL_POINTS(".");
}

namespace video
{
	SMaterial IdentityMaterial;
}

} // end namespace irr


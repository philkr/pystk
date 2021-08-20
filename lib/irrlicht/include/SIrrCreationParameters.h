// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_IRRLICHT_CREATION_PARAMETERS_H_INCLUDED__
#define __I_IRRLICHT_CREATION_PARAMETERS_H_INCLUDED__

#include "dimension2d.h"
#include "ILogger.h"
#include "irrString.h"

namespace irr
{
	class IEventReceiver;
    namespace io{ class IFileSystem; }

	//! Structure for holding Irrlicht Device creation parameters.
	/** This structure is used in the createDeviceEx() function. */
	struct SIrrlichtCreationParameters
	{
		//! Constructs a SIrrlichtCreationParameters structure with default values.
		SIrrlichtCreationParameters() :
			HighPrecisionFPU(false),
			EventReceiver(NULL),
            FileSystem(NULL),
#ifdef _DEBUG
			LoggingLevel(ELL_DEBUG),
#else
			LoggingLevel(ELL_INFORMATION),
#endif
			DisplayAdapter(0),
			UsePerformanceTimer(true),
			SDK_version_do_not_use(IRRLICHT_SDK_VERSION)
		{
		}

		SIrrlichtCreationParameters(const SIrrlichtCreationParameters& other) :
			SDK_version_do_not_use(IRRLICHT_SDK_VERSION)
		{*this = other;}

		SIrrlichtCreationParameters& operator=(const SIrrlichtCreationParameters& other)
		{
			HighPrecisionFPU = other.HighPrecisionFPU;
			EventReceiver = other.EventReceiver;
            FileSystem = other.FileSystem;
			LoggingLevel = other.LoggingLevel;
			DisplayAdapter = other.DisplayAdapter;
			UsePerformanceTimer = other.UsePerformanceTimer;
			PrivateData = other.PrivateData;
			return *this;
		}

		//! Specifies if the device should use high precision FPU setting
		/** This is only relevant for DirectX Devices, which switch to
		low FPU precision by default for performance reasons. However,
		this may lead to problems with the other computations of the
		application. In this case setting this flag to true should help
		- on the expense of performance loss, though.
		Default value: false */
		bool HighPrecisionFPU;

		//! A user created event receiver.
		IEventReceiver* EventReceiver;

        //! A pointer to an existing file system to be used.
        io::IFileSystem *FileSystem;

		//! Specifies the logging level used in the logging interface.
		/** The default value is ELL_INFORMATION. You can access the ILogger interface
		later on from the IrrlichtDevice with getLogger() and set another level.
		But if you need more or less logging information already from device creation,
		then you have to change it here.
		*/
		ELOG_LEVEL LoggingLevel;

		//! Allows one to select which graphic card is used for rendering when more than one card is in the system.
		/** So far only supported on D3D */
		u32 DisplayAdapter;

		//! Enables use of high performance timers on Windows platform.
		/** When performance timers are not used, standard GetTickCount()
		is used instead which usually has worse resolution, but also less
		problems with speed stepping and other techniques.
		*/
		bool UsePerformanceTimer;

		//! Don't use or change this parameter.
		/** Always set it to IRRLICHT_SDK_VERSION, which is done by default.
		This is needed for sdk version checks. */
		const c8* const SDK_version_do_not_use;

		//! Define some private data storage.
		/** Used when platform devices need access to OS specific data structures etc.
		This is only used for Android at th emoment in order to access the native
		Java RE. */
		void *PrivateData;

	};


} // end namespace irr

#endif


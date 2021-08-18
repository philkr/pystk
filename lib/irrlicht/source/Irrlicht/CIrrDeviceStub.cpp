// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CIrrDeviceStub.h"
#include "ISceneManager.h"
#include "IEventReceiver.h"
#include "IFileSystem.h"
#include "os.h"
#include "IrrCompileConfig.h"
#include "CTimer.h"
#include "CLogger.h"
#include "irrString.h"
#include "IRandomizer.h"

namespace irr
{
//! constructor
CIrrDeviceStub::CIrrDeviceStub(const SIrrlichtCreationParameters& params)
: IrrlichtDevice(), VideoDriver(0), SceneManager(0),
	Timer(0), Logger(0), FileSystem(0), CreationParams(params),
	Close(false)
{
	Timer = new CTimer(params.UsePerformanceTimer);
	if (os::Printer::Logger)
	{
		os::Printer::Logger->grab();
		Logger = (CLogger*)os::Printer::Logger;
	}
	else
	{
		Logger = new CLogger();
		os::Printer::Logger = Logger;
	}
	Logger->setLogLevel(CreationParams.LoggingLevel);

	os::Printer::Logger = Logger;

    // If the user supplies a file system, use it instead of creating a new one
    if (params.FileSystem)
    {
        FileSystem = params.FileSystem;
        FileSystem->grab();
    }
    else
        FileSystem = io::createFileSystem();
    core::stringc s = "..:: Antarctica Rendering Engine ";
	s.append("2.0 ::..");
	// os::Printer::log(s.c_str(), ELL_INFORMATION);

	checkVersion(params.SDK_version_do_not_use);
}


CIrrDeviceStub::~CIrrDeviceStub()
{
	FileSystem->drop();

	if (VideoDriver)
		VideoDriver->drop();

	if (SceneManager)
		SceneManager->drop();

	if (Timer)
		Timer->drop();

	if (Logger->drop())
		os::Printer::Logger = 0;
}


void CIrrDeviceStub::createGUIAndScene()
{
	// create Scene manager
	SceneManager = scene::createSceneManager(VideoDriver, FileSystem);
}


//! returns the video driver
video::IVideoDriver* CIrrDeviceStub::getVideoDriver()
{
	return VideoDriver;
}



//! return file system
io::IFileSystem* CIrrDeviceStub::getFileSystem()
{
	return FileSystem;
}


//! returns the scene manager
scene::ISceneManager* CIrrDeviceStub::getSceneManager()
{
	return SceneManager;
}


//! \return Returns a pointer to the ITimer object. With it the
//! current Time can be received.
ITimer* CIrrDeviceStub::getTimer()
{
	return Timer;
}


//! Returns the version of the engine.
const char* CIrrDeviceStub::getVersion() const
{
	return IRRLICHT_SDK_VERSION;
}


//! checks version of sdk and prints warning if there might be a problem
bool CIrrDeviceStub::checkVersion(const char* version)
{
	if (strcmp(getVersion(), version))
	{
		core::stringc w;
		w = "Warning: The library version of the Irrlicht Engine (";
		w += getVersion();
		w += ") does not match the version the application was compiled with (";
		w += version;
		w += "). This may cause problems.";
		os::Printer::log(w.c_str(), ELL_WARNING);
		_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
		return false;
	}

	return true;
}

//! Remove all messages pending in the system message loop
void CIrrDeviceStub::clearSystemMessages()
{
}

} // end namespace irr


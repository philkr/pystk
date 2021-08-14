// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_IRR_DEVICE_STUB_H_INCLUDED__
#define __C_IRR_DEVICE_STUB_H_INCLUDED__

#include "IrrlichtDevice.h"
#include "SIrrCreationParameters.h"
#include "CVideoModeList.h"

namespace irr
{
	// lots of prototypes:
	class ILogger;
	class CLogger;
	class IRandomizer;

	namespace scene
	{
		ISceneManager* createSceneManager(video::IVideoDriver* driver, io::IFileSystem* fs);
	}

	namespace io
	{
		IFileSystem* createFileSystem();
	}

	namespace video
	{
		IVideoDriver* createNullDriver(io::IFileSystem* io);
	}



	//! Stub for an Irrlicht Device implementation
	class CIrrDeviceStub : public IrrlichtDevice
	{
	public:

		//! constructor
		CIrrDeviceStub(const SIrrlichtCreationParameters& param);

		//! destructor
		virtual ~CIrrDeviceStub();

		//! returns the video driver
		virtual video::IVideoDriver* getVideoDriver();

		//! return file system
		virtual io::IFileSystem* getFileSystem();

		//! returns the scene manager
		virtual scene::ISceneManager* getSceneManager();

		//! Returns a pointer to the ITimer object. With it the current Time can be received.
		virtual ITimer* getTimer();

		//! Returns the version of the engine.
		virtual const char* getVersion() const;

		//! Remove all messages pending in the system message loop
		virtual void clearSystemMessages();
	protected:
		void createGUIAndScene();

		//! checks version of SDK and prints warning if there might be a problem
		bool checkVersion(const char* version);

		video::IVideoDriver* VideoDriver;
		scene::ISceneManager* SceneManager;
		ITimer* Timer;
		CLogger* Logger;
		io::IFileSystem* FileSystem;

		SIrrlichtCreationParameters CreationParams;
		bool Close;
	};

} // end namespace irr

#endif


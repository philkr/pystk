// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_IRRLICHT_DEVICE_H_INCLUDED__
#define __I_IRRLICHT_DEVICE_H_INCLUDED__

#include "IReferenceCounted.h"
#include "dimension2d.h"
#include "IVideoDriver.h"
#include "IEventReceiver.h"
#include "ICursorControl.h"
#include "IVideoModeList.h"
#include "ITimer.h"

namespace irr
{
	class ILogger;
	class IEventReceiver;
	class IRandomizer;

	namespace io {
		class IFileSystem;
	} // end namespace io

	namespace scene {
		class ISceneManager;
	} // end namespace scene

	//! The Irrlicht device. You can create it with createDevice() or createDeviceEx().
	/** This is the most important class of the Irrlicht Engine. You can
	access everything in the engine if you have a pointer to an instance of
	this class.  There should be only one instance of this class at any
	time.
	*/
	class IrrlichtDevice : public virtual IReferenceCounted
	{
	public:

		//! Runs the device.
		/** Also increments the virtual timer by calling
		ITimer::tick();. You can prevent this
		by calling ITimer::stop(); before and ITimer::start() after
		calling IrrlichtDevice::run(). Returns false if device wants
		to be deleted. Use it in this way:
		\code
		while(device->run())
		{
			// draw everything here
		}
		\endcode
		If you want the device to do nothing if the window is inactive
		(recommended), use the slightly enhanced code shown at isWindowActive().

		Note if you are running Irrlicht inside an external, custom
		created window: Calling Device->run() will cause Irrlicht to
		dispatch windows messages internally.
		If you are running Irrlicht in your own custom window, you can
		also simply use your own message loop using GetMessage,
		DispatchMessage and whatever and simply don't use this method.
		But note that Irrlicht will not be able to fetch user input
		then. See irr::SIrrlichtCreationParameters::WindowId for more
		informations and example code.
		*/
		virtual bool run() = 0;

		//! Provides access to the video driver for drawing 3d and 2d geometry.
		/** \return Pointer the video driver. */
		virtual video::IVideoDriver* getVideoDriver() = 0;

		//! Provides access to the virtual file system.
		/** \return Pointer to the file system. */
		virtual io::IFileSystem* getFileSystem() = 0;

		//! Provides access to the scene manager.
		/** \return Pointer to the scene manager. */
		virtual scene::ISceneManager* getSceneManager() = 0;

		//! Provides access to the engine's timer.
		/** The system time can be retrieved by it as
		well as the virtual time, which also can be manipulated.
		\return Pointer to the ITimer object. */
		virtual ITimer* getTimer() = 0;

		//! Notifies the device that it should close itself.
		/** IrrlichtDevice::run() will always return false after closeDevice() was called. */
		virtual void closeDevice() = 0;

		//! Get the version of the engine.
		/** The returned string
		will look like this: "1.2.3" or this: "1.2".
		\return String which contains the version. */
		virtual const c8* getVersion() const = 0;

		//! Remove messages pending in the system message loop
		/** This function is usually used after messages have been buffered for a longer time, for example
		when loading a large scene. Clearing the message loop prevents that mouse- or buttonclicks which users
		have pressed in the meantime will now trigger unexpected actions in the gui. <br>
		So far the following messages are cleared:<br>
		Win32: All keyboard and mouse messages<br>
		Linux: All keyboard and mouse messages<br>
		All other devices are not yet supported here.<br>
		The function is still somewhat experimental, as the kind of messages we clear is based on just a few use-cases.
		If you think further messages should be cleared, or some messages should not be cleared here, then please tell us. */
		virtual void clearSystemMessages() = 0;
	};

} // end namespace irr

#endif


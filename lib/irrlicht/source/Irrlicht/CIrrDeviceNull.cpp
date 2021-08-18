// Copyright (C) 2002-2012 Nikolaus Gebhardt
// Copyright (C) 2014-2015 Dawid Gan
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

extern bool GLContextDebugBit;

#include "CIrrDeviceNull.h"

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <time.h>
#include <locale.h>
#include "IEventReceiver.h"
#include "ISceneManager.h"
#include "os.h"
#include "CTimer.h"
#include "irrString.h"
#include "Keycodes.h"
#include "CColorConverter.h"
#include "SIrrCreationParameters.h"
#include "CNullDriver.h"

namespace irr
{

//! constructor
CIrrDeviceNull::CIrrDeviceNull(const SIrrlichtCreationParameters& params)
 : CIrrDeviceStub(params)
{
    // create driver
    VideoDriver = video::createNullDriver(FileSystem);

    if (!VideoDriver)
        return;

    createGUIAndScene();
}



//! destructor
CIrrDeviceNull::~CIrrDeviceNull()
{
}


//! runs the device. Returns false if device wants to be deleted
bool CIrrDeviceNull::run()
{
    os::Timer::tick();
    return !Close;
}


//! notifies the device that it should close itself
void CIrrDeviceNull::closeDevice()
{
    Close = true;
}

} // end namespace

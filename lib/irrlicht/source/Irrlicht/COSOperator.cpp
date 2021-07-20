// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "COSOperator.h"

#ifdef _IRR_WINDOWS_API_
#ifndef _IRR_XBOX_PLATFORM_
#include <windows.h>
#endif
#else
#include <string.h>
#include <unistd.h>
#endif

#include <cassert>

#include "IrrlichtDevice.h"

namespace irr
{

// constructor  linux
	COSOperator::COSOperator(const core::stringc& osVersion, IrrlichtDevice* device)
: IrrDevice(device)
{
}


// constructor
COSOperator::COSOperator(const core::stringc& osVersion) 
: IrrDevice(NULL)
{
	#ifdef _DEBUG
	setDebugName("COSOperator");
	#endif
}

} // end namespace


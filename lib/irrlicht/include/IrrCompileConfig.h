// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_COMPILE_CONFIG_H_INCLUDED__
#define __IRR_COMPILE_CONFIG_H_INCLUDED__

//! Irrlicht SDK Version
#define IRRLICHT_VERSION_MAJOR 1
#define IRRLICHT_VERSION_MINOR 8
#define IRRLICHT_VERSION_REVISION 0
// This flag will be defined only in SVN, the official release code will have
// it undefined
//#define IRRLICHT_VERSION_SVN -alpha
#define IRRLICHT_SDK_VERSION "1.8.0"

#include <stdio.h> // TODO: Although included elsewhere this is required at least for mingw

//! WIN32 for Windows32
//! WIN64 for Windows64
// The windows platform
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
#define _IRR_WINDOWS_
#define _IRR_WINDOWS_API_
#endif

#ifdef _IRR_COMPILE_WITH_WINDOWS_DEVICE_
#define _IRR_COMPILE_WITH_OPENGL_
#endif


#if defined(_MSC_VER) && (_MSC_VER < 1300)
#  error "Only Microsoft Visual Studio 7.0 and later are supported."
#endif


// The MacOS X platform
#if defined(__APPLE__) || defined(MACOSX)
#if !defined(MACOSX)
#define MACOSX // legacy support
#endif
#define _IRR_OSX_PLATFORM_
#endif

#ifdef _IRR_COMPILE_WITH_OFF_SCREEN_OSX_DEVICE_
#define _IRR_COMPILE_WITH_OPENGL_
#define GL_SILENCE_DEPRECATION
#endif


// The Linux platform
#if !defined(_IRR_WINDOWS_API_) && !defined(_IRR_OSX_PLATFORM_)
#define _IRR_POSIX_API_
#endif

#ifdef _IRR_COMPILE_WITH_OFF_SCREEN_DEVICE_
#define _IRR_COMPILE_WITH_OPENGL_
#endif

//! Maximum number of texture an SMaterial can have, up to 8 are supported by Irrlicht.
#define _IRR_MATERIAL_MAX_TEXTURES_ 8


//! Define _IRR_OPENGL_USE_EXTPOINTER_ if the OpenGL renderer should use OpenGL extensions via function pointers.
/** On some systems there is no support for the dynamic extension of OpenGL
    via function pointers such that this has to be undef'ed. */
#ifdef _IRR_COMPILE_WITH_OPENGL_
#if !defined(_IRR_OSX_PLATFORM_) && !defined(_IRR_SOLARIS_PLATFORM_)
#define _IRR_OPENGL_USE_EXTPOINTER_
#endif
#endif

//! Define _IRR_WCHAR_FILESYSTEM to enable unicode filesystem support for the engine.
/** This enables the engine to read/write from unicode filesystem. If you
disable this feature, the engine behave as before (ansi). This is currently only supported
for Windows based systems. You also have to set #define UNICODE for this to compile.
*/
//#define _IRR_WCHAR_FILESYSTEM
#ifdef NO_IRR_WCHAR_FILESYSTEM
#undef _IRR_WCHAR_FILESYSTEM
#endif

//! Define _IRR_COMPILE_WITH_JPEGLIB_ to enable compiling the engine using libjpeg.
/** This enables the engine to read jpeg images. If you comment this out,
the engine will no longer read .jpeg images. */
#define _IRR_COMPILE_WITH_LIBJPEG_
#ifdef NO_IRR_COMPILE_WITH_LIBJPEG_
#undef _IRR_COMPILE_WITH_LIBJPEG_
#endif

//! Define _IRR_USE_NON_SYSTEM_JPEG_LIB_ to let irrlicht use the jpeglib which comes with irrlicht.
/** If this is commented out, Irrlicht will try to compile using the jpeg lib installed in the system.
    This is only used when _IRR_COMPILE_WITH_LIBJPEG_ is defined. */
//#define _IRR_USE_NON_SYSTEM_JPEG_LIB_
#ifdef NO_IRR_USE_NON_SYSTEM_JPEG_LIB_
#undef _IRR_USE_NON_SYSTEM_JPEG_LIB_
#endif

//! Define _IRR_COMPILE_WITH_LIBPNG_ to enable compiling the engine using libpng.
/** This enables the engine to read png images. If you comment this out,
the engine will no longer read .png images. */
#define _IRR_COMPILE_WITH_LIBPNG_
#ifdef NO_IRR_COMPILE_WITH_LIBPNG_
#undef _IRR_COMPILE_WITH_LIBPNG_
#endif

//! Define _IRR_USE_NON_SYSTEM_LIBPNG_ to let irrlicht use the libpng which comes with irrlicht.
/** If this is commented out, Irrlicht will try to compile using the libpng installed in the system.
    This is only used when _IRR_COMPILE_WITH_LIBPNG_ is defined. */
//#define _IRR_USE_NON_SYSTEM_LIB_PNG_
#ifdef NO_IRR_USE_NON_SYSTEM_LIB_PNG_
#undef _IRR_USE_NON_SYSTEM_LIB_PNG_
#endif

//! Define _IRR_USE_NVIDIA_PERFHUD_ to opt-in to using the nVidia PerHUD tool
/** Enable, by opting-in, to use the nVidia PerfHUD performance analysis driver
tool <http://developer.nvidia.com/object/nvperfhud_home.html>. */
#undef _IRR_USE_NVIDIA_PERFHUD_

//! Uncomment the following line if you want to ignore the deprecated warnings
#define IGNORE_DEPRECATED_WARNING

//! Define _IRR_COMPILE_WITH_SKINNED_MESH_SUPPORT_ if you want to use bone based
/** animated meshes. If you compile without this, you will be unable to load
B3D, MS3D or X meshes */
#define _IRR_COMPILE_WITH_SKINNED_MESH_SUPPORT_
#ifdef NO_IRR_COMPILE_WITH_SKINNED_MESH_SUPPORT_
#undef _IRR_COMPILE_WITH_SKINNED_MESH_SUPPORT_
#endif

#ifdef _IRR_COMPILE_WITH_SKINNED_MESH_SUPPORT_
//! Define _IRR_COMPILE_WITH_B3D_LOADER_ if you want to use Blitz3D files
#define _IRR_COMPILE_WITH_B3D_LOADER_
#ifdef NO_IRR_COMPILE_WITH_B3D_LOADER_
#undef _IRR_COMPILE_WITH_B3D_LOADER_
#endif
#endif    // _IRR_COMPILE_WITH_SKINNED_MESH_SUPPORT_

//! Define _IRR_COMPILE_WITH_BMP_LOADER_ if you want to load .bmp files
//! Disabling this loader will also disable the built-in font
#define _IRR_COMPILE_WITH_BMP_LOADER_
#ifdef NO_IRR_COMPILE_WITH_BMP_LOADER_
#undef _IRR_COMPILE_WITH_BMP_LOADER_
#endif
//! Define _IRR_COMPILE_WITH_JPG_LOADER_ if you want to load .jpg files
#define _IRR_COMPILE_WITH_JPG_LOADER_
#ifdef NO_IRR_COMPILE_WITH_JPG_LOADER_
#undef _IRR_COMPILE_WITH_JPG_LOADER_
#endif
//! Define _IRR_COMPILE_WITH_PNG_LOADER_ if you want to load .png files
#define _IRR_COMPILE_WITH_PNG_LOADER_
#ifdef NO_IRR_COMPILE_WITH_PNG_LOADER_
#undef _IRR_COMPILE_WITH_PNG_LOADER_
#endif

//! Define _IRR_COMPILE_WITH_BMP_WRITER_ if you want to write .bmp files
#define _IRR_COMPILE_WITH_BMP_WRITER_
#ifdef NO_IRR_COMPILE_WITH_BMP_WRITER_
#undef _IRR_COMPILE_WITH_BMP_WRITER_
#endif
//! Define _IRR_COMPILE_WITH_JPG_WRITER_ if you want to write .jpg files
#define _IRR_COMPILE_WITH_JPG_WRITER_
#ifdef NO_IRR_COMPILE_WITH_JPG_WRITER_
#undef _IRR_COMPILE_WITH_JPG_WRITER_
#endif
//! Define _IRR_COMPILE_WITH_PNG_WRITER_ if you want to write .png files
#define _IRR_COMPILE_WITH_PNG_WRITER_
#ifdef NO_IRR_COMPILE_WITH_PNG_WRITER_
#undef _IRR_COMPILE_WITH_PNG_WRITER_
#endif

//! Define __IRR_COMPILE_WITH_ZIP_ARCHIVE_LOADER_ if you want to open ZIP and GZIP archives
/** ZIP reading has several more options below to configure. */
#define __IRR_COMPILE_WITH_ZIP_ARCHIVE_LOADER_
#ifdef NO__IRR_COMPILE_WITH_ZIP_ARCHIVE_LOADER_
#undef __IRR_COMPILE_WITH_ZIP_ARCHIVE_LOADER_
#endif
#ifdef __IRR_COMPILE_WITH_ZIP_ARCHIVE_LOADER_
//! Define _IRR_COMPILE_WITH_ZLIB_ to enable compiling the engine using zlib.
/** This enables the engine to read from compressed .zip archives. If you
disable this feature, the engine can still read archives, but only uncompressed
ones. */
#define _IRR_COMPILE_WITH_ZLIB_
#ifdef NO_IRR_COMPILE_WITH_ZLIB_
#undef _IRR_COMPILE_WITH_ZLIB_
#endif
//! Define _IRR_USE_NON_SYSTEM_ZLIB_ to let irrlicht use the zlib which comes with irrlicht.
/** If this is commented out, Irrlicht will try to compile using the zlib
installed on the system. This is only used when _IRR_COMPILE_WITH_ZLIB_ is
defined. */
//#define _IRR_USE_NON_SYSTEM_ZLIB_
#ifdef NO_IRR_USE_NON_SYSTEM_ZLIB_
#undef _IRR_USE_NON_SYSTEM_ZLIB_
#endif
#endif

//! Define __IRR_COMPILE_WITH_MOUNT_ARCHIVE_LOADER_ if you want to mount folders as archives
#define __IRR_COMPILE_WITH_MOUNT_ARCHIVE_LOADER_
#ifdef NO__IRR_COMPILE_WITH_MOUNT_ARCHIVE_LOADER_
#undef __IRR_COMPILE_WITH_MOUNT_ARCHIVE_LOADER_
#endif
//! Define __IRR_COMPILE_WITH_TAR_ARCHIVE_LOADER_ if you want to open TAR archives
#define __IRR_COMPILE_WITH_TAR_ARCHIVE_LOADER_
#ifdef NO__IRR_COMPILE_WITH_TAR_ARCHIVE_LOADER_
#undef __IRR_COMPILE_WITH_TAR_ARCHIVE_LOADER_
#endif
//! Define __IRR_COMPILE_WITH_WAD_ARCHIVE_LOADER_ if you want to open WAD archives
#define __IRR_COMPILE_WITH_WAD_ARCHIVE_LOADER_
#ifdef NO__IRR_COMPILE_WITH_WAD_ARCHIVE_LOADER_
#undef __IRR_COMPILE_WITH_WAD_ARCHIVE_LOADER_
#endif

//! Set FPU settings
/** Irrlicht should use approximate float and integer fpu techniques
precision will be lower but speed higher. currently X86 only
*/
#if !defined(_IRR_OSX_PLATFORM_) && !defined(_IRR_SOLARIS_PLATFORM_)
    //#define IRRLICHT_FAST_MATH
    #ifdef NO_IRRLICHT_FAST_MATH
    #undef IRRLICHT_FAST_MATH
    #endif
#endif

// Some cleanup and standard stuff

#ifdef _IRR_WINDOWS_API_

// To build Irrlicht as a static library, you must define _IRR_STATIC_LIB_ in both the
// Irrlicht build, *and* in the user application, before #including <irrlicht.h>
#ifndef _IRR_STATIC_LIB_
#ifdef IRRLICHT_EXPORTS
#define IRRLICHT_API __declspec(dllexport)
#else
#define IRRLICHT_API __declspec(dllimport)
#endif // IRRLICHT_EXPORT
#else
#define IRRLICHT_API
#endif // _IRR_STATIC_LIB_

// Declare the calling convention.
#if defined(_STDCALL_SUPPORTED)
#define IRRCALLCONV __stdcall
#else
#define IRRCALLCONV __cdecl
#endif // STDCALL_SUPPORTED

#else // _IRR_WINDOWS_API_

// Force symbol export in shared libraries built with gcc.
#if (__GNUC__ >= 4) && !defined(_IRR_STATIC_LIB_) && defined(IRRLICHT_EXPORTS)
#define IRRLICHT_API __attribute__ ((visibility("default")))
#else
#define IRRLICHT_API
#endif

#define IRRCALLCONV

#endif // _IRR_WINDOWS_API_

// We need to disable DIRECT3D9 support for Visual Studio 6.0 because
// those $%&$!! disabled support for it since Dec. 2004 and users are complaining
// about linker errors. Comment this out only if you are knowing what you are
// doing. (Which means you have an old DX9 SDK and VisualStudio6).
#ifdef _MSC_VER
#if (_MSC_VER < 1300 && !defined(__GNUC__))
#undef _IRR_COMPILE_WITH_DIRECT3D_9_
#pragma message("Compiling Irrlicht with Visual Studio 6.0, support for DX9 is disabled.")
#endif
#endif

#ifndef _IRR_WINDOWS_API_
    #undef _IRR_WCHAR_FILESYSTEM
#endif

#if defined(__sparc__) || defined(__sun__)
#define __BIG_ENDIAN__
#endif

//! Define __IRR_HAS_S64 if the irr::s64 type should be enable (needs long long, available on most platforms, but not part of ISO C++ 98)
#define __IRR_HAS_S64
#ifdef NO__IRR_HAS_S64
#undef __IRR_HAS_S64
#endif

#endif // __IRR_COMPILE_CONFIG_H_INCLUDED__


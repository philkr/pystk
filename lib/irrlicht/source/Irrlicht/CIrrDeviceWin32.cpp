// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "IrrCompileConfig.h"

#ifdef _IRR_COMPILE_WITH_WINDOWS_DEVICE_

#include "CIrrDeviceWin32.h"
#include "COpenGLExtensionHandler.h"
#include "IEventReceiver.h"
#include "irrList.h"
#include "os.h"

#include "utils/string_utils.hpp"
#include "utils/utf8.h"

#include "CTimer.h"
#include "irrString.h"
#include "dimension2d.h"
#include <mmsystem.h>
#include <regstr.h>
#include <tchar.h>
#include <winuser.h>

namespace irr
{
    namespace video
    {
        IVideoDriver* createOpenGLDriver(const irr::SIrrlichtCreationParameters& params,
            io::IFileSystem* io, CIrrDeviceWin32* device);
    }
} // end namespace irr

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}


namespace irr
{

static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribs_ARB;

static HGLRC getMeAGLContext(HDC HDc)
{
    std::pair<int, int> version[] = {{4,3}, {4,0}, {3, 3}, {3, 1}};
    for (auto v: version) {
        int ctx[] =
        {
            WGL_CONTEXT_MAJOR_VERSION_ARB, v.first,
            WGL_CONTEXT_MINOR_VERSION_ARB, v.second,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };

        HGLRC hrc = wglCreateContextAttribs_ARB(HDc, 0, ctx);
        if (hrc)
            return hrc;
    }
    return NULL;
}
//! constructor
CIrrDeviceWin32::CIrrDeviceWin32(const SIrrlichtCreationParameters& params)
: CIrrDeviceStub(params), HWnd(0)
{
    #ifdef _DEBUG
    setDebugName("CIrrDeviceWin32");
    #endif

    // get handle to exe file
    HINSTANCE hInstance = GetModuleHandle(0);

    // Store original desktop mode.
    // create the window if we need to and we do not use the null device
    // Register Class
    WNDCLASSEX wcex;
    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = NULL;
    wcex.hCursor        = 0; // LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = 0;
    wcex.lpszClassName  = _T("CIrrDeviceWin32");
    wcex.hIconSm        = 0;

    RegisterClassEx(&wcex);

    // calculate client size
    DWORD style = WS_POPUP;

    style = WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

    // create window
    HWnd = CreateWindow(wcex.lpszClassName, __TEXT(""), style, 0, 0, 10, 10, NULL, NULL, hInstance, NULL);
    if (!HWnd)
    {
        os::Printer::log("Cannot create a opengl window.", ELL_ERROR);
        UnregisterClass(wcex.lpszClassName, hInstance);
        return;
    }
    ShowWindow(HWnd, SW_HIDE);
    UpdateWindow(HWnd);

    // Initialize the OpenGL context
    HDc = GetDC(HWnd);

    // Set up pixel format descriptor with desired parameters
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),             // Size Of This Pixel Format Descriptor
        1,                                         // Version Number
        (DWORD)(PFD_DRAW_TO_WINDOW |               // Format Must Support Window
        PFD_SUPPORT_OPENGL),                        // Format Must Support OpenGL
        PFD_TYPE_RGBA,                             // Request An RGBA Format
        32,                                        // Select Our Color Depth
        0, 0, 0, 0, 0, 0,                          // Color Bits Ignored
        0,                                         // No Alpha Buffer
        0,                                         // Shift Bit Ignored
        0,                                         // No Accumulation Buffer
        0, 0, 0, 0,	                               // Accumulation Bits Ignored
        16,                                        // Z-Buffer (Depth Buffer)
        BYTE(0),                                   // Stencil Buffer Depth
        0,                                         // No Auxiliary Buffer
        PFD_MAIN_PLANE,                            // Main Drawing Layer
        0,                                         // Reserved
        0, 0, 0                                    // Layer Masks Ignored
    };

    GLuint PixelFormat = ChoosePixelFormat(HDc, &pfd);
    if (!PixelFormat)
    {
        os::Printer::log("Cannot create a GL pixel format.", ELL_ERROR);
        ReleaseDC(HWnd, HDc);
        DestroyWindow(HWnd);
        UnregisterClass(wcex.lpszClassName, hInstance);
        return;
    }

    SetPixelFormat(HDc, PixelFormat, &pfd);
    HGLRC dummy_rc = wglCreateContext(HDc);
    if (!dummy_rc)
    {
        os::Printer::log("Cannot create a GL rendering context.", ELL_ERROR);
        ReleaseDC(HWnd, HDc);
        DestroyWindow(HWnd);
        UnregisterClass(wcex.lpszClassName, hInstance);
        return;
    }

	if (!wglMakeCurrent(HDc, dummy_rc))
	{
		os::Printer::log("Cannot activate a GL rendering context.", ELL_ERROR);
		wglDeleteContext(dummy_rc);
		ReleaseDC(HWnd, HDc);
		DestroyWindow(HWnd);
		UnregisterClass(wcex.lpszClassName, hInstance);
		return;
	}

    // Load the OpenGL ARB extensions
	core::stringc wglExtensions;
#ifdef WGL_ARB_extensions_string
	PFNWGLGETEXTENSIONSSTRINGARBPROC irrGetExtensionsString = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionsStringARB");
	if (irrGetExtensionsString)
		wglExtensions = irrGetExtensionsString(HDc);
#elif defined(WGL_EXT_extensions_string)
	PFNWGLGETEXTENSIONSSTRINGEXTPROC irrGetExtensionsString = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)wglGetProcAddress("wglGetExtensionsStringEXT");
	if (irrGetExtensionsString)
		wglExtensions = irrGetExtensionsString(HDc);
#endif
#ifdef WGL_ARB_create_context
	wglCreateContextAttribs_ARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
#endif

	if (!wglMakeCurrent(HDc, 0))
	{
		os::Printer::log("Cannot deactivate a GL rendering context.", ELL_ERROR);
		wglDeleteContext(dummy_rc);
		ReleaseDC(HWnd, HDc);
		DestroyWindow(HWnd);
		UnregisterClass(wcex.lpszClassName, hInstance);
		return;
	}
    // Delete the initial con
    wglDeleteContext(dummy_rc);

	// create rendering context
#ifdef WGL_ARB_create_context
	if (wglCreateContextAttribs_ARB)
	{
		HRc = getMeAGLContext(HDc);
	}
	else
#endif
		HRc = wglCreateContext(HDc);

	if (!HRc)
	{
		os::Printer::log("Cannot create a GL rendering context.", ELL_ERROR);
		return;
	}

	// activate rendering context

	if (!wglMakeCurrent(HDc, HRc))
	{
		os::Printer::log("Cannot activate GL rendering context", ELL_ERROR);
		wglDeleteContext(HRc);
		ReleaseDC(HWnd, HDc);
		DestroyWindow(HWnd);
		UnregisterClass(wcex.lpszClassName, hInstance);
		return;
	}

    // create driver
    createDriver();

    if (VideoDriver)
        createGUIAndScene();
}


//! destructor
CIrrDeviceWin32::~CIrrDeviceWin32()
{
    if (HDc && !wglMakeCurrent(HDc, 0))
        os::Printer::log("Release of dc and rc failed.", ELL_WARNING);

    if (HRc && !wglDeleteContext(HRc))
        os::Printer::log("Release of rendering context failed.", ELL_WARNING);

    if (HDc)
        ReleaseDC(HWnd, HDc);

    if (HWnd)
		DestroyWindow(HWnd);
}


//! create the driver
void CIrrDeviceWin32::createDriver()
{
    #ifdef _IRR_COMPILE_WITH_OPENGL_
    VideoDriver = video::createOpenGLDriver(CreationParams, FileSystem, this);
    if (!VideoDriver)
    {
        os::Printer::log("Could not create OpenGL driver.", ELL_ERROR);
    }
    #else
    os::Printer::log("OpenGL driver was not compiled in.", ELL_ERROR);
    #endif
}


//! make the device current.
bool CIrrDeviceWin32::makeCurrent()
{
    return wglMakeCurrent(HDc, HRc);
}


//! runs the device. Returns false if device wants to be deleted
bool CIrrDeviceWin32::run()
{
    os::Timer::tick();
    handleSystemMessages();

    _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
    return !Close;
}

//! notifies the device that it should close itself
void CIrrDeviceWin32::closeDevice()
{
    MSG msg;
    PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_REMOVE);
    PostQuitMessage(0);
    PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_REMOVE);
    DestroyWindow(HWnd);
    HINSTANCE hInstance = GetModuleHandle(0);
    UnregisterClass(_T("CIrrDeviceWin32"), hInstance);
    Close=true;
}

//! Process system events
void CIrrDeviceWin32::handleSystemMessages()
{
    MSG msg;

    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        // No message translation because we don't use WM_CHAR and it would conflict with our
        // deadkey handling.

        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (msg.message == WM_QUIT)
            Close = true;
    }
}


//! Remove all messages pending in the system message loop
void CIrrDeviceWin32::clearSystemMessages()
{
}

// shows last error in a messagebox to help internal debugging.
void CIrrDeviceWin32::ReportLastWinApiError()
{
    // (based on code from ovidiucucu from http://www.codeguru.com/forum/showthread.php?t=318721)
    LPCTSTR pszCaption = __TEXT("Windows SDK Error Report");
    DWORD dwError = GetLastError();

    if(NOERROR == dwError)
    {
        MessageBox(NULL, __TEXT("No error"), pszCaption, MB_OK);
    }
    else
    {
        const DWORD dwFormatControl = FORMAT_MESSAGE_ALLOCATE_BUFFER |
                                        FORMAT_MESSAGE_IGNORE_INSERTS |
                                        FORMAT_MESSAGE_FROM_SYSTEM;

        LPVOID pTextBuffer = NULL;
        DWORD dwCount = FormatMessage(dwFormatControl,
                                        NULL,
                                        dwError,
                                        0,
                                        (LPTSTR) &pTextBuffer,
                                        0,
                                        NULL);
        if(0 != dwCount)
        {
            MessageBox(NULL, (LPCTSTR)pTextBuffer, pszCaption, MB_OK|MB_ICONERROR);
            LocalFree(pTextBuffer);
        }
        else
        {
            MessageBox(NULL, __TEXT("Unknown error"), pszCaption, MB_OK|MB_ICONERROR);
        }
    }
}

} // end namespace

#endif // _IRR_COMPILE_WITH_WINDOWS_DEVICE_

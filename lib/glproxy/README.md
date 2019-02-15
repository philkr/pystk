GLproxy
==========
[![Linux (Ubuntu 12.04) and OS X (10.10 & 10.11)](https://img.shields.io/travis/glproxy/glproxy/master.svg?style=flat-square&label=Linux%20%26%20OS%20X)](https://travis-ci.org/glproxy/glproxy/builds)
[![Windows Build status](https://img.shields.io/appveyor/ci/lygstate/glproxy/master.svg?style=flat-square&label=Windows)](https://ci.appveyor.com/project/lygstate/glproxy/branch/master)

GLproxy is a library for handling OpenGL function pointer management for
you.

It hides the complexity of `dlopen()`, `dlsym()`,
`glXGetProcAddress()`, `eglGetProcAddress()`, etc. from the
app developer, with very little knowledge needed on their part.  They
get to read GL specs and write code using undecorated function names
like `glCompileShader()`.

Don't forget to check for your extensions or versions being present
before you use them, just like before!  We'll tell you what you forgot
to check for instead of just segfaulting, though.

Features
--------

* Automatically initializes as new OpenGL functions are used.
* Desktop OpenGL 4.4 core and compatibility context support.
* OpenGL ES 1/2/3 context support.
* Knows about function aliases so (e.g.) `glBufferData()` can be
  used with `GL_ARB_vertex_buffer_object` implementations, along
  with desktop OpenGL 1.5+ implementations.
* GLX, and WGL support.
* EGL support. EGL headers are included, so they're not necessary to build GLproxy
  with EGL support.
* Can be mixed with non-glproxy OpenGL usage.

Building (CMake)
-----------------

CMake is now the recommended way to build glproxy. It supports building both
shared and static libraries (by default only shared library is built). It also
supports building and running tests, both for the static and the shared library.

Building with CMake should be as simple as running:

    mkdir build
    cd build
    cmake -G "<my-generator>" ..
    cmake --build .
Running tests for Win32 should be as simple as running:
    cmake --build . --target RUN_TESTS
Running tests for Unix should be as simple as running:
    ctest

(run `cmake -h` see a list of possible generators). Then, to build the project,
depending on the type of generator you use, e.g. for Unix type `make`, and for
MSVC open the solution in Visual studio and build the solution.

* To build & test for 32 bit with MSVC, using the following command
  cmake -G "Visual Studio 14 2015" ..
  cmake --build . --config Release
  cmake --build . --target RUN_TESTS --config Release

  cmake --build . --config Debug
  cmake --build . --target RUN_TESTS --config Debug

* To build for 64 bit with MSVC add ` Win64` to the generator name, e.g.
  cmake -G "Visual Studio 14 2015 Win64" ..

* To rebuild the generated headers from the specs, add
`-DGLPROXY_REBUILD_FROM_SPECS=ON` to the `cmake` invocation.

* To disable building shared libraries and building static libraries, add
`-DGLPROXY_BUILD_SHARED=OFF` to the `cmake` invocation.

* To disable building tests, add
`-DGLPROXY_BUILD_TESTS=OFF` to the `cmake` invocation.

* To link to the static Runtime Library with MSVC (rather than to the DLL), add
`-DGLPROXY_MSVC_USE_RUNTIME_LIBRARY_DLL=OFF` to the `cmake` invocation.

Switching your Code to Use GLproxy
---------------------------------

* NOTE: If you use the static version of GLproxy, you must build your project with
  "GLPROXY_STATIC_LIB" defined!

It should be as easy as replacing:

    #include <GL/gl.h>
    #include <GL/glx.h>
    #include <GL/glext.h>
    #include <EGL/egl.h>
    #include <EGL/eglext.h>
    #include <Windows.h> // for WGL

with:

    #include <glproxy/gl.h>
    #include <glproxy/glx.h>
    #include <glproxy/egl.h>
    #include <glproxy/wgl.h>

As long as glproxy's headers appear first, you should be ready to go.
Additionally, some new helpers become available, so you don't have to
write them:

`int glproxy_gl_version()` returns the GL version:

* 12 for GL 1.2
* 20 for GL 2.0
* 44 for GL 4.4

`bool glproxy_has_gl_extension()` returns whether a GL extension is
available (`GL_ARB_texture_buffer_object`, for example).

Note that this is not terribly fast, so keep it out of your hot paths,
ok?

Using OpenGL ES / EGL
----------------------

Building GLproxy with OpenGL ES / EGL support is now built-in. However, to
actually make use OpenGL ES and/or EGL on a computer, it's recommended (and in
some platforms necessary) to use an OpenGL ES / EGL emulator. I recommend using
[PowerVR SDK](http://community.imgtec.com/developers/powervr/graphics-sdk/),
which is available for Linux, OS X and Windows. Download it and run the
installer. In the installer, you don't have to check everything: Enough to check
`PowerVR Tools -> PVRVFrame` and `PowerVR SDK -> Native SDK`. There's no need to
add anything from PowerVR SDK to the include directories to build or use GLproxy,
as it already includes all the necessary headers for using OpenGL ES / EGL.
There's also no need to link with anything from PowerVR SDK to build or use
GLproxy, as it loads the necessary libraries at run-time. However, when running
your app, if want to use EGL / OpenGL ES, you'll have to add the directory that
contains the right shared libraries (`GLES_CM`, `GLESv2` and `EGL`) to your
`PATH` environment variable. For instance, if you're on Windows, and used the
default locations when installing PowerVR SDK, then add
`C:\Imagination\PowerVR_Graphics\PowerVR_Tools\PVRVFrame\Library\Windows_x86_64`
to your `PATH` (for Windows 64 bit) or
`C:\Imagination\PowerVR_Graphics\PowerVR_Tools\PVRVFrame\Library\Windows_x86_32`
(for Windows 32 bit). For other platforms it would be something similar. Of
course, feel free to copy the shared libraries somewhere else.

Why not use GLEW?
--------------------

GLEW has several issues:

* Doesn't know about aliases of functions (There are 5 providers of
  glPointParameterfv, for example, and you don't want to have to
  choose which one to call when they're all the same).
* Doesn't support Desktop OpenGL 3.2+ core contexts.
* Doesn't support OpenGL ES.
* Doesn't support EGL.
* Has a hard-to-maintain parser of extension specification text
  instead of using the old .spec file or the new .xml.
* Has significant startup time overhead when `glewInit()`
  autodetects the world.

The motivation for this project came out of previous use of libGLEW in
[piglit](http://piglit.freedesktop.org/).  Other GL dispatch code
generation projects had similar failures.  Ideally, piglit wants to be
able to build a single binary for a test that can run on whatever
context or window system it chooses, not based on link time choices.

We had to solve some of GLEW's problems for piglit and solving them
meant replacing every single piece of GLEW, so we built
piglit-dispatch from scratch.  And since we wanted to reuse it in
other GL-related projects, this is the result.

Multiple-Thread safe and multiple different context in the same thread
---------------
For main thread single opengl context, we have a global constructor to
initiate a GLproxy context to respond to WGL/EGL/GLX/GL calles, and choose
the system default one, for the GL context manager, the detecting order is:
* For Win32, the order is [`WGL`，`EGL`(Google ANGLE) ]
* For Linux, the order is [`GLX`, `EGL`]
* For MacOS, the order is [`CGL`(we provide no proxy for CGL), `GLX`]
* For iOS, there order is [`EAGL`(we provide no proxy for EAGL)]

For GL calls proxy, we first detecting the which type of GL context it is.
then binding the following calls to that context permanantly.
If we want to switch the GL context, using the following APIs to do that:
`glproxy_context_create`
`glproxy_context_get`
`glproxy_context_set`
`glproxy_context_destroy`


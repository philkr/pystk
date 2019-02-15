/* GL dispatch code.
 * This is code-generated from the GL API XML files from Khronos.
 */
#if PLATFORM_HAS_EGL
#include "glproxy/egl.h"

struct egl_dispatch_table {
    PFNEGLBINDAPIPROC glproxy_eglBindAPI;
    PFNEGLBINDTEXIMAGEPROC glproxy_eglBindTexImage;
    PFNEGLCHOOSECONFIGPROC glproxy_eglChooseConfig;
    PFNEGLCLIENTWAITSYNCPROC glproxy_eglClientWaitSync;
    PFNEGLCLIENTWAITSYNCKHRPROC glproxy_eglClientWaitSyncKHR;
    PFNEGLCLIENTWAITSYNCNVPROC glproxy_eglClientWaitSyncNV;
    PFNEGLCOPYBUFFERSPROC glproxy_eglCopyBuffers;
    PFNEGLCREATECONTEXTPROC glproxy_eglCreateContext;
    PFNEGLCREATEDRMIMAGEMESAPROC glproxy_eglCreateDRMImageMESA;
    PFNEGLCREATEFENCESYNCNVPROC glproxy_eglCreateFenceSyncNV;
    PFNEGLCREATEIMAGEPROC glproxy_eglCreateImage;
    PFNEGLCREATEIMAGEKHRPROC glproxy_eglCreateImageKHR;
    PFNEGLCREATENATIVECLIENTBUFFERANDROIDPROC glproxy_eglCreateNativeClientBufferANDROID;
    PFNEGLCREATEPBUFFERFROMCLIENTBUFFERPROC glproxy_eglCreatePbufferFromClientBuffer;
    PFNEGLCREATEPBUFFERSURFACEPROC glproxy_eglCreatePbufferSurface;
    PFNEGLCREATEPIXMAPSURFACEPROC glproxy_eglCreatePixmapSurface;
    PFNEGLCREATEPIXMAPSURFACEHIPROC glproxy_eglCreatePixmapSurfaceHI;
    PFNEGLCREATEPLATFORMPIXMAPSURFACEPROC glproxy_eglCreatePlatformPixmapSurface;
    PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC glproxy_eglCreatePlatformPixmapSurfaceEXT;
    PFNEGLCREATEPLATFORMWINDOWSURFACEPROC glproxy_eglCreatePlatformWindowSurface;
    PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC glproxy_eglCreatePlatformWindowSurfaceEXT;
    PFNEGLCREATESTREAMFROMFILEDESCRIPTORKHRPROC glproxy_eglCreateStreamFromFileDescriptorKHR;
    PFNEGLCREATESTREAMKHRPROC glproxy_eglCreateStreamKHR;
    PFNEGLCREATESTREAMPRODUCERSURFACEKHRPROC glproxy_eglCreateStreamProducerSurfaceKHR;
    PFNEGLCREATESTREAMSYNCNVPROC glproxy_eglCreateStreamSyncNV;
    PFNEGLCREATESYNCPROC glproxy_eglCreateSync;
    PFNEGLCREATESYNC64KHRPROC glproxy_eglCreateSync64KHR;
    PFNEGLCREATESYNCKHRPROC glproxy_eglCreateSyncKHR;
    PFNEGLCREATEWINDOWSURFACEPROC glproxy_eglCreateWindowSurface;
    PFNEGLDEBUGMESSAGECONTROLKHRPROC glproxy_eglDebugMessageControlKHR;
    PFNEGLDESTROYCONTEXTPROC glproxy_eglDestroyContext;
    PFNEGLDESTROYIMAGEPROC glproxy_eglDestroyImage;
    PFNEGLDESTROYIMAGEKHRPROC glproxy_eglDestroyImageKHR;
    PFNEGLDESTROYSTREAMKHRPROC glproxy_eglDestroyStreamKHR;
    PFNEGLDESTROYSURFACEPROC glproxy_eglDestroySurface;
    PFNEGLDESTROYSYNCPROC glproxy_eglDestroySync;
    PFNEGLDESTROYSYNCKHRPROC glproxy_eglDestroySyncKHR;
    PFNEGLDESTROYSYNCNVPROC glproxy_eglDestroySyncNV;
    PFNEGLDUPNATIVEFENCEFDANDROIDPROC glproxy_eglDupNativeFenceFDANDROID;
    PFNEGLEXPORTDMABUFIMAGEMESAPROC glproxy_eglExportDMABUFImageMESA;
    PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC glproxy_eglExportDMABUFImageQueryMESA;
    PFNEGLEXPORTDRMIMAGEMESAPROC glproxy_eglExportDRMImageMESA;
    PFNEGLFENCENVPROC glproxy_eglFenceNV;
    PFNEGLGETCONFIGATTRIBPROC glproxy_eglGetConfigAttrib;
    PFNEGLGETCONFIGSPROC glproxy_eglGetConfigs;
    PFNEGLGETCURRENTCONTEXTPROC glproxy_eglGetCurrentContext;
    PFNEGLGETCURRENTDISPLAYPROC glproxy_eglGetCurrentDisplay;
    PFNEGLGETCURRENTSURFACEPROC glproxy_eglGetCurrentSurface;
    PFNEGLGETDISPLAYPROC glproxy_eglGetDisplay;
    PFNEGLGETERRORPROC glproxy_eglGetError;
    PFNEGLGETOUTPUTLAYERSEXTPROC glproxy_eglGetOutputLayersEXT;
    PFNEGLGETOUTPUTPORTSEXTPROC glproxy_eglGetOutputPortsEXT;
    PFNEGLGETPLATFORMDISPLAYPROC glproxy_eglGetPlatformDisplay;
    PFNEGLGETPLATFORMDISPLAYEXTPROC glproxy_eglGetPlatformDisplayEXT;
    PFNEGLGETPROCADDRESSPROC glproxy_eglGetProcAddress;
    PFNEGLGETSTREAMFILEDESCRIPTORKHRPROC glproxy_eglGetStreamFileDescriptorKHR;
    PFNEGLGETSYNCATTRIBPROC glproxy_eglGetSyncAttrib;
    PFNEGLGETSYNCATTRIBKHRPROC glproxy_eglGetSyncAttribKHR;
    PFNEGLGETSYNCATTRIBNVPROC glproxy_eglGetSyncAttribNV;
    PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC glproxy_eglGetSystemTimeFrequencyNV;
    PFNEGLGETSYSTEMTIMENVPROC glproxy_eglGetSystemTimeNV;
    PFNEGLINITIALIZEPROC glproxy_eglInitialize;
    PFNEGLLABELOBJECTKHRPROC glproxy_eglLabelObjectKHR;
    PFNEGLLOCKSURFACEKHRPROC glproxy_eglLockSurfaceKHR;
    PFNEGLMAKECURRENTPROC glproxy_eglMakeCurrent;
    PFNEGLOUTPUTLAYERATTRIBEXTPROC glproxy_eglOutputLayerAttribEXT;
    PFNEGLOUTPUTPORTATTRIBEXTPROC glproxy_eglOutputPortAttribEXT;
    PFNEGLPOSTSUBBUFFERNVPROC glproxy_eglPostSubBufferNV;
    PFNEGLPRESENTATIONTIMEANDROIDPROC glproxy_eglPresentationTimeANDROID;
    PFNEGLQUERYAPIPROC glproxy_eglQueryAPI;
    PFNEGLQUERYCONTEXTPROC glproxy_eglQueryContext;
    PFNEGLQUERYDEBUGKHRPROC glproxy_eglQueryDebugKHR;
    PFNEGLQUERYDEVICEATTRIBEXTPROC glproxy_eglQueryDeviceAttribEXT;
    PFNEGLQUERYDEVICESTRINGEXTPROC glproxy_eglQueryDeviceStringEXT;
    PFNEGLQUERYDEVICESEXTPROC glproxy_eglQueryDevicesEXT;
    PFNEGLQUERYDISPLAYATTRIBEXTPROC glproxy_eglQueryDisplayAttribEXT;
    PFNEGLQUERYDISPLAYATTRIBNVPROC glproxy_eglQueryDisplayAttribNV;
    PFNEGLQUERYNATIVEDISPLAYNVPROC glproxy_eglQueryNativeDisplayNV;
    PFNEGLQUERYNATIVEPIXMAPNVPROC glproxy_eglQueryNativePixmapNV;
    PFNEGLQUERYNATIVEWINDOWNVPROC glproxy_eglQueryNativeWindowNV;
    PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC glproxy_eglQueryOutputLayerAttribEXT;
    PFNEGLQUERYOUTPUTLAYERSTRINGEXTPROC glproxy_eglQueryOutputLayerStringEXT;
    PFNEGLQUERYOUTPUTPORTATTRIBEXTPROC glproxy_eglQueryOutputPortAttribEXT;
    PFNEGLQUERYOUTPUTPORTSTRINGEXTPROC glproxy_eglQueryOutputPortStringEXT;
    PFNEGLQUERYSTREAMKHRPROC glproxy_eglQueryStreamKHR;
    PFNEGLQUERYSTREAMMETADATANVPROC glproxy_eglQueryStreamMetadataNV;
    PFNEGLQUERYSTREAMTIMEKHRPROC glproxy_eglQueryStreamTimeKHR;
    PFNEGLQUERYSTREAMU64KHRPROC glproxy_eglQueryStreamu64KHR;
    PFNEGLQUERYSTRINGPROC glproxy_eglQueryString;
    PFNEGLQUERYSURFACEPROC glproxy_eglQuerySurface;
    PFNEGLQUERYSURFACE64KHRPROC glproxy_eglQuerySurface64KHR;
    PFNEGLQUERYSURFACEPOINTERANGLEPROC glproxy_eglQuerySurfacePointerANGLE;
    PFNEGLRELEASETEXIMAGEPROC glproxy_eglReleaseTexImage;
    PFNEGLRELEASETHREADPROC glproxy_eglReleaseThread;
    PFNEGLSETBLOBCACHEFUNCSANDROIDPROC glproxy_eglSetBlobCacheFuncsANDROID;
    PFNEGLSETDAMAGEREGIONKHRPROC glproxy_eglSetDamageRegionKHR;
    PFNEGLSETSTREAMMETADATANVPROC glproxy_eglSetStreamMetadataNV;
    PFNEGLSIGNALSYNCKHRPROC glproxy_eglSignalSyncKHR;
    PFNEGLSIGNALSYNCNVPROC glproxy_eglSignalSyncNV;
    PFNEGLSTREAMATTRIBKHRPROC glproxy_eglStreamAttribKHR;
    PFNEGLSTREAMCONSUMERACQUIREKHRPROC glproxy_eglStreamConsumerAcquireKHR;
    PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALATTRIBSNVPROC glproxy_eglStreamConsumerGLTextureExternalAttribsNV;
    PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC glproxy_eglStreamConsumerGLTextureExternalKHR;
    PFNEGLSTREAMCONSUMEROUTPUTEXTPROC glproxy_eglStreamConsumerOutputEXT;
    PFNEGLSTREAMCONSUMERRELEASEKHRPROC glproxy_eglStreamConsumerReleaseKHR;
    PFNEGLSURFACEATTRIBPROC glproxy_eglSurfaceAttrib;
    PFNEGLSWAPBUFFERSPROC glproxy_eglSwapBuffers;
    PFNEGLSWAPBUFFERSREGION2NOKPROC glproxy_eglSwapBuffersRegion2NOK;
    PFNEGLSWAPBUFFERSREGIONNOKPROC glproxy_eglSwapBuffersRegionNOK;
    PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC glproxy_eglSwapBuffersWithDamageEXT;
    PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC glproxy_eglSwapBuffersWithDamageKHR;
    PFNEGLSWAPINTERVALPROC glproxy_eglSwapInterval;
    PFNEGLTERMINATEPROC glproxy_eglTerminate;
    PFNEGLUNLOCKSURFACEKHRPROC glproxy_eglUnlockSurfaceKHR;
    PFNEGLWAITCLIENTPROC glproxy_eglWaitClient;
    PFNEGLWAITGLPROC glproxy_eglWaitGL;
    PFNEGLWAITNATIVEPROC glproxy_eglWaitNative;
    PFNEGLWAITSYNCPROC glproxy_eglWaitSync;
    PFNEGLWAITSYNCKHRPROC glproxy_eglWaitSyncKHR;
};

#define EGL_EXTENSIONS_BITMAP_COUNT 4

enum egl_provider_versions {
    EGL_1_0 = 10,
    EGL_1_1 = 11,
    EGL_1_2 = 12,
    EGL_1_4 = 14,
    EGL_1_5 = 15,
} PACKED;


#endif /* PLATFORM_HAS_EGL */

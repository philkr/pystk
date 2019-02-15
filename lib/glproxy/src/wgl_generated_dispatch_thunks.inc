/* GL dispatch code.
 * This is code-generated from the GL API XML files from Khronos.
 */
#include "dispatch_common.h"
#if PLATFORM_HAS_WGL

#define wgl_extensions_count 53

static const char wgl_extension_enum_strings[] =
    "WGL_3DFX_multisample\0"
    "WGL_3DL_stereo_control\0"
    "WGL_AMD_gpu_association\0"
    "WGL_ARB_buffer_region\0"
    "WGL_ARB_context_flush_control\0"
    "WGL_ARB_create_context\0"
    "WGL_ARB_create_context_profile\0"
    "WGL_ARB_create_context_robustness\0"
    "WGL_ARB_extensions_string\0"
    "WGL_ARB_framebuffer_sRGB\0"
    "WGL_ARB_make_current_read\0"
    "WGL_ARB_multisample\0"
    "WGL_ARB_pbuffer\0"
    "WGL_ARB_pixel_format\0"
    "WGL_ARB_pixel_format_float\0"
    "WGL_ARB_render_texture\0"
    "WGL_ARB_robustness_application_isolation\0"
    "WGL_ARB_robustness_share_group_isolation\0"
    "WGL_ATI_pixel_format_float\0"
    "WGL_EXT_create_context_es2_profile\0"
    "WGL_EXT_create_context_es_profile\0"
    "WGL_EXT_depth_float\0"
    "WGL_EXT_display_color_table\0"
    "WGL_EXT_extensions_string\0"
    "WGL_EXT_framebuffer_sRGB\0"
    "WGL_EXT_make_current_read\0"
    "WGL_EXT_multisample\0"
    "WGL_EXT_pbuffer\0"
    "WGL_EXT_pixel_format\0"
    "WGL_EXT_pixel_format_packed_float\0"
    "WGL_EXT_swap_control\0"
    "WGL_EXT_swap_control_tear\0"
    "WGL_I3D_digital_video_control\0"
    "WGL_I3D_gamma\0"
    "WGL_I3D_genlock\0"
    "WGL_I3D_image_buffer\0"
    "WGL_I3D_swap_frame_lock\0"
    "WGL_I3D_swap_frame_usage\0"
    "WGL_NV_DX_interop\0"
    "WGL_NV_DX_interop2\0"
    "WGL_NV_copy_image\0"
    "WGL_NV_delay_before_swap\0"
    "WGL_NV_float_buffer\0"
    "WGL_NV_gpu_affinity\0"
    "WGL_NV_multisample_coverage\0"
    "WGL_NV_present_video\0"
    "WGL_NV_render_depth_texture\0"
    "WGL_NV_render_texture_rectangle\0"
    "WGL_NV_swap_group\0"
    "WGL_NV_vertex_array_range\0"
    "WGL_NV_video_capture\0"
    "WGL_NV_video_output\0"
    "WGL_OML_sync_control\0"
;
static const khronos_uint16_t wgl_extension_offsets[] = {
    0,
    21,
    44,
    68,
    90,
    120,
    143,
    174,
    208,
    234,
    259,
    285,
    305,
    321,
    342,
    369,
    392,
    433,
    474,
    501,
    536,
    570,
    590,
    618,
    644,
    669,
    695,
    715,
    731,
    752,
    786,
    807,
    833,
    863,
    877,
    893,
    914,
    938,
    963,
    981,
    1000,
    1018,
    1043,
    1063,
    1083,
    1111,
    1132,
    1160,
    1192,
    1210,
    1236,
    1257,
    1277,
    1298
};

static const khronos_uint8_t wgl_entrypoint_strings[] = {
    119, 103, 108, 65, 108, 108, 111, 99, 97, 116, 101, 77, 101, 109, 111, 114, 121, 78, 86, 0, /*wglAllocateMemoryNV*/
    119, 103, 108, 65, 115, 115, 111, 99, 105, 97, 116, 101, 73, 109, 97, 103, 101, 66, 117, 102, 102, 101, 114, 69, 118, 101, 110, 116, 115, 73, 51, 68, 0, /*wglAssociateImageBufferEventsI3D*/
    119, 103, 108, 66, 101, 103, 105, 110, 70, 114, 97, 109, 101, 84, 114, 97, 99, 107, 105, 110, 103, 73, 51, 68, 0, /*wglBeginFrameTrackingI3D*/
    119, 103, 108, 66, 105, 110, 100, 68, 105, 115, 112, 108, 97, 121, 67, 111, 108, 111, 114, 84, 97, 98, 108, 101, 69, 88, 84, 0, /*wglBindDisplayColorTableEXT*/
    119, 103, 108, 66, 105, 110, 100, 83, 119, 97, 112, 66, 97, 114, 114, 105, 101, 114, 78, 86, 0, /*wglBindSwapBarrierNV*/
    119, 103, 108, 66, 105, 110, 100, 84, 101, 120, 73, 109, 97, 103, 101, 65, 82, 66, 0, /*wglBindTexImageARB*/
    119, 103, 108, 66, 105, 110, 100, 86, 105, 100, 101, 111, 67, 97, 112, 116, 117, 114, 101, 68, 101, 118, 105, 99, 101, 78, 86, 0, /*wglBindVideoCaptureDeviceNV*/
    119, 103, 108, 66, 105, 110, 100, 86, 105, 100, 101, 111, 68, 101, 118, 105, 99, 101, 78, 86, 0, /*wglBindVideoDeviceNV*/
    119, 103, 108, 66, 105, 110, 100, 86, 105, 100, 101, 111, 73, 109, 97, 103, 101, 78, 86, 0, /*wglBindVideoImageNV*/
    119, 103, 108, 66, 108, 105, 116, 67, 111, 110, 116, 101, 120, 116, 70, 114, 97, 109, 101, 98, 117, 102, 102, 101, 114, 65, 77, 68, 0, /*wglBlitContextFramebufferAMD*/
    119, 103, 108, 67, 104, 111, 111, 115, 101, 80, 105, 120, 101, 108, 70, 111, 114, 109, 97, 116, 0, /*wglChoosePixelFormat*/
    119, 103, 108, 67, 104, 111, 111, 115, 101, 80, 105, 120, 101, 108, 70, 111, 114, 109, 97, 116, 65, 82, 66, 0, /*wglChoosePixelFormatARB*/
    119, 103, 108, 67, 104, 111, 111, 115, 101, 80, 105, 120, 101, 108, 70, 111, 114, 109, 97, 116, 69, 88, 84, 0, /*wglChoosePixelFormatEXT*/
    119, 103, 108, 67, 111, 112, 121, 67, 111, 110, 116, 101, 120, 116, 0, /*wglCopyContext*/
    119, 103, 108, 67, 111, 112, 121, 73, 109, 97, 103, 101, 83, 117, 98, 68, 97, 116, 97, 78, 86, 0, /*wglCopyImageSubDataNV*/
    119, 103, 108, 67, 114, 101, 97, 116, 101, 65, 102, 102, 105, 110, 105, 116, 121, 68, 67, 78, 86, 0, /*wglCreateAffinityDCNV*/
    119, 103, 108, 67, 114, 101, 97, 116, 101, 65, 115, 115, 111, 99, 105, 97, 116, 101, 100, 67, 111, 110, 116, 101, 120, 116, 65, 77, 68, 0, /*wglCreateAssociatedContextAMD*/
    119, 103, 108, 67, 114, 101, 97, 116, 101, 65, 115, 115, 111, 99, 105, 97, 116, 101, 100, 67, 111, 110, 116, 101, 120, 116, 65, 116, 116, 114, 105, 98, 115, 65, 77, 68, 0, /*wglCreateAssociatedContextAttribsAMD*/
    119, 103, 108, 67, 114, 101, 97, 116, 101, 66, 117, 102, 102, 101, 114, 82, 101, 103, 105, 111, 110, 65, 82, 66, 0, /*wglCreateBufferRegionARB*/
    119, 103, 108, 67, 114, 101, 97, 116, 101, 67, 111, 110, 116, 101, 120, 116, 0, /*wglCreateContext*/
    119, 103, 108, 67, 114, 101, 97, 116, 101, 67, 111, 110, 116, 101, 120, 116, 65, 116, 116, 114, 105, 98, 115, 65, 82, 66, 0, /*wglCreateContextAttribsARB*/
    119, 103, 108, 67, 114, 101, 97, 116, 101, 68, 105, 115, 112, 108, 97, 121, 67, 111, 108, 111, 114, 84, 97, 98, 108, 101, 69, 88, 84, 0, /*wglCreateDisplayColorTableEXT*/
    119, 103, 108, 67, 114, 101, 97, 116, 101, 73, 109, 97, 103, 101, 66, 117, 102, 102, 101, 114, 73, 51, 68, 0, /*wglCreateImageBufferI3D*/
    119, 103, 108, 67, 114, 101, 97, 116, 101, 76, 97, 121, 101, 114, 67, 111, 110, 116, 101, 120, 116, 0, /*wglCreateLayerContext*/
    119, 103, 108, 67, 114, 101, 97, 116, 101, 80, 98, 117, 102, 102, 101, 114, 65, 82, 66, 0, /*wglCreatePbufferARB*/
    119, 103, 108, 67, 114, 101, 97, 116, 101, 80, 98, 117, 102, 102, 101, 114, 69, 88, 84, 0, /*wglCreatePbufferEXT*/
    119, 103, 108, 68, 88, 67, 108, 111, 115, 101, 68, 101, 118, 105, 99, 101, 78, 86, 0, /*wglDXCloseDeviceNV*/
    119, 103, 108, 68, 88, 76, 111, 99, 107, 79, 98, 106, 101, 99, 116, 115, 78, 86, 0, /*wglDXLockObjectsNV*/
    119, 103, 108, 68, 88, 79, 98, 106, 101, 99, 116, 65, 99, 99, 101, 115, 115, 78, 86, 0, /*wglDXObjectAccessNV*/
    119, 103, 108, 68, 88, 79, 112, 101, 110, 68, 101, 118, 105, 99, 101, 78, 86, 0, /*wglDXOpenDeviceNV*/
    119, 103, 108, 68, 88, 82, 101, 103, 105, 115, 116, 101, 114, 79, 98, 106, 101, 99, 116, 78, 86, 0, /*wglDXRegisterObjectNV*/
    119, 103, 108, 68, 88, 83, 101, 116, 82, 101, 115, 111, 117, 114, 99, 101, 83, 104, 97, 114, 101, 72, 97, 110, 100, 108, 101, 78, 86, 0, /*wglDXSetResourceShareHandleNV*/
    119, 103, 108, 68, 88, 85, 110, 108, 111, 99, 107, 79, 98, 106, 101, 99, 116, 115, 78, 86, 0, /*wglDXUnlockObjectsNV*/
    119, 103, 108, 68, 88, 85, 110, 114, 101, 103, 105, 115, 116, 101, 114, 79, 98, 106, 101, 99, 116, 78, 86, 0, /*wglDXUnregisterObjectNV*/
    119, 103, 108, 68, 101, 108, 97, 121, 66, 101, 102, 111, 114, 101, 83, 119, 97, 112, 78, 86, 0, /*wglDelayBeforeSwapNV*/
    119, 103, 108, 68, 101, 108, 101, 116, 101, 65, 115, 115, 111, 99, 105, 97, 116, 101, 100, 67, 111, 110, 116, 101, 120, 116, 65, 77, 68, 0, /*wglDeleteAssociatedContextAMD*/
    119, 103, 108, 68, 101, 108, 101, 116, 101, 66, 117, 102, 102, 101, 114, 82, 101, 103, 105, 111, 110, 65, 82, 66, 0, /*wglDeleteBufferRegionARB*/
    119, 103, 108, 68, 101, 108, 101, 116, 101, 67, 111, 110, 116, 101, 120, 116, 0, /*wglDeleteContext*/
    119, 103, 108, 68, 101, 108, 101, 116, 101, 68, 67, 78, 86, 0, /*wglDeleteDCNV*/
    119, 103, 108, 68, 101, 115, 99, 114, 105, 98, 101, 76, 97, 121, 101, 114, 80, 108, 97, 110, 101, 0, /*wglDescribeLayerPlane*/
    119, 103, 108, 68, 101, 115, 99, 114, 105, 98, 101, 80, 105, 120, 101, 108, 70, 111, 114, 109, 97, 116, 0, /*wglDescribePixelFormat*/
    119, 103, 108, 68, 101, 115, 116, 114, 111, 121, 68, 105, 115, 112, 108, 97, 121, 67, 111, 108, 111, 114, 84, 97, 98, 108, 101, 69, 88, 84, 0, /*wglDestroyDisplayColorTableEXT*/
    119, 103, 108, 68, 101, 115, 116, 114, 111, 121, 73, 109, 97, 103, 101, 66, 117, 102, 102, 101, 114, 73, 51, 68, 0, /*wglDestroyImageBufferI3D*/
    119, 103, 108, 68, 101, 115, 116, 114, 111, 121, 80, 98, 117, 102, 102, 101, 114, 65, 82, 66, 0, /*wglDestroyPbufferARB*/
    119, 103, 108, 68, 101, 115, 116, 114, 111, 121, 80, 98, 117, 102, 102, 101, 114, 69, 88, 84, 0, /*wglDestroyPbufferEXT*/
    119, 103, 108, 68, 105, 115, 97, 98, 108, 101, 70, 114, 97, 109, 101, 76, 111, 99, 107, 73, 51, 68, 0, /*wglDisableFrameLockI3D*/
    119, 103, 108, 68, 105, 115, 97, 98, 108, 101, 71, 101, 110, 108, 111, 99, 107, 73, 51, 68, 0, /*wglDisableGenlockI3D*/
    119, 103, 108, 69, 110, 97, 98, 108, 101, 70, 114, 97, 109, 101, 76, 111, 99, 107, 73, 51, 68, 0, /*wglEnableFrameLockI3D*/
    119, 103, 108, 69, 110, 97, 98, 108, 101, 71, 101, 110, 108, 111, 99, 107, 73, 51, 68, 0, /*wglEnableGenlockI3D*/
    119, 103, 108, 69, 110, 100, 70, 114, 97, 109, 101, 84, 114, 97, 99, 107, 105, 110, 103, 73, 51, 68, 0, /*wglEndFrameTrackingI3D*/
    119, 103, 108, 69, 110, 117, 109, 71, 112, 117, 68, 101, 118, 105, 99, 101, 115, 78, 86, 0, /*wglEnumGpuDevicesNV*/
    119, 103, 108, 69, 110, 117, 109, 71, 112, 117, 115, 70, 114, 111, 109, 65, 102, 102, 105, 110, 105, 116, 121, 68, 67, 78, 86, 0, /*wglEnumGpusFromAffinityDCNV*/
    119, 103, 108, 69, 110, 117, 109, 71, 112, 117, 115, 78, 86, 0, /*wglEnumGpusNV*/
    119, 103, 108, 69, 110, 117, 109, 101, 114, 97, 116, 101, 86, 105, 100, 101, 111, 67, 97, 112, 116, 117, 114, 101, 68, 101, 118, 105, 99, 101, 115, 78, 86, 0, /*wglEnumerateVideoCaptureDevicesNV*/
    119, 103, 108, 69, 110, 117, 109, 101, 114, 97, 116, 101, 86, 105, 100, 101, 111, 68, 101, 118, 105, 99, 101, 115, 78, 86, 0, /*wglEnumerateVideoDevicesNV*/
    119, 103, 108, 70, 114, 101, 101, 77, 101, 109, 111, 114, 121, 78, 86, 0, /*wglFreeMemoryNV*/
    119, 103, 108, 71, 101, 110, 108, 111, 99, 107, 83, 97, 109, 112, 108, 101, 82, 97, 116, 101, 73, 51, 68, 0, /*wglGenlockSampleRateI3D*/
    119, 103, 108, 71, 101, 110, 108, 111, 99, 107, 83, 111, 117, 114, 99, 101, 68, 101, 108, 97, 121, 73, 51, 68, 0, /*wglGenlockSourceDelayI3D*/
    119, 103, 108, 71, 101, 110, 108, 111, 99, 107, 83, 111, 117, 114, 99, 101, 69, 100, 103, 101, 73, 51, 68, 0, /*wglGenlockSourceEdgeI3D*/
    119, 103, 108, 71, 101, 110, 108, 111, 99, 107, 83, 111, 117, 114, 99, 101, 73, 51, 68, 0, /*wglGenlockSourceI3D*/
    119, 103, 108, 71, 101, 116, 67, 111, 110, 116, 101, 120, 116, 71, 80, 85, 73, 68, 65, 77, 68, 0, /*wglGetContextGPUIDAMD*/
    119, 103, 108, 71, 101, 116, 67, 117, 114, 114, 101, 110, 116, 65, 115, 115, 111, 99, 105, 97, 116, 101, 100, 67, 111, 110, 116, 101, 120, 116, 65, 77, 68, 0, /*wglGetCurrentAssociatedContextAMD*/
    119, 103, 108, 71, 101, 116, 67, 117, 114, 114, 101, 110, 116, 67, 111, 110, 116, 101, 120, 116, 0, /*wglGetCurrentContext*/
    119, 103, 108, 71, 101, 116, 67, 117, 114, 114, 101, 110, 116, 68, 67, 0, /*wglGetCurrentDC*/
    119, 103, 108, 71, 101, 116, 67, 117, 114, 114, 101, 110, 116, 82, 101, 97, 100, 68, 67, 65, 82, 66, 0, /*wglGetCurrentReadDCARB*/
    119, 103, 108, 71, 101, 116, 67, 117, 114, 114, 101, 110, 116, 82, 101, 97, 100, 68, 67, 69, 88, 84, 0, /*wglGetCurrentReadDCEXT*/
    119, 103, 108, 71, 101, 116, 68, 101, 102, 97, 117, 108, 116, 80, 114, 111, 99, 65, 100, 100, 114, 101, 115, 115, 0, /*wglGetDefaultProcAddress*/
    119, 103, 108, 71, 101, 116, 68, 105, 103, 105, 116, 97, 108, 86, 105, 100, 101, 111, 80, 97, 114, 97, 109, 101, 116, 101, 114, 115, 73, 51, 68, 0, /*wglGetDigitalVideoParametersI3D*/
    119, 103, 108, 71, 101, 116, 69, 110, 104, 77, 101, 116, 97, 70, 105, 108, 101, 80, 105, 120, 101, 108, 70, 111, 114, 109, 97, 116, 0, /*wglGetEnhMetaFilePixelFormat*/
    119, 103, 108, 71, 101, 116, 69, 120, 116, 101, 110, 115, 105, 111, 110, 115, 83, 116, 114, 105, 110, 103, 65, 82, 66, 0, /*wglGetExtensionsStringARB*/
    119, 103, 108, 71, 101, 116, 69, 120, 116, 101, 110, 115, 105, 111, 110, 115, 83, 116, 114, 105, 110, 103, 69, 88, 84, 0, /*wglGetExtensionsStringEXT*/
    119, 103, 108, 71, 101, 116, 70, 114, 97, 109, 101, 85, 115, 97, 103, 101, 73, 51, 68, 0, /*wglGetFrameUsageI3D*/
    119, 103, 108, 71, 101, 116, 71, 80, 85, 73, 68, 115, 65, 77, 68, 0, /*wglGetGPUIDsAMD*/
    119, 103, 108, 71, 101, 116, 71, 80, 85, 73, 110, 102, 111, 65, 77, 68, 0, /*wglGetGPUInfoAMD*/
    119, 103, 108, 71, 101, 116, 71, 97, 109, 109, 97, 84, 97, 98, 108, 101, 73, 51, 68, 0, /*wglGetGammaTableI3D*/
    119, 103, 108, 71, 101, 116, 71, 97, 109, 109, 97, 84, 97, 98, 108, 101, 80, 97, 114, 97, 109, 101, 116, 101, 114, 115, 73, 51, 68, 0, /*wglGetGammaTableParametersI3D*/
    119, 103, 108, 71, 101, 116, 71, 101, 110, 108, 111, 99, 107, 83, 97, 109, 112, 108, 101, 82, 97, 116, 101, 73, 51, 68, 0, /*wglGetGenlockSampleRateI3D*/
    119, 103, 108, 71, 101, 116, 71, 101, 110, 108, 111, 99, 107, 83, 111, 117, 114, 99, 101, 68, 101, 108, 97, 121, 73, 51, 68, 0, /*wglGetGenlockSourceDelayI3D*/
    119, 103, 108, 71, 101, 116, 71, 101, 110, 108, 111, 99, 107, 83, 111, 117, 114, 99, 101, 69, 100, 103, 101, 73, 51, 68, 0, /*wglGetGenlockSourceEdgeI3D*/
    119, 103, 108, 71, 101, 116, 71, 101, 110, 108, 111, 99, 107, 83, 111, 117, 114, 99, 101, 73, 51, 68, 0, /*wglGetGenlockSourceI3D*/
    119, 103, 108, 71, 101, 116, 76, 97, 121, 101, 114, 80, 97, 108, 101, 116, 116, 101, 69, 110, 116, 114, 105, 101, 115, 0, /*wglGetLayerPaletteEntries*/
    119, 103, 108, 71, 101, 116, 77, 115, 99, 82, 97, 116, 101, 79, 77, 76, 0, /*wglGetMscRateOML*/
    119, 103, 108, 71, 101, 116, 80, 98, 117, 102, 102, 101, 114, 68, 67, 65, 82, 66, 0, /*wglGetPbufferDCARB*/
    119, 103, 108, 71, 101, 116, 80, 98, 117, 102, 102, 101, 114, 68, 67, 69, 88, 84, 0, /*wglGetPbufferDCEXT*/
    119, 103, 108, 71, 101, 116, 80, 105, 120, 101, 108, 70, 111, 114, 109, 97, 116, 0, /*wglGetPixelFormat*/
    119, 103, 108, 71, 101, 116, 80, 105, 120, 101, 108, 70, 111, 114, 109, 97, 116, 65, 116, 116, 114, 105, 98, 102, 118, 65, 82, 66, 0, /*wglGetPixelFormatAttribfvARB*/
    119, 103, 108, 71, 101, 116, 80, 105, 120, 101, 108, 70, 111, 114, 109, 97, 116, 65, 116, 116, 114, 105, 98, 102, 118, 69, 88, 84, 0, /*wglGetPixelFormatAttribfvEXT*/
    119, 103, 108, 71, 101, 116, 80, 105, 120, 101, 108, 70, 111, 114, 109, 97, 116, 65, 116, 116, 114, 105, 98, 105, 118, 65, 82, 66, 0, /*wglGetPixelFormatAttribivARB*/
    119, 103, 108, 71, 101, 116, 80, 105, 120, 101, 108, 70, 111, 114, 109, 97, 116, 65, 116, 116, 114, 105, 98, 105, 118, 69, 88, 84, 0, /*wglGetPixelFormatAttribivEXT*/
    119, 103, 108, 71, 101, 116, 80, 114, 111, 99, 65, 100, 100, 114, 101, 115, 115, 0, /*wglGetProcAddress*/
    119, 103, 108, 71, 101, 116, 83, 119, 97, 112, 73, 110, 116, 101, 114, 118, 97, 108, 69, 88, 84, 0, /*wglGetSwapIntervalEXT*/
    119, 103, 108, 71, 101, 116, 83, 121, 110, 99, 86, 97, 108, 117, 101, 115, 79, 77, 76, 0, /*wglGetSyncValuesOML*/
    119, 103, 108, 71, 101, 116, 86, 105, 100, 101, 111, 68, 101, 118, 105, 99, 101, 78, 86, 0, /*wglGetVideoDeviceNV*/
    119, 103, 108, 71, 101, 116, 86, 105, 100, 101, 111, 73, 110, 102, 111, 78, 86, 0, /*wglGetVideoInfoNV*/
    119, 103, 108, 73, 115, 69, 110, 97, 98, 108, 101, 100, 70, 114, 97, 109, 101, 76, 111, 99, 107, 73, 51, 68, 0, /*wglIsEnabledFrameLockI3D*/
    119, 103, 108, 73, 115, 69, 110, 97, 98, 108, 101, 100, 71, 101, 110, 108, 111, 99, 107, 73, 51, 68, 0, /*wglIsEnabledGenlockI3D*/
    119, 103, 108, 74, 111, 105, 110, 83, 119, 97, 112, 71, 114, 111, 117, 112, 78, 86, 0, /*wglJoinSwapGroupNV*/
    119, 103, 108, 76, 111, 97, 100, 68, 105, 115, 112, 108, 97, 121, 67, 111, 108, 111, 114, 84, 97, 98, 108, 101, 69, 88, 84, 0, /*wglLoadDisplayColorTableEXT*/
    119, 103, 108, 76, 111, 99, 107, 86, 105, 100, 101, 111, 67, 97, 112, 116, 117, 114, 101, 68, 101, 118, 105, 99, 101, 78, 86, 0, /*wglLockVideoCaptureDeviceNV*/
    119, 103, 108, 77, 97, 107, 101, 65, 115, 115, 111, 99, 105, 97, 116, 101, 100, 67, 111, 110, 116, 101, 120, 116, 67, 117, 114, 114, 101, 110, 116, 65, 77, 68, 0, /*wglMakeAssociatedContextCurrentAMD*/
    119, 103, 108, 77, 97, 107, 101, 67, 111, 110, 116, 101, 120, 116, 67, 117, 114, 114, 101, 110, 116, 65, 82, 66, 0, /*wglMakeContextCurrentARB*/
    119, 103, 108, 77, 97, 107, 101, 67, 111, 110, 116, 101, 120, 116, 67, 117, 114, 114, 101, 110, 116, 69, 88, 84, 0, /*wglMakeContextCurrentEXT*/
    119, 103, 108, 77, 97, 107, 101, 67, 117, 114, 114, 101, 110, 116, 0, /*wglMakeCurrent*/
    119, 103, 108, 81, 117, 101, 114, 121, 67, 117, 114, 114, 101, 110, 116, 67, 111, 110, 116, 101, 120, 116, 78, 86, 0, /*wglQueryCurrentContextNV*/
    119, 103, 108, 81, 117, 101, 114, 121, 70, 114, 97, 109, 101, 67, 111, 117, 110, 116, 78, 86, 0, /*wglQueryFrameCountNV*/
    119, 103, 108, 81, 117, 101, 114, 121, 70, 114, 97, 109, 101, 76, 111, 99, 107, 77, 97, 115, 116, 101, 114, 73, 51, 68, 0, /*wglQueryFrameLockMasterI3D*/
    119, 103, 108, 81, 117, 101, 114, 121, 70, 114, 97, 109, 101, 84, 114, 97, 99, 107, 105, 110, 103, 73, 51, 68, 0, /*wglQueryFrameTrackingI3D*/
    119, 103, 108, 81, 117, 101, 114, 121, 71, 101, 110, 108, 111, 99, 107, 77, 97, 120, 83, 111, 117, 114, 99, 101, 68, 101, 108, 97, 121, 73, 51, 68, 0, /*wglQueryGenlockMaxSourceDelayI3D*/
    119, 103, 108, 81, 117, 101, 114, 121, 77, 97, 120, 83, 119, 97, 112, 71, 114, 111, 117, 112, 115, 78, 86, 0, /*wglQueryMaxSwapGroupsNV*/
    119, 103, 108, 81, 117, 101, 114, 121, 80, 98, 117, 102, 102, 101, 114, 65, 82, 66, 0, /*wglQueryPbufferARB*/
    119, 103, 108, 81, 117, 101, 114, 121, 80, 98, 117, 102, 102, 101, 114, 69, 88, 84, 0, /*wglQueryPbufferEXT*/
    119, 103, 108, 81, 117, 101, 114, 121, 83, 119, 97, 112, 71, 114, 111, 117, 112, 78, 86, 0, /*wglQuerySwapGroupNV*/
    119, 103, 108, 81, 117, 101, 114, 121, 86, 105, 100, 101, 111, 67, 97, 112, 116, 117, 114, 101, 68, 101, 118, 105, 99, 101, 78, 86, 0, /*wglQueryVideoCaptureDeviceNV*/
    119, 103, 108, 82, 101, 97, 108, 105, 122, 101, 76, 97, 121, 101, 114, 80, 97, 108, 101, 116, 116, 101, 0, /*wglRealizeLayerPalette*/
    119, 103, 108, 82, 101, 108, 101, 97, 115, 101, 73, 109, 97, 103, 101, 66, 117, 102, 102, 101, 114, 69, 118, 101, 110, 116, 115, 73, 51, 68, 0, /*wglReleaseImageBufferEventsI3D*/
    119, 103, 108, 82, 101, 108, 101, 97, 115, 101, 80, 98, 117, 102, 102, 101, 114, 68, 67, 65, 82, 66, 0, /*wglReleasePbufferDCARB*/
    119, 103, 108, 82, 101, 108, 101, 97, 115, 101, 80, 98, 117, 102, 102, 101, 114, 68, 67, 69, 88, 84, 0, /*wglReleasePbufferDCEXT*/
    119, 103, 108, 82, 101, 108, 101, 97, 115, 101, 84, 101, 120, 73, 109, 97, 103, 101, 65, 82, 66, 0, /*wglReleaseTexImageARB*/
    119, 103, 108, 82, 101, 108, 101, 97, 115, 101, 86, 105, 100, 101, 111, 67, 97, 112, 116, 117, 114, 101, 68, 101, 118, 105, 99, 101, 78, 86, 0, /*wglReleaseVideoCaptureDeviceNV*/
    119, 103, 108, 82, 101, 108, 101, 97, 115, 101, 86, 105, 100, 101, 111, 68, 101, 118, 105, 99, 101, 78, 86, 0, /*wglReleaseVideoDeviceNV*/
    119, 103, 108, 82, 101, 108, 101, 97, 115, 101, 86, 105, 100, 101, 111, 73, 109, 97, 103, 101, 78, 86, 0, /*wglReleaseVideoImageNV*/
    119, 103, 108, 82, 101, 115, 101, 116, 70, 114, 97, 109, 101, 67, 111, 117, 110, 116, 78, 86, 0, /*wglResetFrameCountNV*/
    119, 103, 108, 82, 101, 115, 116, 111, 114, 101, 66, 117, 102, 102, 101, 114, 82, 101, 103, 105, 111, 110, 65, 82, 66, 0, /*wglRestoreBufferRegionARB*/
    119, 103, 108, 83, 97, 118, 101, 66, 117, 102, 102, 101, 114, 82, 101, 103, 105, 111, 110, 65, 82, 66, 0, /*wglSaveBufferRegionARB*/
    119, 103, 108, 83, 101, 110, 100, 80, 98, 117, 102, 102, 101, 114, 84, 111, 86, 105, 100, 101, 111, 78, 86, 0, /*wglSendPbufferToVideoNV*/
    119, 103, 108, 83, 101, 116, 68, 105, 103, 105, 116, 97, 108, 86, 105, 100, 101, 111, 80, 97, 114, 97, 109, 101, 116, 101, 114, 115, 73, 51, 68, 0, /*wglSetDigitalVideoParametersI3D*/
    119, 103, 108, 83, 101, 116, 71, 97, 109, 109, 97, 84, 97, 98, 108, 101, 73, 51, 68, 0, /*wglSetGammaTableI3D*/
    119, 103, 108, 83, 101, 116, 71, 97, 109, 109, 97, 84, 97, 98, 108, 101, 80, 97, 114, 97, 109, 101, 116, 101, 114, 115, 73, 51, 68, 0, /*wglSetGammaTableParametersI3D*/
    119, 103, 108, 83, 101, 116, 76, 97, 121, 101, 114, 80, 97, 108, 101, 116, 116, 101, 69, 110, 116, 114, 105, 101, 115, 0, /*wglSetLayerPaletteEntries*/
    119, 103, 108, 83, 101, 116, 80, 98, 117, 102, 102, 101, 114, 65, 116, 116, 114, 105, 98, 65, 82, 66, 0, /*wglSetPbufferAttribARB*/
    119, 103, 108, 83, 101, 116, 80, 105, 120, 101, 108, 70, 111, 114, 109, 97, 116, 0, /*wglSetPixelFormat*/
    119, 103, 108, 83, 101, 116, 83, 116, 101, 114, 101, 111, 69, 109, 105, 116, 116, 101, 114, 83, 116, 97, 116, 101, 51, 68, 76, 0, /*wglSetStereoEmitterState3DL*/
    119, 103, 108, 83, 104, 97, 114, 101, 76, 105, 115, 116, 115, 0, /*wglShareLists*/
    119, 103, 108, 83, 119, 97, 112, 66, 117, 102, 102, 101, 114, 115, 0, /*wglSwapBuffers*/
    119, 103, 108, 83, 119, 97, 112, 66, 117, 102, 102, 101, 114, 115, 77, 115, 99, 79, 77, 76, 0, /*wglSwapBuffersMscOML*/
    119, 103, 108, 83, 119, 97, 112, 73, 110, 116, 101, 114, 118, 97, 108, 69, 88, 84, 0, /*wglSwapIntervalEXT*/
    119, 103, 108, 83, 119, 97, 112, 76, 97, 121, 101, 114, 66, 117, 102, 102, 101, 114, 115, 0, /*wglSwapLayerBuffers*/
    119, 103, 108, 83, 119, 97, 112, 76, 97, 121, 101, 114, 66, 117, 102, 102, 101, 114, 115, 77, 115, 99, 79, 77, 76, 0, /*wglSwapLayerBuffersMscOML*/
    119, 103, 108, 85, 115, 101, 70, 111, 110, 116, 66, 105, 116, 109, 97, 112, 115, 65, 0, /*wglUseFontBitmapsA*/
    119, 103, 108, 85, 115, 101, 70, 111, 110, 116, 66, 105, 116, 109, 97, 112, 115, 87, 0, /*wglUseFontBitmapsW*/
    119, 103, 108, 85, 115, 101, 70, 111, 110, 116, 79, 117, 116, 108, 105, 110, 101, 115, 0, /*wglUseFontOutlines*/
    119, 103, 108, 85, 115, 101, 70, 111, 110, 116, 79, 117, 116, 108, 105, 110, 101, 115, 65, 0, /*wglUseFontOutlinesA*/
    119, 103, 108, 85, 115, 101, 70, 111, 110, 116, 79, 117, 116, 108, 105, 110, 101, 115, 87, 0, /*wglUseFontOutlinesW*/
    119, 103, 108, 87, 97, 105, 116, 70, 111, 114, 77, 115, 99, 79, 77, 76, 0, /*wglWaitForMscOML*/
    119, 103, 108, 87, 97, 105, 116, 70, 111, 114, 83, 98, 99, 79, 77, 76, 0, /*wglWaitForSbcOML*/
};

static const struct dispatch_resolve_info wgl_resolve_info_table[] = {
    {DISPATCH_RESOLVE_EXTENSION, 0, 49 /* WGL_NV_vertex_array_range */, 0}, /* wglAllocateMemoryNV */
    {DISPATCH_RESOLVE_EXTENSION, 1, 35 /* WGL_I3D_image_buffer */, 20}, /* wglAssociateImageBufferEventsI3D */
    {DISPATCH_RESOLVE_EXTENSION, 2, 37 /* WGL_I3D_swap_frame_usage */, 53}, /* wglBeginFrameTrackingI3D */
    {DISPATCH_RESOLVE_EXTENSION, 3, 22 /* WGL_EXT_display_color_table */, 78}, /* wglBindDisplayColorTableEXT */
    {DISPATCH_RESOLVE_EXTENSION, 4, 48 /* WGL_NV_swap_group */, 106}, /* wglBindSwapBarrierNV */
    {DISPATCH_RESOLVE_EXTENSION, 5, 15 /* WGL_ARB_render_texture */, 127}, /* wglBindTexImageARB */
    {DISPATCH_RESOLVE_EXTENSION, 6, 50 /* WGL_NV_video_capture */, 146}, /* wglBindVideoCaptureDeviceNV */
    {DISPATCH_RESOLVE_EXTENSION, 7, 45 /* WGL_NV_present_video */, 174}, /* wglBindVideoDeviceNV */
    {DISPATCH_RESOLVE_EXTENSION, 8, 51 /* WGL_NV_video_output */, 195}, /* wglBindVideoImageNV */
    {DISPATCH_RESOLVE_EXTENSION, 9, 2 /* WGL_AMD_gpu_association */, 215}, /* wglBlitContextFramebufferAMD */
    {DISPATCH_RESOLVE_DIRECT, 10, WGL_1_0, 244}, /* wglChoosePixelFormat */
    {DISPATCH_RESOLVE_EXTENSION, 11, 13 /* WGL_ARB_pixel_format */, 265}, /* wglChoosePixelFormatARB */
    {DISPATCH_RESOLVE_EXTENSION, 12, 28 /* WGL_EXT_pixel_format */, 289}, /* wglChoosePixelFormatEXT */
    {DISPATCH_RESOLVE_DIRECT, 13, WGL_1_0, 313}, /* wglCopyContext */
    {DISPATCH_RESOLVE_EXTENSION, 14, 40 /* WGL_NV_copy_image */, 328}, /* wglCopyImageSubDataNV */
    {DISPATCH_RESOLVE_EXTENSION, 15, 43 /* WGL_NV_gpu_affinity */, 350}, /* wglCreateAffinityDCNV */
    {DISPATCH_RESOLVE_EXTENSION, 16, 2 /* WGL_AMD_gpu_association */, 372}, /* wglCreateAssociatedContextAMD */
    {DISPATCH_RESOLVE_EXTENSION, 17, 2 /* WGL_AMD_gpu_association */, 402}, /* wglCreateAssociatedContextAttribsAMD */
    {DISPATCH_RESOLVE_EXTENSION, 18, 3 /* WGL_ARB_buffer_region */, 439}, /* wglCreateBufferRegionARB */
    {DISPATCH_RESOLVE_DIRECT, 19, WGL_1_0, 464}, /* wglCreateContext */
    {DISPATCH_RESOLVE_EXTENSION, 20, 5 /* WGL_ARB_create_context */, 481}, /* wglCreateContextAttribsARB */
    {DISPATCH_RESOLVE_EXTENSION, 21, 22 /* WGL_EXT_display_color_table */, 508}, /* wglCreateDisplayColorTableEXT */
    {DISPATCH_RESOLVE_EXTENSION, 22, 35 /* WGL_I3D_image_buffer */, 538}, /* wglCreateImageBufferI3D */
    {DISPATCH_RESOLVE_DIRECT, 23, WGL_1_0, 562}, /* wglCreateLayerContext */
    {DISPATCH_RESOLVE_EXTENSION, 24, 12 /* WGL_ARB_pbuffer */, 584}, /* wglCreatePbufferARB */
    {DISPATCH_RESOLVE_EXTENSION, 25, 27 /* WGL_EXT_pbuffer */, 604}, /* wglCreatePbufferEXT */
    {DISPATCH_RESOLVE_EXTENSION, 26, 38 /* WGL_NV_DX_interop */, 624}, /* wglDXCloseDeviceNV */
    {DISPATCH_RESOLVE_EXTENSION, 27, 38 /* WGL_NV_DX_interop */, 643}, /* wglDXLockObjectsNV */
    {DISPATCH_RESOLVE_EXTENSION, 28, 38 /* WGL_NV_DX_interop */, 662}, /* wglDXObjectAccessNV */
    {DISPATCH_RESOLVE_EXTENSION, 29, 38 /* WGL_NV_DX_interop */, 682}, /* wglDXOpenDeviceNV */
    {DISPATCH_RESOLVE_EXTENSION, 30, 38 /* WGL_NV_DX_interop */, 700}, /* wglDXRegisterObjectNV */
    {DISPATCH_RESOLVE_EXTENSION, 31, 38 /* WGL_NV_DX_interop */, 722}, /* wglDXSetResourceShareHandleNV */
    {DISPATCH_RESOLVE_EXTENSION, 32, 38 /* WGL_NV_DX_interop */, 752}, /* wglDXUnlockObjectsNV */
    {DISPATCH_RESOLVE_EXTENSION, 33, 38 /* WGL_NV_DX_interop */, 773}, /* wglDXUnregisterObjectNV */
    {DISPATCH_RESOLVE_EXTENSION, 34, 41 /* WGL_NV_delay_before_swap */, 797}, /* wglDelayBeforeSwapNV */
    {DISPATCH_RESOLVE_EXTENSION, 35, 2 /* WGL_AMD_gpu_association */, 818}, /* wglDeleteAssociatedContextAMD */
    {DISPATCH_RESOLVE_EXTENSION, 36, 3 /* WGL_ARB_buffer_region */, 848}, /* wglDeleteBufferRegionARB */
    {DISPATCH_RESOLVE_DIRECT, 37, WGL_1_0, 873}, /* wglDeleteContext */
    {DISPATCH_RESOLVE_EXTENSION, 38, 43 /* WGL_NV_gpu_affinity */, 890}, /* wglDeleteDCNV */
    {DISPATCH_RESOLVE_DIRECT, 39, WGL_1_0, 904}, /* wglDescribeLayerPlane */
    {DISPATCH_RESOLVE_DIRECT, 40, WGL_1_0, 926}, /* wglDescribePixelFormat */
    {DISPATCH_RESOLVE_EXTENSION, 41, 22 /* WGL_EXT_display_color_table */, 949}, /* wglDestroyDisplayColorTableEXT */
    {DISPATCH_RESOLVE_EXTENSION, 42, 35 /* WGL_I3D_image_buffer */, 980}, /* wglDestroyImageBufferI3D */
    {DISPATCH_RESOLVE_EXTENSION, 43, 12 /* WGL_ARB_pbuffer */, 1005}, /* wglDestroyPbufferARB */
    {DISPATCH_RESOLVE_EXTENSION, 44, 27 /* WGL_EXT_pbuffer */, 1026}, /* wglDestroyPbufferEXT */
    {DISPATCH_RESOLVE_EXTENSION, 45, 36 /* WGL_I3D_swap_frame_lock */, 1047}, /* wglDisableFrameLockI3D */
    {DISPATCH_RESOLVE_EXTENSION, 46, 34 /* WGL_I3D_genlock */, 1070}, /* wglDisableGenlockI3D */
    {DISPATCH_RESOLVE_EXTENSION, 47, 36 /* WGL_I3D_swap_frame_lock */, 1091}, /* wglEnableFrameLockI3D */
    {DISPATCH_RESOLVE_EXTENSION, 48, 34 /* WGL_I3D_genlock */, 1113}, /* wglEnableGenlockI3D */
    {DISPATCH_RESOLVE_EXTENSION, 49, 37 /* WGL_I3D_swap_frame_usage */, 1133}, /* wglEndFrameTrackingI3D */
    {DISPATCH_RESOLVE_EXTENSION, 50, 43 /* WGL_NV_gpu_affinity */, 1156}, /* wglEnumGpuDevicesNV */
    {DISPATCH_RESOLVE_EXTENSION, 51, 43 /* WGL_NV_gpu_affinity */, 1176}, /* wglEnumGpusFromAffinityDCNV */
    {DISPATCH_RESOLVE_EXTENSION, 52, 43 /* WGL_NV_gpu_affinity */, 1204}, /* wglEnumGpusNV */
    {DISPATCH_RESOLVE_EXTENSION, 53, 50 /* WGL_NV_video_capture */, 1218}, /* wglEnumerateVideoCaptureDevicesNV */
    {DISPATCH_RESOLVE_EXTENSION, 54, 45 /* WGL_NV_present_video */, 1252}, /* wglEnumerateVideoDevicesNV */
    {DISPATCH_RESOLVE_EXTENSION, 55, 49 /* WGL_NV_vertex_array_range */, 1279}, /* wglFreeMemoryNV */
    {DISPATCH_RESOLVE_EXTENSION, 56, 34 /* WGL_I3D_genlock */, 1295}, /* wglGenlockSampleRateI3D */
    {DISPATCH_RESOLVE_EXTENSION, 57, 34 /* WGL_I3D_genlock */, 1319}, /* wglGenlockSourceDelayI3D */
    {DISPATCH_RESOLVE_EXTENSION, 58, 34 /* WGL_I3D_genlock */, 1344}, /* wglGenlockSourceEdgeI3D */
    {DISPATCH_RESOLVE_EXTENSION, 59, 34 /* WGL_I3D_genlock */, 1368}, /* wglGenlockSourceI3D */
    {DISPATCH_RESOLVE_EXTENSION, 60, 2 /* WGL_AMD_gpu_association */, 1388}, /* wglGetContextGPUIDAMD */
    {DISPATCH_RESOLVE_EXTENSION, 61, 2 /* WGL_AMD_gpu_association */, 1410}, /* wglGetCurrentAssociatedContextAMD */
    {DISPATCH_RESOLVE_DIRECT, 62, WGL_1_0, 1444}, /* wglGetCurrentContext */
    {DISPATCH_RESOLVE_DIRECT, 63, WGL_1_0, 1465}, /* wglGetCurrentDC */
    {DISPATCH_RESOLVE_EXTENSION, 64, 10 /* WGL_ARB_make_current_read */, 1481}, /* wglGetCurrentReadDCARB */
    {DISPATCH_RESOLVE_EXTENSION, 65, 25 /* WGL_EXT_make_current_read */, 1504}, /* wglGetCurrentReadDCEXT */
    {DISPATCH_RESOLVE_DIRECT, 66, WGL_1_0, 1527}, /* wglGetDefaultProcAddress */
    {DISPATCH_RESOLVE_EXTENSION, 67, 32 /* WGL_I3D_digital_video_control */, 1552}, /* wglGetDigitalVideoParametersI3D */
    {DISPATCH_RESOLVE_DIRECT, 68, WGL_1_0, 1584}, /* wglGetEnhMetaFilePixelFormat */
    {DISPATCH_RESOLVE_EXTENSION, 69, 8 /* WGL_ARB_extensions_string */, 1613}, /* wglGetExtensionsStringARB */
    {DISPATCH_RESOLVE_EXTENSION, 70, 23 /* WGL_EXT_extensions_string */, 1639}, /* wglGetExtensionsStringEXT */
    {DISPATCH_RESOLVE_EXTENSION, 71, 37 /* WGL_I3D_swap_frame_usage */, 1665}, /* wglGetFrameUsageI3D */
    {DISPATCH_RESOLVE_EXTENSION, 72, 2 /* WGL_AMD_gpu_association */, 1685}, /* wglGetGPUIDsAMD */
    {DISPATCH_RESOLVE_EXTENSION, 73, 2 /* WGL_AMD_gpu_association */, 1701}, /* wglGetGPUInfoAMD */
    {DISPATCH_RESOLVE_EXTENSION, 74, 33 /* WGL_I3D_gamma */, 1718}, /* wglGetGammaTableI3D */
    {DISPATCH_RESOLVE_EXTENSION, 75, 33 /* WGL_I3D_gamma */, 1738}, /* wglGetGammaTableParametersI3D */
    {DISPATCH_RESOLVE_EXTENSION, 76, 34 /* WGL_I3D_genlock */, 1768}, /* wglGetGenlockSampleRateI3D */
    {DISPATCH_RESOLVE_EXTENSION, 77, 34 /* WGL_I3D_genlock */, 1795}, /* wglGetGenlockSourceDelayI3D */
    {DISPATCH_RESOLVE_EXTENSION, 78, 34 /* WGL_I3D_genlock */, 1823}, /* wglGetGenlockSourceEdgeI3D */
    {DISPATCH_RESOLVE_EXTENSION, 79, 34 /* WGL_I3D_genlock */, 1850}, /* wglGetGenlockSourceI3D */
    {DISPATCH_RESOLVE_DIRECT, 80, WGL_1_0, 1873}, /* wglGetLayerPaletteEntries */
    {DISPATCH_RESOLVE_EXTENSION, 81, 52 /* WGL_OML_sync_control */, 1899}, /* wglGetMscRateOML */
    {DISPATCH_RESOLVE_EXTENSION, 82, 12 /* WGL_ARB_pbuffer */, 1916}, /* wglGetPbufferDCARB */
    {DISPATCH_RESOLVE_EXTENSION, 83, 27 /* WGL_EXT_pbuffer */, 1935}, /* wglGetPbufferDCEXT */
    {DISPATCH_RESOLVE_DIRECT, 84, WGL_1_0, 1954}, /* wglGetPixelFormat */
    {DISPATCH_RESOLVE_EXTENSION, 85, 13 /* WGL_ARB_pixel_format */, 1972}, /* wglGetPixelFormatAttribfvARB */
    {DISPATCH_RESOLVE_EXTENSION, 86, 28 /* WGL_EXT_pixel_format */, 2001}, /* wglGetPixelFormatAttribfvEXT */
    {DISPATCH_RESOLVE_EXTENSION, 87, 13 /* WGL_ARB_pixel_format */, 2030}, /* wglGetPixelFormatAttribivARB */
    {DISPATCH_RESOLVE_EXTENSION, 88, 28 /* WGL_EXT_pixel_format */, 2059}, /* wglGetPixelFormatAttribivEXT */
    {DISPATCH_RESOLVE_DIRECT, 89, WGL_1_0, 2088}, /* wglGetProcAddress */
    {DISPATCH_RESOLVE_EXTENSION, 90, 30 /* WGL_EXT_swap_control */, 2106}, /* wglGetSwapIntervalEXT */
    {DISPATCH_RESOLVE_EXTENSION, 91, 52 /* WGL_OML_sync_control */, 2128}, /* wglGetSyncValuesOML */
    {DISPATCH_RESOLVE_EXTENSION, 92, 51 /* WGL_NV_video_output */, 2148}, /* wglGetVideoDeviceNV */
    {DISPATCH_RESOLVE_EXTENSION, 93, 51 /* WGL_NV_video_output */, 2168}, /* wglGetVideoInfoNV */
    {DISPATCH_RESOLVE_EXTENSION, 94, 36 /* WGL_I3D_swap_frame_lock */, 2186}, /* wglIsEnabledFrameLockI3D */
    {DISPATCH_RESOLVE_EXTENSION, 95, 34 /* WGL_I3D_genlock */, 2211}, /* wglIsEnabledGenlockI3D */
    {DISPATCH_RESOLVE_EXTENSION, 96, 48 /* WGL_NV_swap_group */, 2234}, /* wglJoinSwapGroupNV */
    {DISPATCH_RESOLVE_EXTENSION, 97, 22 /* WGL_EXT_display_color_table */, 2253}, /* wglLoadDisplayColorTableEXT */
    {DISPATCH_RESOLVE_EXTENSION, 98, 50 /* WGL_NV_video_capture */, 2281}, /* wglLockVideoCaptureDeviceNV */
    {DISPATCH_RESOLVE_EXTENSION, 99, 2 /* WGL_AMD_gpu_association */, 2309}, /* wglMakeAssociatedContextCurrentAMD */
    {DISPATCH_RESOLVE_EXTENSION, 100, 10 /* WGL_ARB_make_current_read */, 2344}, /* wglMakeContextCurrentARB */
    {DISPATCH_RESOLVE_EXTENSION, 101, 25 /* WGL_EXT_make_current_read */, 2369}, /* wglMakeContextCurrentEXT */
    {DISPATCH_RESOLVE_DIRECT, 102, WGL_1_0, 2394}, /* wglMakeCurrent */
    {DISPATCH_RESOLVE_EXTENSION, 103, 45 /* WGL_NV_present_video */, 2409}, /* wglQueryCurrentContextNV */
    {DISPATCH_RESOLVE_EXTENSION, 104, 48 /* WGL_NV_swap_group */, 2434}, /* wglQueryFrameCountNV */
    {DISPATCH_RESOLVE_EXTENSION, 105, 36 /* WGL_I3D_swap_frame_lock */, 2455}, /* wglQueryFrameLockMasterI3D */
    {DISPATCH_RESOLVE_EXTENSION, 106, 37 /* WGL_I3D_swap_frame_usage */, 2482}, /* wglQueryFrameTrackingI3D */
    {DISPATCH_RESOLVE_EXTENSION, 107, 34 /* WGL_I3D_genlock */, 2507}, /* wglQueryGenlockMaxSourceDelayI3D */
    {DISPATCH_RESOLVE_EXTENSION, 108, 48 /* WGL_NV_swap_group */, 2540}, /* wglQueryMaxSwapGroupsNV */
    {DISPATCH_RESOLVE_EXTENSION, 109, 12 /* WGL_ARB_pbuffer */, 2564}, /* wglQueryPbufferARB */
    {DISPATCH_RESOLVE_EXTENSION, 110, 27 /* WGL_EXT_pbuffer */, 2583}, /* wglQueryPbufferEXT */
    {DISPATCH_RESOLVE_EXTENSION, 111, 48 /* WGL_NV_swap_group */, 2602}, /* wglQuerySwapGroupNV */
    {DISPATCH_RESOLVE_EXTENSION, 112, 50 /* WGL_NV_video_capture */, 2622}, /* wglQueryVideoCaptureDeviceNV */
    {DISPATCH_RESOLVE_DIRECT, 113, WGL_1_0, 2651}, /* wglRealizeLayerPalette */
    {DISPATCH_RESOLVE_EXTENSION, 114, 35 /* WGL_I3D_image_buffer */, 2674}, /* wglReleaseImageBufferEventsI3D */
    {DISPATCH_RESOLVE_EXTENSION, 115, 12 /* WGL_ARB_pbuffer */, 2705}, /* wglReleasePbufferDCARB */
    {DISPATCH_RESOLVE_EXTENSION, 116, 27 /* WGL_EXT_pbuffer */, 2728}, /* wglReleasePbufferDCEXT */
    {DISPATCH_RESOLVE_EXTENSION, 117, 15 /* WGL_ARB_render_texture */, 2751}, /* wglReleaseTexImageARB */
    {DISPATCH_RESOLVE_EXTENSION, 118, 50 /* WGL_NV_video_capture */, 2773}, /* wglReleaseVideoCaptureDeviceNV */
    {DISPATCH_RESOLVE_EXTENSION, 119, 51 /* WGL_NV_video_output */, 2804}, /* wglReleaseVideoDeviceNV */
    {DISPATCH_RESOLVE_EXTENSION, 120, 51 /* WGL_NV_video_output */, 2828}, /* wglReleaseVideoImageNV */
    {DISPATCH_RESOLVE_EXTENSION, 121, 48 /* WGL_NV_swap_group */, 2851}, /* wglResetFrameCountNV */
    {DISPATCH_RESOLVE_EXTENSION, 122, 3 /* WGL_ARB_buffer_region */, 2872}, /* wglRestoreBufferRegionARB */
    {DISPATCH_RESOLVE_EXTENSION, 123, 3 /* WGL_ARB_buffer_region */, 2898}, /* wglSaveBufferRegionARB */
    {DISPATCH_RESOLVE_EXTENSION, 124, 51 /* WGL_NV_video_output */, 2921}, /* wglSendPbufferToVideoNV */
    {DISPATCH_RESOLVE_EXTENSION, 125, 32 /* WGL_I3D_digital_video_control */, 2945}, /* wglSetDigitalVideoParametersI3D */
    {DISPATCH_RESOLVE_EXTENSION, 126, 33 /* WGL_I3D_gamma */, 2977}, /* wglSetGammaTableI3D */
    {DISPATCH_RESOLVE_EXTENSION, 127, 33 /* WGL_I3D_gamma */, 2997}, /* wglSetGammaTableParametersI3D */
    {DISPATCH_RESOLVE_DIRECT, 128, WGL_1_0, 3027}, /* wglSetLayerPaletteEntries */
    {DISPATCH_RESOLVE_EXTENSION, 129, 15 /* WGL_ARB_render_texture */, 3053}, /* wglSetPbufferAttribARB */
    {DISPATCH_RESOLVE_DIRECT, 130, WGL_1_0, 3076}, /* wglSetPixelFormat */
    {DISPATCH_RESOLVE_EXTENSION, 131, 1 /* WGL_3DL_stereo_control */, 3094}, /* wglSetStereoEmitterState3DL */
    {DISPATCH_RESOLVE_DIRECT, 132, WGL_1_0, 3122}, /* wglShareLists */
    {DISPATCH_RESOLVE_DIRECT, 133, WGL_1_0, 3136}, /* wglSwapBuffers */
    {DISPATCH_RESOLVE_EXTENSION, 134, 52 /* WGL_OML_sync_control */, 3151}, /* wglSwapBuffersMscOML */
    {DISPATCH_RESOLVE_EXTENSION, 135, 30 /* WGL_EXT_swap_control */, 3172}, /* wglSwapIntervalEXT */
    {DISPATCH_RESOLVE_DIRECT, 136, WGL_1_0, 3191}, /* wglSwapLayerBuffers */
    {DISPATCH_RESOLVE_EXTENSION, 137, 52 /* WGL_OML_sync_control */, 3211}, /* wglSwapLayerBuffersMscOML */
    {DISPATCH_RESOLVE_DIRECT, 138, WGL_1_0, 3237}, /* wglUseFontBitmapsA */
    {DISPATCH_RESOLVE_DIRECT, 139, WGL_1_0, 3256}, /* wglUseFontBitmapsW */
    {DISPATCH_RESOLVE_DIRECT, 140, WGL_1_0, 3275}, /* wglUseFontOutlines */
    {DISPATCH_RESOLVE_DIRECT, 141, WGL_1_0, 3294}, /* wglUseFontOutlinesA */
    {DISPATCH_RESOLVE_DIRECT, 142, WGL_1_0, 3314}, /* wglUseFontOutlinesW */
    {DISPATCH_RESOLVE_EXTENSION, 143, 52 /* WGL_OML_sync_control */, 3334}, /* wglWaitForMscOML */
    {DISPATCH_RESOLVE_EXTENSION, 144, 52 /* WGL_OML_sync_control */, 3351}, /* wglWaitForSbcOML */
    {DISPATCH_RESOLVE_TERMINATOR, 145, 0, 0}
};

static khronos_uint16_t wgl_resolve_offsets[145] = {0};
static khronos_uint32_t wgl_method_name_offsets[145] = {0};

#define HAS_DISPATCH_RESOLVE_DIRECT 1
#define HAS_DISPATCH_RESOLVE_VERSION 0
#define current_resolve wgl_resolve
#define current_glproxy_resolve_init wgl_glproxy_resolve_init
#define current_glproxy_resolve_direct wgl_glproxy_resolve_direct
#define current_glproxy_resolve_version wgl_glproxy_resolve_version
#define current_glproxy_resolve_extension wgl_glproxy_resolve_extension
#define current_dispatch_table wgl_dispatch_table
#define current_metadata wgl_metadata
#define current_glproxy_resolve_local wgl_glproxy_resolve_local
#define current_glproxy_dispatch_metadata_init wgl_glproxy_dispatch_metadata_init
#define current_extension_offsets wgl_extension_offsets
#define current_extensions_count wgl_extensions_count
#define current_extension_enum_strings wgl_extension_enum_strings
#define current_entrypoint_strings wgl_entrypoint_strings
#define current_resolve_info_table wgl_resolve_info_table
#define current_resolve_offsets wgl_resolve_offsets
#define current_method_name_offsets wgl_method_name_offsets
#include "dispatch_generated.inc"
#undef current_resolve
#undef current_glproxy_resolve_init
#undef current_glproxy_resolve_direct
#undef current_glproxy_resolve_version
#undef current_glproxy_resolve_extension
#undef current_dispatch_table
#undef current_metadata
#undef current_glproxy_resolve_local
#undef current_glproxy_dispatch_metadata_init
#undef current_extension_offsets
#undef current_extensions_count
#undef current_extension_enum_strings
#undef current_entrypoint_strings
#undef current_resolve_info_table
#undef current_resolve_offsets
#undef current_method_name_offsets
#undef HAS_DISPATCH_RESOLVE_DIRECT
#undef HAS_DISPATCH_RESOLVE_VERSION

GEN_THUNK_RET(wgl, void *, wglAllocateMemoryNV, (GLsizei size, GLfloat readfreq, GLfloat writefreq, GLfloat priority), (size, readfreq, writefreq, priority), 0, PFNWGLALLOCATEMEMORYNVPROC)
GEN_THUNK_RET(wgl, BOOL, wglAssociateImageBufferEventsI3D, (HDC hDC, const HANDLE * pEvent, const LPVOID * pAddress, const DWORD * pSize, UINT count), (hDC, pEvent, pAddress, pSize, count), 1, PFNWGLASSOCIATEIMAGEBUFFEREVENTSI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglBeginFrameTrackingI3D, (void), (), 2, PFNWGLBEGINFRAMETRACKINGI3DPROC)
GEN_THUNK_RET(wgl, GLboolean, wglBindDisplayColorTableEXT, (GLushort id), (id), 3, PFNWGLBINDDISPLAYCOLORTABLEEXTPROC)
GEN_THUNK_RET(wgl, BOOL, wglBindSwapBarrierNV, (GLuint group, GLuint barrier), (group, barrier), 4, PFNWGLBINDSWAPBARRIERNVPROC)
GEN_THUNK_RET(wgl, BOOL, wglBindTexImageARB, (HPBUFFERARB hPbuffer, int iBuffer), (hPbuffer, iBuffer), 5, PFNWGLBINDTEXIMAGEARBPROC)
GEN_THUNK_RET(wgl, BOOL, wglBindVideoCaptureDeviceNV, (UINT uVideoSlot, HVIDEOINPUTDEVICENV hDevice), (uVideoSlot, hDevice), 6, PFNWGLBINDVIDEOCAPTUREDEVICENVPROC)
GEN_THUNK_RET(wgl, BOOL, wglBindVideoDeviceNV, (HDC hDC, unsigned int uVideoSlot, HVIDEOOUTPUTDEVICENV hVideoDevice, const int * piAttribList), (hDC, uVideoSlot, hVideoDevice, piAttribList), 7, PFNWGLBINDVIDEODEVICENVPROC)
GEN_THUNK_RET(wgl, BOOL, wglBindVideoImageNV, (HPVIDEODEV hVideoDevice, HPBUFFERARB hPbuffer, int iVideoBuffer), (hVideoDevice, hPbuffer, iVideoBuffer), 8, PFNWGLBINDVIDEOIMAGENVPROC)
GEN_THUNK(wgl, wglBlitContextFramebufferAMD, (HGLRC dstCtx, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter), (dstCtx, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter), 9, PFNWGLBLITCONTEXTFRAMEBUFFERAMDPROC)
GEN_THUNK_RET(wgl, int, wglChoosePixelFormat, (HDC hDc, const PIXELFORMATDESCRIPTOR * pPfd), (hDc, pPfd), 10, PFNWGLCHOOSEPIXELFORMATPROC)
GEN_THUNK_RET(wgl, BOOL, wglChoosePixelFormatARB, (HDC hdc, const int * piAttribIList, const FLOAT * pfAttribFList, UINT nMaxFormats, int * piFormats, UINT * nNumFormats), (hdc, piAttribIList, pfAttribFList, nMaxFormats, piFormats, nNumFormats), 11, PFNWGLCHOOSEPIXELFORMATARBPROC)
GEN_THUNK_RET(wgl, BOOL, wglChoosePixelFormatEXT, (HDC hdc, const int * piAttribIList, const FLOAT * pfAttribFList, UINT nMaxFormats, int * piFormats, UINT * nNumFormats), (hdc, piAttribIList, pfAttribFList, nMaxFormats, piFormats, nNumFormats), 12, PFNWGLCHOOSEPIXELFORMATEXTPROC)
GEN_THUNK_RET(wgl, BOOL, wglCopyContext, (HGLRC hglrcSrc, HGLRC hglrcDst, UINT mask), (hglrcSrc, hglrcDst, mask), 13, PFNWGLCOPYCONTEXTPROC)
GEN_THUNK_RET(wgl, BOOL, wglCopyImageSubDataNV, (HGLRC hSrcRC, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, HGLRC hDstRC, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth), (hSrcRC, srcName, srcTarget, srcLevel, srcX, srcY, srcZ, hDstRC, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, width, height, depth), 14, PFNWGLCOPYIMAGESUBDATANVPROC)
GEN_THUNK_RET(wgl, HDC, wglCreateAffinityDCNV, (const HGPUNV * phGpuList), (phGpuList), 15, PFNWGLCREATEAFFINITYDCNVPROC)
GEN_THUNK_RET(wgl, HGLRC, wglCreateAssociatedContextAMD, (UINT id), (id), 16, PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC)
GEN_THUNK_RET(wgl, HGLRC, wglCreateAssociatedContextAttribsAMD, (UINT id, HGLRC hShareContext, const int * attribList), (id, hShareContext, attribList), 17, PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC)
GEN_THUNK_RET(wgl, HANDLE, wglCreateBufferRegionARB, (HDC hDC, int iLayerPlane, UINT uType), (hDC, iLayerPlane, uType), 18, PFNWGLCREATEBUFFERREGIONARBPROC)
GEN_THUNK_RET(wgl, HGLRC, wglCreateContext, (HDC hDc), (hDc), 19, PFNWGLCREATECONTEXTPROC)
GEN_THUNK_RET(wgl, HGLRC, wglCreateContextAttribsARB, (HDC hDC, HGLRC hShareContext, const int * attribList), (hDC, hShareContext, attribList), 20, PFNWGLCREATECONTEXTATTRIBSARBPROC)
GEN_THUNK_RET(wgl, GLboolean, wglCreateDisplayColorTableEXT, (GLushort id), (id), 21, PFNWGLCREATEDISPLAYCOLORTABLEEXTPROC)
GEN_THUNK_RET(wgl, LPVOID, wglCreateImageBufferI3D, (HDC hDC, DWORD dwSize, UINT uFlags), (hDC, dwSize, uFlags), 22, PFNWGLCREATEIMAGEBUFFERI3DPROC)
GEN_THUNK_RET(wgl, HGLRC, wglCreateLayerContext, (HDC hDc, int level), (hDc, level), 23, PFNWGLCREATELAYERCONTEXTPROC)
GEN_THUNK_RET(wgl, HPBUFFERARB, wglCreatePbufferARB, (HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int * piAttribList), (hDC, iPixelFormat, iWidth, iHeight, piAttribList), 24, PFNWGLCREATEPBUFFERARBPROC)
GEN_THUNK_RET(wgl, HPBUFFEREXT, wglCreatePbufferEXT, (HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int * piAttribList), (hDC, iPixelFormat, iWidth, iHeight, piAttribList), 25, PFNWGLCREATEPBUFFEREXTPROC)
GEN_THUNK_RET(wgl, BOOL, wglDXCloseDeviceNV, (HANDLE hDevice), (hDevice), 26, PFNWGLDXCLOSEDEVICENVPROC)
GEN_THUNK_RET(wgl, BOOL, wglDXLockObjectsNV, (HANDLE hDevice, GLint count, HANDLE * hObjects), (hDevice, count, hObjects), 27, PFNWGLDXLOCKOBJECTSNVPROC)
GEN_THUNK_RET(wgl, BOOL, wglDXObjectAccessNV, (HANDLE hObject, GLenum access), (hObject, access), 28, PFNWGLDXOBJECTACCESSNVPROC)
GEN_THUNK_RET(wgl, HANDLE, wglDXOpenDeviceNV, (void * dxDevice), (dxDevice), 29, PFNWGLDXOPENDEVICENVPROC)
GEN_THUNK_RET(wgl, HANDLE, wglDXRegisterObjectNV, (HANDLE hDevice, void * dxObject, GLuint name, GLenum type, GLenum access), (hDevice, dxObject, name, type, access), 30, PFNWGLDXREGISTEROBJECTNVPROC)
GEN_THUNK_RET(wgl, BOOL, wglDXSetResourceShareHandleNV, (void * dxObject, HANDLE shareHandle), (dxObject, shareHandle), 31, PFNWGLDXSETRESOURCESHAREHANDLENVPROC)
GEN_THUNK_RET(wgl, BOOL, wglDXUnlockObjectsNV, (HANDLE hDevice, GLint count, HANDLE * hObjects), (hDevice, count, hObjects), 32, PFNWGLDXUNLOCKOBJECTSNVPROC)
GEN_THUNK_RET(wgl, BOOL, wglDXUnregisterObjectNV, (HANDLE hDevice, HANDLE hObject), (hDevice, hObject), 33, PFNWGLDXUNREGISTEROBJECTNVPROC)
GEN_THUNK_RET(wgl, BOOL, wglDelayBeforeSwapNV, (HDC hDC, GLfloat seconds), (hDC, seconds), 34, PFNWGLDELAYBEFORESWAPNVPROC)
GEN_THUNK_RET(wgl, BOOL, wglDeleteAssociatedContextAMD, (HGLRC hglrc), (hglrc), 35, PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC)
GEN_THUNK(wgl, wglDeleteBufferRegionARB, (HANDLE hRegion), (hRegion), 36, PFNWGLDELETEBUFFERREGIONARBPROC)
GEN_THUNK_RET(wgl, BOOL, wglDeleteContext, (HGLRC oldContext), (oldContext), 37, PFNWGLDELETECONTEXTPROC)
GEN_THUNK_RET(wgl, BOOL, wglDeleteDCNV, (HDC hdc), (hdc), 38, PFNWGLDELETEDCNVPROC)
GEN_THUNK_RET(wgl, BOOL, wglDescribeLayerPlane, (HDC hDc, int pixelFormat, int layerPlane, UINT nBytes, const LAYERPLANEDESCRIPTOR * plpd), (hDc, pixelFormat, layerPlane, nBytes, plpd), 39, PFNWGLDESCRIBELAYERPLANEPROC)
GEN_THUNK_RET(wgl, int, wglDescribePixelFormat, (HDC hdc, int ipfd, UINT cjpfd, const PIXELFORMATDESCRIPTOR * ppfd), (hdc, ipfd, cjpfd, ppfd), 40, PFNWGLDESCRIBEPIXELFORMATPROC)
GEN_THUNK(wgl, wglDestroyDisplayColorTableEXT, (GLushort id), (id), 41, PFNWGLDESTROYDISPLAYCOLORTABLEEXTPROC)
GEN_THUNK_RET(wgl, BOOL, wglDestroyImageBufferI3D, (HDC hDC, LPVOID pAddress), (hDC, pAddress), 42, PFNWGLDESTROYIMAGEBUFFERI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglDestroyPbufferARB, (HPBUFFERARB hPbuffer), (hPbuffer), 43, PFNWGLDESTROYPBUFFERARBPROC)
GEN_THUNK_RET(wgl, BOOL, wglDestroyPbufferEXT, (HPBUFFEREXT hPbuffer), (hPbuffer), 44, PFNWGLDESTROYPBUFFEREXTPROC)
GEN_THUNK_RET(wgl, BOOL, wglDisableFrameLockI3D, (void), (), 45, PFNWGLDISABLEFRAMELOCKI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglDisableGenlockI3D, (HDC hDC), (hDC), 46, PFNWGLDISABLEGENLOCKI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglEnableFrameLockI3D, (void), (), 47, PFNWGLENABLEFRAMELOCKI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglEnableGenlockI3D, (HDC hDC), (hDC), 48, PFNWGLENABLEGENLOCKI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglEndFrameTrackingI3D, (void), (), 49, PFNWGLENDFRAMETRACKINGI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglEnumGpuDevicesNV, (HGPUNV hGpu, UINT iDeviceIndex, PGPU_DEVICE lpGpuDevice), (hGpu, iDeviceIndex, lpGpuDevice), 50, PFNWGLENUMGPUDEVICESNVPROC)
GEN_THUNK_RET(wgl, BOOL, wglEnumGpusFromAffinityDCNV, (HDC hAffinityDC, UINT iGpuIndex, HGPUNV * hGpu), (hAffinityDC, iGpuIndex, hGpu), 51, PFNWGLENUMGPUSFROMAFFINITYDCNVPROC)
GEN_THUNK_RET(wgl, BOOL, wglEnumGpusNV, (UINT iGpuIndex, HGPUNV * phGpu), (iGpuIndex, phGpu), 52, PFNWGLENUMGPUSNVPROC)
GEN_THUNK_RET(wgl, UINT, wglEnumerateVideoCaptureDevicesNV, (HDC hDc, HVIDEOINPUTDEVICENV * phDeviceList), (hDc, phDeviceList), 53, PFNWGLENUMERATEVIDEOCAPTUREDEVICESNVPROC)
GEN_THUNK_RET(wgl, int, wglEnumerateVideoDevicesNV, (HDC hDC, HVIDEOOUTPUTDEVICENV * phDeviceList), (hDC, phDeviceList), 54, PFNWGLENUMERATEVIDEODEVICESNVPROC)
GEN_THUNK(wgl, wglFreeMemoryNV, (void * pointer), (pointer), 55, PFNWGLFREEMEMORYNVPROC)
GEN_THUNK_RET(wgl, BOOL, wglGenlockSampleRateI3D, (HDC hDC, UINT uRate), (hDC, uRate), 56, PFNWGLGENLOCKSAMPLERATEI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglGenlockSourceDelayI3D, (HDC hDC, UINT uDelay), (hDC, uDelay), 57, PFNWGLGENLOCKSOURCEDELAYI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglGenlockSourceEdgeI3D, (HDC hDC, UINT uEdge), (hDC, uEdge), 58, PFNWGLGENLOCKSOURCEEDGEI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglGenlockSourceI3D, (HDC hDC, UINT uSource), (hDC, uSource), 59, PFNWGLGENLOCKSOURCEI3DPROC)
GEN_THUNK_RET(wgl, UINT, wglGetContextGPUIDAMD, (HGLRC hglrc), (hglrc), 60, PFNWGLGETCONTEXTGPUIDAMDPROC)
GEN_THUNK_RET(wgl, HGLRC, wglGetCurrentAssociatedContextAMD, (void), (), 61, PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC)
GEN_THUNK_RET(wgl, HGLRC, wglGetCurrentContext, (void), (), 62, PFNWGLGETCURRENTCONTEXTPROC)
GEN_THUNK_RET(wgl, HDC, wglGetCurrentDC, (void), (), 63, PFNWGLGETCURRENTDCPROC)
GEN_THUNK_RET(wgl, HDC, wglGetCurrentReadDCARB, (void), (), 64, PFNWGLGETCURRENTREADDCARBPROC)
GEN_THUNK_RET(wgl, HDC, wglGetCurrentReadDCEXT, (void), (), 65, PFNWGLGETCURRENTREADDCEXTPROC)
GEN_THUNK_RET(wgl, PROC, wglGetDefaultProcAddress, (LPCSTR lpszProc), (lpszProc), 66, PFNWGLGETDEFAULTPROCADDRESSPROC)
GEN_THUNK_RET(wgl, BOOL, wglGetDigitalVideoParametersI3D, (HDC hDC, int iAttribute, int * piValue), (hDC, iAttribute, piValue), 67, PFNWGLGETDIGITALVIDEOPARAMETERSI3DPROC)
GEN_THUNK_RET(wgl, UINT, wglGetEnhMetaFilePixelFormat, (HENHMETAFILE hemf, const PIXELFORMATDESCRIPTOR * ppfd), (hemf, ppfd), 68, PFNWGLGETENHMETAFILEPIXELFORMATPROC)
GEN_THUNK_RET(wgl, const char *, wglGetExtensionsStringARB, (HDC hdc), (hdc), 69, PFNWGLGETEXTENSIONSSTRINGARBPROC)
GEN_THUNK_RET(wgl, const char *, wglGetExtensionsStringEXT, (void), (), 70, PFNWGLGETEXTENSIONSSTRINGEXTPROC)
GEN_THUNK_RET(wgl, BOOL, wglGetFrameUsageI3D, (float * pUsage), (pUsage), 71, PFNWGLGETFRAMEUSAGEI3DPROC)
GEN_THUNK_RET(wgl, UINT, wglGetGPUIDsAMD, (UINT maxCount, UINT * ids), (maxCount, ids), 72, PFNWGLGETGPUIDSAMDPROC)
GEN_THUNK_RET(wgl, INT, wglGetGPUInfoAMD, (UINT id, int property, GLenum dataType, UINT size, void * data), (id, property, dataType, size, data), 73, PFNWGLGETGPUINFOAMDPROC)
GEN_THUNK_RET(wgl, BOOL, wglGetGammaTableI3D, (HDC hDC, int iEntries, USHORT * puRed, USHORT * puGreen, USHORT * puBlue), (hDC, iEntries, puRed, puGreen, puBlue), 74, PFNWGLGETGAMMATABLEI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglGetGammaTableParametersI3D, (HDC hDC, int iAttribute, int * piValue), (hDC, iAttribute, piValue), 75, PFNWGLGETGAMMATABLEPARAMETERSI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglGetGenlockSampleRateI3D, (HDC hDC, UINT * uRate), (hDC, uRate), 76, PFNWGLGETGENLOCKSAMPLERATEI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglGetGenlockSourceDelayI3D, (HDC hDC, UINT * uDelay), (hDC, uDelay), 77, PFNWGLGETGENLOCKSOURCEDELAYI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglGetGenlockSourceEdgeI3D, (HDC hDC, UINT * uEdge), (hDC, uEdge), 78, PFNWGLGETGENLOCKSOURCEEDGEI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglGetGenlockSourceI3D, (HDC hDC, UINT * uSource), (hDC, uSource), 79, PFNWGLGETGENLOCKSOURCEI3DPROC)
GEN_THUNK_RET(wgl, int, wglGetLayerPaletteEntries, (HDC hdc, int iLayerPlane, int iStart, int cEntries, const COLORREF * pcr), (hdc, iLayerPlane, iStart, cEntries, pcr), 80, PFNWGLGETLAYERPALETTEENTRIESPROC)
GEN_THUNK_RET(wgl, BOOL, wglGetMscRateOML, (HDC hdc, INT32 * numerator, INT32 * denominator), (hdc, numerator, denominator), 81, PFNWGLGETMSCRATEOMLPROC)
GEN_THUNK_RET(wgl, HDC, wglGetPbufferDCARB, (HPBUFFERARB hPbuffer), (hPbuffer), 82, PFNWGLGETPBUFFERDCARBPROC)
GEN_THUNK_RET(wgl, HDC, wglGetPbufferDCEXT, (HPBUFFEREXT hPbuffer), (hPbuffer), 83, PFNWGLGETPBUFFERDCEXTPROC)
GEN_THUNK_RET(wgl, int, wglGetPixelFormat, (HDC hdc), (hdc), 84, PFNWGLGETPIXELFORMATPROC)
GEN_THUNK_RET(wgl, BOOL, wglGetPixelFormatAttribfvARB, (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int * piAttributes, FLOAT * pfValues), (hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, pfValues), 85, PFNWGLGETPIXELFORMATATTRIBFVARBPROC)
GEN_THUNK_RET(wgl, BOOL, wglGetPixelFormatAttribfvEXT, (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int * piAttributes, FLOAT * pfValues), (hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, pfValues), 86, PFNWGLGETPIXELFORMATATTRIBFVEXTPROC)
GEN_THUNK_RET(wgl, BOOL, wglGetPixelFormatAttribivARB, (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int * piAttributes, int * piValues), (hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, piValues), 87, PFNWGLGETPIXELFORMATATTRIBIVARBPROC)
GEN_THUNK_RET(wgl, BOOL, wglGetPixelFormatAttribivEXT, (HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int * piAttributes, int * piValues), (hdc, iPixelFormat, iLayerPlane, nAttributes, piAttributes, piValues), 88, PFNWGLGETPIXELFORMATATTRIBIVEXTPROC)
GEN_THUNK_RET(wgl, PROC, wglGetProcAddress, (LPCSTR lpszProc), (lpszProc), 89, PFNWGLGETPROCADDRESSPROC)
GEN_THUNK_RET(wgl, int, wglGetSwapIntervalEXT, (void), (), 90, PFNWGLGETSWAPINTERVALEXTPROC)
GEN_THUNK_RET(wgl, BOOL, wglGetSyncValuesOML, (HDC hdc, INT64 * ust, INT64 * msc, INT64 * sbc), (hdc, ust, msc, sbc), 91, PFNWGLGETSYNCVALUESOMLPROC)
GEN_THUNK_RET(wgl, BOOL, wglGetVideoDeviceNV, (HDC hDC, int numDevices, HPVIDEODEV * hVideoDevice), (hDC, numDevices, hVideoDevice), 92, PFNWGLGETVIDEODEVICENVPROC)
GEN_THUNK_RET(wgl, BOOL, wglGetVideoInfoNV, (HPVIDEODEV hpVideoDevice, unsigned long * pulCounterOutputPbuffer, unsigned long * pulCounterOutputVideo), (hpVideoDevice, pulCounterOutputPbuffer, pulCounterOutputVideo), 93, PFNWGLGETVIDEOINFONVPROC)
GEN_THUNK_RET(wgl, BOOL, wglIsEnabledFrameLockI3D, (BOOL * pFlag), (pFlag), 94, PFNWGLISENABLEDFRAMELOCKI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglIsEnabledGenlockI3D, (HDC hDC, BOOL * pFlag), (hDC, pFlag), 95, PFNWGLISENABLEDGENLOCKI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglJoinSwapGroupNV, (HDC hDC, GLuint group), (hDC, group), 96, PFNWGLJOINSWAPGROUPNVPROC)
GEN_THUNK_RET(wgl, GLboolean, wglLoadDisplayColorTableEXT, (const GLushort * table, GLuint length), (table, length), 97, PFNWGLLOADDISPLAYCOLORTABLEEXTPROC)
GEN_THUNK_RET(wgl, BOOL, wglLockVideoCaptureDeviceNV, (HDC hDc, HVIDEOINPUTDEVICENV hDevice), (hDc, hDevice), 98, PFNWGLLOCKVIDEOCAPTUREDEVICENVPROC)
GEN_THUNK_RET(wgl, BOOL, wglMakeAssociatedContextCurrentAMD, (HGLRC hglrc), (hglrc), 99, PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC)
GEN_THUNK_RET(wgl, BOOL, wglMakeContextCurrentARB, (HDC hDrawDC, HDC hReadDC, HGLRC hglrc), (hDrawDC, hReadDC, hglrc), 100, PFNWGLMAKECONTEXTCURRENTARBPROC)
GEN_THUNK_RET(wgl, BOOL, wglMakeContextCurrentEXT, (HDC hDrawDC, HDC hReadDC, HGLRC hglrc), (hDrawDC, hReadDC, hglrc), 101, PFNWGLMAKECONTEXTCURRENTEXTPROC)
GEN_THUNK_RET(wgl, BOOL, wglMakeCurrent, (HDC hDc, HGLRC newContext), (hDc, newContext), 102, PFNWGLMAKECURRENTPROC)
GEN_THUNK_RET(wgl, BOOL, wglQueryCurrentContextNV, (int iAttribute, int * piValue), (iAttribute, piValue), 103, PFNWGLQUERYCURRENTCONTEXTNVPROC)
GEN_THUNK_RET(wgl, BOOL, wglQueryFrameCountNV, (HDC hDC, GLuint * count), (hDC, count), 104, PFNWGLQUERYFRAMECOUNTNVPROC)
GEN_THUNK_RET(wgl, BOOL, wglQueryFrameLockMasterI3D, (BOOL * pFlag), (pFlag), 105, PFNWGLQUERYFRAMELOCKMASTERI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglQueryFrameTrackingI3D, (DWORD * pFrameCount, DWORD * pMissedFrames, float * pLastMissedUsage), (pFrameCount, pMissedFrames, pLastMissedUsage), 106, PFNWGLQUERYFRAMETRACKINGI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglQueryGenlockMaxSourceDelayI3D, (HDC hDC, UINT * uMaxLineDelay, UINT * uMaxPixelDelay), (hDC, uMaxLineDelay, uMaxPixelDelay), 107, PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglQueryMaxSwapGroupsNV, (HDC hDC, GLuint * maxGroups, GLuint * maxBarriers), (hDC, maxGroups, maxBarriers), 108, PFNWGLQUERYMAXSWAPGROUPSNVPROC)
GEN_THUNK_RET(wgl, BOOL, wglQueryPbufferARB, (HPBUFFERARB hPbuffer, int iAttribute, int * piValue), (hPbuffer, iAttribute, piValue), 109, PFNWGLQUERYPBUFFERARBPROC)
GEN_THUNK_RET(wgl, BOOL, wglQueryPbufferEXT, (HPBUFFEREXT hPbuffer, int iAttribute, int * piValue), (hPbuffer, iAttribute, piValue), 110, PFNWGLQUERYPBUFFEREXTPROC)
GEN_THUNK_RET(wgl, BOOL, wglQuerySwapGroupNV, (HDC hDC, GLuint * group, GLuint * barrier), (hDC, group, barrier), 111, PFNWGLQUERYSWAPGROUPNVPROC)
GEN_THUNK_RET(wgl, BOOL, wglQueryVideoCaptureDeviceNV, (HDC hDc, HVIDEOINPUTDEVICENV hDevice, int iAttribute, int * piValue), (hDc, hDevice, iAttribute, piValue), 112, PFNWGLQUERYVIDEOCAPTUREDEVICENVPROC)
GEN_THUNK_RET(wgl, BOOL, wglRealizeLayerPalette, (HDC hdc, int iLayerPlane, BOOL bRealize), (hdc, iLayerPlane, bRealize), 113, PFNWGLREALIZELAYERPALETTEPROC)
GEN_THUNK_RET(wgl, BOOL, wglReleaseImageBufferEventsI3D, (HDC hDC, const LPVOID * pAddress, UINT count), (hDC, pAddress, count), 114, PFNWGLRELEASEIMAGEBUFFEREVENTSI3DPROC)
GEN_THUNK_RET(wgl, int, wglReleasePbufferDCARB, (HPBUFFERARB hPbuffer, HDC hDC), (hPbuffer, hDC), 115, PFNWGLRELEASEPBUFFERDCARBPROC)
GEN_THUNK_RET(wgl, int, wglReleasePbufferDCEXT, (HPBUFFEREXT hPbuffer, HDC hDC), (hPbuffer, hDC), 116, PFNWGLRELEASEPBUFFERDCEXTPROC)
GEN_THUNK_RET(wgl, BOOL, wglReleaseTexImageARB, (HPBUFFERARB hPbuffer, int iBuffer), (hPbuffer, iBuffer), 117, PFNWGLRELEASETEXIMAGEARBPROC)
GEN_THUNK_RET(wgl, BOOL, wglReleaseVideoCaptureDeviceNV, (HDC hDc, HVIDEOINPUTDEVICENV hDevice), (hDc, hDevice), 118, PFNWGLRELEASEVIDEOCAPTUREDEVICENVPROC)
GEN_THUNK_RET(wgl, BOOL, wglReleaseVideoDeviceNV, (HPVIDEODEV hVideoDevice), (hVideoDevice), 119, PFNWGLRELEASEVIDEODEVICENVPROC)
GEN_THUNK_RET(wgl, BOOL, wglReleaseVideoImageNV, (HPBUFFERARB hPbuffer, int iVideoBuffer), (hPbuffer, iVideoBuffer), 120, PFNWGLRELEASEVIDEOIMAGENVPROC)
GEN_THUNK_RET(wgl, BOOL, wglResetFrameCountNV, (HDC hDC), (hDC), 121, PFNWGLRESETFRAMECOUNTNVPROC)
GEN_THUNK_RET(wgl, BOOL, wglRestoreBufferRegionARB, (HANDLE hRegion, int x, int y, int width, int height, int xSrc, int ySrc), (hRegion, x, y, width, height, xSrc, ySrc), 122, PFNWGLRESTOREBUFFERREGIONARBPROC)
GEN_THUNK_RET(wgl, BOOL, wglSaveBufferRegionARB, (HANDLE hRegion, int x, int y, int width, int height), (hRegion, x, y, width, height), 123, PFNWGLSAVEBUFFERREGIONARBPROC)
GEN_THUNK_RET(wgl, BOOL, wglSendPbufferToVideoNV, (HPBUFFERARB hPbuffer, int iBufferType, unsigned long * pulCounterPbuffer, BOOL bBlock), (hPbuffer, iBufferType, pulCounterPbuffer, bBlock), 124, PFNWGLSENDPBUFFERTOVIDEONVPROC)
GEN_THUNK_RET(wgl, BOOL, wglSetDigitalVideoParametersI3D, (HDC hDC, int iAttribute, const int * piValue), (hDC, iAttribute, piValue), 125, PFNWGLSETDIGITALVIDEOPARAMETERSI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglSetGammaTableI3D, (HDC hDC, int iEntries, const USHORT * puRed, const USHORT * puGreen, const USHORT * puBlue), (hDC, iEntries, puRed, puGreen, puBlue), 126, PFNWGLSETGAMMATABLEI3DPROC)
GEN_THUNK_RET(wgl, BOOL, wglSetGammaTableParametersI3D, (HDC hDC, int iAttribute, const int * piValue), (hDC, iAttribute, piValue), 127, PFNWGLSETGAMMATABLEPARAMETERSI3DPROC)
GEN_THUNK_RET(wgl, int, wglSetLayerPaletteEntries, (HDC hdc, int iLayerPlane, int iStart, int cEntries, const COLORREF * pcr), (hdc, iLayerPlane, iStart, cEntries, pcr), 128, PFNWGLSETLAYERPALETTEENTRIESPROC)
GEN_THUNK_RET(wgl, BOOL, wglSetPbufferAttribARB, (HPBUFFERARB hPbuffer, const int * piAttribList), (hPbuffer, piAttribList), 129, PFNWGLSETPBUFFERATTRIBARBPROC)
GEN_THUNK_RET(wgl, BOOL, wglSetPixelFormat, (HDC hdc, int ipfd, const PIXELFORMATDESCRIPTOR * ppfd), (hdc, ipfd, ppfd), 130, PFNWGLSETPIXELFORMATPROC)
GEN_THUNK_RET(wgl, BOOL, wglSetStereoEmitterState3DL, (HDC hDC, UINT uState), (hDC, uState), 131, PFNWGLSETSTEREOEMITTERSTATE3DLPROC)
GEN_THUNK_RET(wgl, BOOL, wglShareLists, (HGLRC hrcSrvShare, HGLRC hrcSrvSource), (hrcSrvShare, hrcSrvSource), 132, PFNWGLSHARELISTSPROC)
GEN_THUNK_RET(wgl, BOOL, wglSwapBuffers, (HDC hdc), (hdc), 133, PFNWGLSWAPBUFFERSPROC)
GEN_THUNK_RET(wgl, INT64, wglSwapBuffersMscOML, (HDC hdc, INT64 target_msc, INT64 divisor, INT64 remainder), (hdc, target_msc, divisor, remainder), 134, PFNWGLSWAPBUFFERSMSCOMLPROC)
GEN_THUNK_RET(wgl, BOOL, wglSwapIntervalEXT, (int interval), (interval), 135, PFNWGLSWAPINTERVALEXTPROC)
GEN_THUNK_RET(wgl, BOOL, wglSwapLayerBuffers, (HDC hdc, UINT fuFlags), (hdc, fuFlags), 136, PFNWGLSWAPLAYERBUFFERSPROC)
GEN_THUNK_RET(wgl, INT64, wglSwapLayerBuffersMscOML, (HDC hdc, int fuPlanes, INT64 target_msc, INT64 divisor, INT64 remainder), (hdc, fuPlanes, target_msc, divisor, remainder), 137, PFNWGLSWAPLAYERBUFFERSMSCOMLPROC)
GEN_THUNK_RET(wgl, BOOL, wglUseFontBitmapsA, (HDC hDC, DWORD first, DWORD count, DWORD listBase), (hDC, first, count, listBase), 138, PFNWGLUSEFONTBITMAPSAPROC)
GEN_THUNK_RET(wgl, BOOL, wglUseFontBitmapsW, (HDC hDC, DWORD first, DWORD count, DWORD listBase), (hDC, first, count, listBase), 139, PFNWGLUSEFONTBITMAPSWPROC)
GEN_THUNK_RET(wgl, BOOL, wglUseFontOutlines, (HDC hDC, DWORD first, DWORD count, DWORD listBase, FLOAT deviation, FLOAT extrusion, int format, LPGLYPHMETRICSFLOAT lpgmf), (hDC, first, count, listBase, deviation, extrusion, format, lpgmf), 140, PFNWGLUSEFONTOUTLINESPROC)
GEN_THUNK_RET(wgl, BOOL, wglUseFontOutlinesA, (HDC hDC, DWORD first, DWORD count, DWORD listBase, FLOAT deviation, FLOAT extrusion, int format, LPGLYPHMETRICSFLOAT lpgmf), (hDC, first, count, listBase, deviation, extrusion, format, lpgmf), 141, PFNWGLUSEFONTOUTLINESAPROC)
GEN_THUNK_RET(wgl, BOOL, wglUseFontOutlinesW, (HDC hDC, DWORD first, DWORD count, DWORD listBase, FLOAT deviation, FLOAT extrusion, int format, LPGLYPHMETRICSFLOAT lpgmf), (hDC, first, count, listBase, deviation, extrusion, format, lpgmf), 142, PFNWGLUSEFONTOUTLINESWPROC)
GEN_THUNK_RET(wgl, BOOL, wglWaitForMscOML, (HDC hdc, INT64 target_msc, INT64 divisor, INT64 remainder, INT64 * ust, INT64 * msc, INT64 * sbc), (hdc, target_msc, divisor, remainder, ust, msc, sbc), 143, PFNWGLWAITFORMSCOMLPROC)
GEN_THUNK_RET(wgl, BOOL, wglWaitForSbcOML, (HDC hdc, INT64 target_sbc, INT64 * ust, INT64 * msc, INT64 * sbc), (hdc, target_sbc, ust, msc, sbc), 144, PFNWGLWAITFORSBCOMLPROC)

#endif /* PLATFORM_HAS_WGL */

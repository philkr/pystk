/* GL dispatch code.
 * This is code-generated from the GL API XML files from Khronos.
 */
#include "dispatch_common.h"
#if PLATFORM_HAS_EGL

#define egl_extensions_count 100

static const char egl_extension_enum_strings[] =
    "EGL_ANDROID_blob_cache\0"
    "EGL_ANDROID_create_native_client_buffer\0"
    "EGL_ANDROID_framebuffer_target\0"
    "EGL_ANDROID_front_buffer_auto_refresh\0"
    "EGL_ANDROID_image_native_buffer\0"
    "EGL_ANDROID_native_fence_sync\0"
    "EGL_ANDROID_presentation_time\0"
    "EGL_ANDROID_recordable\0"
    "EGL_ANGLE_d3d_share_handle_client_buffer\0"
    "EGL_ANGLE_device_d3d\0"
    "EGL_ANGLE_query_surface_pointer\0"
    "EGL_ANGLE_surface_d3d_texture_2d_share_handle\0"
    "EGL_ANGLE_window_fixed_size\0"
    "EGL_ARM_pixmap_multisample_discard\0"
    "EGL_EXT_buffer_age\0"
    "EGL_EXT_client_extensions\0"
    "EGL_EXT_create_context_robustness\0"
    "EGL_EXT_device_base\0"
    "EGL_EXT_device_drm\0"
    "EGL_EXT_device_enumeration\0"
    "EGL_EXT_device_openwf\0"
    "EGL_EXT_device_query\0"
    "EGL_EXT_image_dma_buf_import\0"
    "EGL_EXT_multiview_window\0"
    "EGL_EXT_output_base\0"
    "EGL_EXT_output_drm\0"
    "EGL_EXT_output_openwf\0"
    "EGL_EXT_platform_base\0"
    "EGL_EXT_platform_device\0"
    "EGL_EXT_platform_wayland\0"
    "EGL_EXT_platform_x11\0"
    "EGL_EXT_protected_content\0"
    "EGL_EXT_protected_surface\0"
    "EGL_EXT_stream_consumer_egloutput\0"
    "EGL_EXT_swap_buffers_with_damage\0"
    "EGL_EXT_yuv_surface\0"
    "EGL_HI_clientpixmap\0"
    "EGL_HI_colorformats\0"
    "EGL_IMG_context_priority\0"
    "EGL_IMG_image_plane_attribs\0"
    "EGL_KHR_cl_event\0"
    "EGL_KHR_cl_event2\0"
    "EGL_KHR_client_get_all_proc_addresses\0"
    "EGL_KHR_config_attribs\0"
    "EGL_KHR_create_context\0"
    "EGL_KHR_create_context_no_error\0"
    "EGL_KHR_debug\0"
    "EGL_KHR_fence_sync\0"
    "EGL_KHR_get_all_proc_addresses\0"
    "EGL_KHR_gl_colorspace\0"
    "EGL_KHR_gl_renderbuffer_image\0"
    "EGL_KHR_gl_texture_2D_image\0"
    "EGL_KHR_gl_texture_3D_image\0"
    "EGL_KHR_gl_texture_cubemap_image\0"
    "EGL_KHR_image\0"
    "EGL_KHR_image_base\0"
    "EGL_KHR_image_pixmap\0"
    "EGL_KHR_lock_surface\0"
    "EGL_KHR_lock_surface2\0"
    "EGL_KHR_lock_surface3\0"
    "EGL_KHR_mutable_render_buffer\0"
    "EGL_KHR_partial_update\0"
    "EGL_KHR_platform_android\0"
    "EGL_KHR_platform_gbm\0"
    "EGL_KHR_platform_wayland\0"
    "EGL_KHR_platform_x11\0"
    "EGL_KHR_reusable_sync\0"
    "EGL_KHR_stream\0"
    "EGL_KHR_stream_consumer_gltexture\0"
    "EGL_KHR_stream_cross_process_fd\0"
    "EGL_KHR_stream_fifo\0"
    "EGL_KHR_stream_producer_aldatalocator\0"
    "EGL_KHR_stream_producer_eglsurface\0"
    "EGL_KHR_surfaceless_context\0"
    "EGL_KHR_swap_buffers_with_damage\0"
    "EGL_KHR_vg_parent_image\0"
    "EGL_KHR_wait_sync\0"
    "EGL_MESA_drm_image\0"
    "EGL_MESA_image_dma_buf_export\0"
    "EGL_MESA_platform_gbm\0"
    "EGL_NOK_swap_region\0"
    "EGL_NOK_swap_region2\0"
    "EGL_NOK_texture_from_pixmap\0"
    "EGL_NV_3dvision_surface\0"
    "EGL_NV_coverage_sample\0"
    "EGL_NV_coverage_sample_resolve\0"
    "EGL_NV_cuda_event\0"
    "EGL_NV_depth_nonlinear\0"
    "EGL_NV_device_cuda\0"
    "EGL_NV_native_query\0"
    "EGL_NV_post_convert_rounding\0"
    "EGL_NV_post_sub_buffer\0"
    "EGL_NV_robustness_video_memory_purge\0"
    "EGL_NV_stream_consumer_gltexture_yuv\0"
    "EGL_NV_stream_metadata\0"
    "EGL_NV_stream_sync\0"
    "EGL_NV_sync\0"
    "EGL_NV_system_time\0"
    "EGL_TIZEN_image_native_buffer\0"
    "EGL_TIZEN_image_native_surface\0"
;
static const khronos_uint16_t egl_extension_offsets[] = {
    0,
    23,
    63,
    94,
    132,
    164,
    194,
    224,
    247,
    288,
    309,
    341,
    387,
    415,
    450,
    469,
    495,
    529,
    549,
    568,
    595,
    617,
    638,
    667,
    692,
    712,
    731,
    753,
    775,
    799,
    824,
    845,
    871,
    897,
    931,
    964,
    984,
    1004,
    1024,
    1049,
    1077,
    1094,
    1112,
    1150,
    1173,
    1196,
    1228,
    1242,
    1261,
    1292,
    1314,
    1344,
    1372,
    1400,
    1433,
    1447,
    1466,
    1487,
    1508,
    1530,
    1552,
    1582,
    1605,
    1630,
    1651,
    1676,
    1697,
    1719,
    1734,
    1768,
    1800,
    1820,
    1858,
    1893,
    1921,
    1954,
    1978,
    1996,
    2015,
    2045,
    2067,
    2087,
    2108,
    2136,
    2160,
    2183,
    2214,
    2232,
    2255,
    2274,
    2294,
    2323,
    2346,
    2383,
    2420,
    2443,
    2462,
    2474,
    2493,
    2523,
    2554
};

static const khronos_uint8_t egl_entrypoint_strings[] = {
    101, 103, 108, 66, 105, 110, 100, 65, 80, 73, 0, /*eglBindAPI*/
    101, 103, 108, 66, 105, 110, 100, 84, 101, 120, 73, 109, 97, 103, 101, 0, /*eglBindTexImage*/
    101, 103, 108, 67, 104, 111, 111, 115, 101, 67, 111, 110, 102, 105, 103, 0, /*eglChooseConfig*/
    101, 103, 108, 67, 108, 105, 101, 110, 116, 87, 97, 105, 116, 83, 121, 110, 99, 0, /*eglClientWaitSync*/
    101, 103, 108, 67, 108, 105, 101, 110, 116, 87, 97, 105, 116, 83, 121, 110, 99, 75, 72, 82, 0, /*eglClientWaitSyncKHR*/
    101, 103, 108, 67, 108, 105, 101, 110, 116, 87, 97, 105, 116, 83, 121, 110, 99, 78, 86, 0, /*eglClientWaitSyncNV*/
    101, 103, 108, 67, 111, 112, 121, 66, 117, 102, 102, 101, 114, 115, 0, /*eglCopyBuffers*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 67, 111, 110, 116, 101, 120, 116, 0, /*eglCreateContext*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 68, 82, 77, 73, 109, 97, 103, 101, 77, 69, 83, 65, 0, /*eglCreateDRMImageMESA*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 70, 101, 110, 99, 101, 83, 121, 110, 99, 78, 86, 0, /*eglCreateFenceSyncNV*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 73, 109, 97, 103, 101, 0, /*eglCreateImage*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 73, 109, 97, 103, 101, 75, 72, 82, 0, /*eglCreateImageKHR*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 78, 97, 116, 105, 118, 101, 67, 108, 105, 101, 110, 116, 66, 117, 102, 102, 101, 114, 65, 78, 68, 82, 79, 73, 68, 0, /*eglCreateNativeClientBufferANDROID*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 80, 98, 117, 102, 102, 101, 114, 70, 114, 111, 109, 67, 108, 105, 101, 110, 116, 66, 117, 102, 102, 101, 114, 0, /*eglCreatePbufferFromClientBuffer*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 80, 98, 117, 102, 102, 101, 114, 83, 117, 114, 102, 97, 99, 101, 0, /*eglCreatePbufferSurface*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 80, 105, 120, 109, 97, 112, 83, 117, 114, 102, 97, 99, 101, 0, /*eglCreatePixmapSurface*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 80, 105, 120, 109, 97, 112, 83, 117, 114, 102, 97, 99, 101, 72, 73, 0, /*eglCreatePixmapSurfaceHI*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 80, 108, 97, 116, 102, 111, 114, 109, 80, 105, 120, 109, 97, 112, 83, 117, 114, 102, 97, 99, 101, 0, /*eglCreatePlatformPixmapSurface*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 80, 108, 97, 116, 102, 111, 114, 109, 80, 105, 120, 109, 97, 112, 83, 117, 114, 102, 97, 99, 101, 69, 88, 84, 0, /*eglCreatePlatformPixmapSurfaceEXT*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 80, 108, 97, 116, 102, 111, 114, 109, 87, 105, 110, 100, 111, 119, 83, 117, 114, 102, 97, 99, 101, 0, /*eglCreatePlatformWindowSurface*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 80, 108, 97, 116, 102, 111, 114, 109, 87, 105, 110, 100, 111, 119, 83, 117, 114, 102, 97, 99, 101, 69, 88, 84, 0, /*eglCreatePlatformWindowSurfaceEXT*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 83, 116, 114, 101, 97, 109, 70, 114, 111, 109, 70, 105, 108, 101, 68, 101, 115, 99, 114, 105, 112, 116, 111, 114, 75, 72, 82, 0, /*eglCreateStreamFromFileDescriptorKHR*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 83, 116, 114, 101, 97, 109, 75, 72, 82, 0, /*eglCreateStreamKHR*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 83, 116, 114, 101, 97, 109, 80, 114, 111, 100, 117, 99, 101, 114, 83, 117, 114, 102, 97, 99, 101, 75, 72, 82, 0, /*eglCreateStreamProducerSurfaceKHR*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 83, 116, 114, 101, 97, 109, 83, 121, 110, 99, 78, 86, 0, /*eglCreateStreamSyncNV*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 83, 121, 110, 99, 0, /*eglCreateSync*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 83, 121, 110, 99, 54, 52, 75, 72, 82, 0, /*eglCreateSync64KHR*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 83, 121, 110, 99, 75, 72, 82, 0, /*eglCreateSyncKHR*/
    101, 103, 108, 67, 114, 101, 97, 116, 101, 87, 105, 110, 100, 111, 119, 83, 117, 114, 102, 97, 99, 101, 0, /*eglCreateWindowSurface*/
    101, 103, 108, 68, 101, 98, 117, 103, 77, 101, 115, 115, 97, 103, 101, 67, 111, 110, 116, 114, 111, 108, 75, 72, 82, 0, /*eglDebugMessageControlKHR*/
    101, 103, 108, 68, 101, 115, 116, 114, 111, 121, 67, 111, 110, 116, 101, 120, 116, 0, /*eglDestroyContext*/
    101, 103, 108, 68, 101, 115, 116, 114, 111, 121, 73, 109, 97, 103, 101, 0, /*eglDestroyImage*/
    101, 103, 108, 68, 101, 115, 116, 114, 111, 121, 73, 109, 97, 103, 101, 75, 72, 82, 0, /*eglDestroyImageKHR*/
    101, 103, 108, 68, 101, 115, 116, 114, 111, 121, 83, 116, 114, 101, 97, 109, 75, 72, 82, 0, /*eglDestroyStreamKHR*/
    101, 103, 108, 68, 101, 115, 116, 114, 111, 121, 83, 117, 114, 102, 97, 99, 101, 0, /*eglDestroySurface*/
    101, 103, 108, 68, 101, 115, 116, 114, 111, 121, 83, 121, 110, 99, 0, /*eglDestroySync*/
    101, 103, 108, 68, 101, 115, 116, 114, 111, 121, 83, 121, 110, 99, 75, 72, 82, 0, /*eglDestroySyncKHR*/
    101, 103, 108, 68, 101, 115, 116, 114, 111, 121, 83, 121, 110, 99, 78, 86, 0, /*eglDestroySyncNV*/
    101, 103, 108, 68, 117, 112, 78, 97, 116, 105, 118, 101, 70, 101, 110, 99, 101, 70, 68, 65, 78, 68, 82, 79, 73, 68, 0, /*eglDupNativeFenceFDANDROID*/
    101, 103, 108, 69, 120, 112, 111, 114, 116, 68, 77, 65, 66, 85, 70, 73, 109, 97, 103, 101, 77, 69, 83, 65, 0, /*eglExportDMABUFImageMESA*/
    101, 103, 108, 69, 120, 112, 111, 114, 116, 68, 77, 65, 66, 85, 70, 73, 109, 97, 103, 101, 81, 117, 101, 114, 121, 77, 69, 83, 65, 0, /*eglExportDMABUFImageQueryMESA*/
    101, 103, 108, 69, 120, 112, 111, 114, 116, 68, 82, 77, 73, 109, 97, 103, 101, 77, 69, 83, 65, 0, /*eglExportDRMImageMESA*/
    101, 103, 108, 70, 101, 110, 99, 101, 78, 86, 0, /*eglFenceNV*/
    101, 103, 108, 71, 101, 116, 67, 111, 110, 102, 105, 103, 65, 116, 116, 114, 105, 98, 0, /*eglGetConfigAttrib*/
    101, 103, 108, 71, 101, 116, 67, 111, 110, 102, 105, 103, 115, 0, /*eglGetConfigs*/
    101, 103, 108, 71, 101, 116, 67, 117, 114, 114, 101, 110, 116, 67, 111, 110, 116, 101, 120, 116, 0, /*eglGetCurrentContext*/
    101, 103, 108, 71, 101, 116, 67, 117, 114, 114, 101, 110, 116, 68, 105, 115, 112, 108, 97, 121, 0, /*eglGetCurrentDisplay*/
    101, 103, 108, 71, 101, 116, 67, 117, 114, 114, 101, 110, 116, 83, 117, 114, 102, 97, 99, 101, 0, /*eglGetCurrentSurface*/
    101, 103, 108, 71, 101, 116, 68, 105, 115, 112, 108, 97, 121, 0, /*eglGetDisplay*/
    101, 103, 108, 71, 101, 116, 69, 114, 114, 111, 114, 0, /*eglGetError*/
    101, 103, 108, 71, 101, 116, 79, 117, 116, 112, 117, 116, 76, 97, 121, 101, 114, 115, 69, 88, 84, 0, /*eglGetOutputLayersEXT*/
    101, 103, 108, 71, 101, 116, 79, 117, 116, 112, 117, 116, 80, 111, 114, 116, 115, 69, 88, 84, 0, /*eglGetOutputPortsEXT*/
    101, 103, 108, 71, 101, 116, 80, 108, 97, 116, 102, 111, 114, 109, 68, 105, 115, 112, 108, 97, 121, 0, /*eglGetPlatformDisplay*/
    101, 103, 108, 71, 101, 116, 80, 108, 97, 116, 102, 111, 114, 109, 68, 105, 115, 112, 108, 97, 121, 69, 88, 84, 0, /*eglGetPlatformDisplayEXT*/
    101, 103, 108, 71, 101, 116, 80, 114, 111, 99, 65, 100, 100, 114, 101, 115, 115, 0, /*eglGetProcAddress*/
    101, 103, 108, 71, 101, 116, 83, 116, 114, 101, 97, 109, 70, 105, 108, 101, 68, 101, 115, 99, 114, 105, 112, 116, 111, 114, 75, 72, 82, 0, /*eglGetStreamFileDescriptorKHR*/
    101, 103, 108, 71, 101, 116, 83, 121, 110, 99, 65, 116, 116, 114, 105, 98, 0, /*eglGetSyncAttrib*/
    101, 103, 108, 71, 101, 116, 83, 121, 110, 99, 65, 116, 116, 114, 105, 98, 75, 72, 82, 0, /*eglGetSyncAttribKHR*/
    101, 103, 108, 71, 101, 116, 83, 121, 110, 99, 65, 116, 116, 114, 105, 98, 78, 86, 0, /*eglGetSyncAttribNV*/
    101, 103, 108, 71, 101, 116, 83, 121, 115, 116, 101, 109, 84, 105, 109, 101, 70, 114, 101, 113, 117, 101, 110, 99, 121, 78, 86, 0, /*eglGetSystemTimeFrequencyNV*/
    101, 103, 108, 71, 101, 116, 83, 121, 115, 116, 101, 109, 84, 105, 109, 101, 78, 86, 0, /*eglGetSystemTimeNV*/
    101, 103, 108, 73, 110, 105, 116, 105, 97, 108, 105, 122, 101, 0, /*eglInitialize*/
    101, 103, 108, 76, 97, 98, 101, 108, 79, 98, 106, 101, 99, 116, 75, 72, 82, 0, /*eglLabelObjectKHR*/
    101, 103, 108, 76, 111, 99, 107, 83, 117, 114, 102, 97, 99, 101, 75, 72, 82, 0, /*eglLockSurfaceKHR*/
    101, 103, 108, 77, 97, 107, 101, 67, 117, 114, 114, 101, 110, 116, 0, /*eglMakeCurrent*/
    101, 103, 108, 79, 117, 116, 112, 117, 116, 76, 97, 121, 101, 114, 65, 116, 116, 114, 105, 98, 69, 88, 84, 0, /*eglOutputLayerAttribEXT*/
    101, 103, 108, 79, 117, 116, 112, 117, 116, 80, 111, 114, 116, 65, 116, 116, 114, 105, 98, 69, 88, 84, 0, /*eglOutputPortAttribEXT*/
    101, 103, 108, 80, 111, 115, 116, 83, 117, 98, 66, 117, 102, 102, 101, 114, 78, 86, 0, /*eglPostSubBufferNV*/
    101, 103, 108, 80, 114, 101, 115, 101, 110, 116, 97, 116, 105, 111, 110, 84, 105, 109, 101, 65, 78, 68, 82, 79, 73, 68, 0, /*eglPresentationTimeANDROID*/
    101, 103, 108, 81, 117, 101, 114, 121, 65, 80, 73, 0, /*eglQueryAPI*/
    101, 103, 108, 81, 117, 101, 114, 121, 67, 111, 110, 116, 101, 120, 116, 0, /*eglQueryContext*/
    101, 103, 108, 81, 117, 101, 114, 121, 68, 101, 98, 117, 103, 75, 72, 82, 0, /*eglQueryDebugKHR*/
    101, 103, 108, 81, 117, 101, 114, 121, 68, 101, 118, 105, 99, 101, 65, 116, 116, 114, 105, 98, 69, 88, 84, 0, /*eglQueryDeviceAttribEXT*/
    101, 103, 108, 81, 117, 101, 114, 121, 68, 101, 118, 105, 99, 101, 83, 116, 114, 105, 110, 103, 69, 88, 84, 0, /*eglQueryDeviceStringEXT*/
    101, 103, 108, 81, 117, 101, 114, 121, 68, 101, 118, 105, 99, 101, 115, 69, 88, 84, 0, /*eglQueryDevicesEXT*/
    101, 103, 108, 81, 117, 101, 114, 121, 68, 105, 115, 112, 108, 97, 121, 65, 116, 116, 114, 105, 98, 69, 88, 84, 0, /*eglQueryDisplayAttribEXT*/
    101, 103, 108, 81, 117, 101, 114, 121, 68, 105, 115, 112, 108, 97, 121, 65, 116, 116, 114, 105, 98, 78, 86, 0, /*eglQueryDisplayAttribNV*/
    101, 103, 108, 81, 117, 101, 114, 121, 78, 97, 116, 105, 118, 101, 68, 105, 115, 112, 108, 97, 121, 78, 86, 0, /*eglQueryNativeDisplayNV*/
    101, 103, 108, 81, 117, 101, 114, 121, 78, 97, 116, 105, 118, 101, 80, 105, 120, 109, 97, 112, 78, 86, 0, /*eglQueryNativePixmapNV*/
    101, 103, 108, 81, 117, 101, 114, 121, 78, 97, 116, 105, 118, 101, 87, 105, 110, 100, 111, 119, 78, 86, 0, /*eglQueryNativeWindowNV*/
    101, 103, 108, 81, 117, 101, 114, 121, 79, 117, 116, 112, 117, 116, 76, 97, 121, 101, 114, 65, 116, 116, 114, 105, 98, 69, 88, 84, 0, /*eglQueryOutputLayerAttribEXT*/
    101, 103, 108, 81, 117, 101, 114, 121, 79, 117, 116, 112, 117, 116, 76, 97, 121, 101, 114, 83, 116, 114, 105, 110, 103, 69, 88, 84, 0, /*eglQueryOutputLayerStringEXT*/
    101, 103, 108, 81, 117, 101, 114, 121, 79, 117, 116, 112, 117, 116, 80, 111, 114, 116, 65, 116, 116, 114, 105, 98, 69, 88, 84, 0, /*eglQueryOutputPortAttribEXT*/
    101, 103, 108, 81, 117, 101, 114, 121, 79, 117, 116, 112, 117, 116, 80, 111, 114, 116, 83, 116, 114, 105, 110, 103, 69, 88, 84, 0, /*eglQueryOutputPortStringEXT*/
    101, 103, 108, 81, 117, 101, 114, 121, 83, 116, 114, 101, 97, 109, 75, 72, 82, 0, /*eglQueryStreamKHR*/
    101, 103, 108, 81, 117, 101, 114, 121, 83, 116, 114, 101, 97, 109, 77, 101, 116, 97, 100, 97, 116, 97, 78, 86, 0, /*eglQueryStreamMetadataNV*/
    101, 103, 108, 81, 117, 101, 114, 121, 83, 116, 114, 101, 97, 109, 84, 105, 109, 101, 75, 72, 82, 0, /*eglQueryStreamTimeKHR*/
    101, 103, 108, 81, 117, 101, 114, 121, 83, 116, 114, 101, 97, 109, 117, 54, 52, 75, 72, 82, 0, /*eglQueryStreamu64KHR*/
    101, 103, 108, 81, 117, 101, 114, 121, 83, 116, 114, 105, 110, 103, 0, /*eglQueryString*/
    101, 103, 108, 81, 117, 101, 114, 121, 83, 117, 114, 102, 97, 99, 101, 0, /*eglQuerySurface*/
    101, 103, 108, 81, 117, 101, 114, 121, 83, 117, 114, 102, 97, 99, 101, 54, 52, 75, 72, 82, 0, /*eglQuerySurface64KHR*/
    101, 103, 108, 81, 117, 101, 114, 121, 83, 117, 114, 102, 97, 99, 101, 80, 111, 105, 110, 116, 101, 114, 65, 78, 71, 76, 69, 0, /*eglQuerySurfacePointerANGLE*/
    101, 103, 108, 82, 101, 108, 101, 97, 115, 101, 84, 101, 120, 73, 109, 97, 103, 101, 0, /*eglReleaseTexImage*/
    101, 103, 108, 82, 101, 108, 101, 97, 115, 101, 84, 104, 114, 101, 97, 100, 0, /*eglReleaseThread*/
    101, 103, 108, 83, 101, 116, 66, 108, 111, 98, 67, 97, 99, 104, 101, 70, 117, 110, 99, 115, 65, 78, 68, 82, 79, 73, 68, 0, /*eglSetBlobCacheFuncsANDROID*/
    101, 103, 108, 83, 101, 116, 68, 97, 109, 97, 103, 101, 82, 101, 103, 105, 111, 110, 75, 72, 82, 0, /*eglSetDamageRegionKHR*/
    101, 103, 108, 83, 101, 116, 83, 116, 114, 101, 97, 109, 77, 101, 116, 97, 100, 97, 116, 97, 78, 86, 0, /*eglSetStreamMetadataNV*/
    101, 103, 108, 83, 105, 103, 110, 97, 108, 83, 121, 110, 99, 75, 72, 82, 0, /*eglSignalSyncKHR*/
    101, 103, 108, 83, 105, 103, 110, 97, 108, 83, 121, 110, 99, 78, 86, 0, /*eglSignalSyncNV*/
    101, 103, 108, 83, 116, 114, 101, 97, 109, 65, 116, 116, 114, 105, 98, 75, 72, 82, 0, /*eglStreamAttribKHR*/
    101, 103, 108, 83, 116, 114, 101, 97, 109, 67, 111, 110, 115, 117, 109, 101, 114, 65, 99, 113, 117, 105, 114, 101, 75, 72, 82, 0, /*eglStreamConsumerAcquireKHR*/
    101, 103, 108, 83, 116, 114, 101, 97, 109, 67, 111, 110, 115, 117, 109, 101, 114, 71, 76, 84, 101, 120, 116, 117, 114, 101, 69, 120, 116, 101, 114, 110, 97, 108, 65, 116, 116, 114, 105, 98, 115, 78, 86, 0, /*eglStreamConsumerGLTextureExternalAttribsNV*/
    101, 103, 108, 83, 116, 114, 101, 97, 109, 67, 111, 110, 115, 117, 109, 101, 114, 71, 76, 84, 101, 120, 116, 117, 114, 101, 69, 120, 116, 101, 114, 110, 97, 108, 75, 72, 82, 0, /*eglStreamConsumerGLTextureExternalKHR*/
    101, 103, 108, 83, 116, 114, 101, 97, 109, 67, 111, 110, 115, 117, 109, 101, 114, 79, 117, 116, 112, 117, 116, 69, 88, 84, 0, /*eglStreamConsumerOutputEXT*/
    101, 103, 108, 83, 116, 114, 101, 97, 109, 67, 111, 110, 115, 117, 109, 101, 114, 82, 101, 108, 101, 97, 115, 101, 75, 72, 82, 0, /*eglStreamConsumerReleaseKHR*/
    101, 103, 108, 83, 117, 114, 102, 97, 99, 101, 65, 116, 116, 114, 105, 98, 0, /*eglSurfaceAttrib*/
    101, 103, 108, 83, 119, 97, 112, 66, 117, 102, 102, 101, 114, 115, 0, /*eglSwapBuffers*/
    101, 103, 108, 83, 119, 97, 112, 66, 117, 102, 102, 101, 114, 115, 82, 101, 103, 105, 111, 110, 50, 78, 79, 75, 0, /*eglSwapBuffersRegion2NOK*/
    101, 103, 108, 83, 119, 97, 112, 66, 117, 102, 102, 101, 114, 115, 82, 101, 103, 105, 111, 110, 78, 79, 75, 0, /*eglSwapBuffersRegionNOK*/
    101, 103, 108, 83, 119, 97, 112, 66, 117, 102, 102, 101, 114, 115, 87, 105, 116, 104, 68, 97, 109, 97, 103, 101, 69, 88, 84, 0, /*eglSwapBuffersWithDamageEXT*/
    101, 103, 108, 83, 119, 97, 112, 66, 117, 102, 102, 101, 114, 115, 87, 105, 116, 104, 68, 97, 109, 97, 103, 101, 75, 72, 82, 0, /*eglSwapBuffersWithDamageKHR*/
    101, 103, 108, 83, 119, 97, 112, 73, 110, 116, 101, 114, 118, 97, 108, 0, /*eglSwapInterval*/
    101, 103, 108, 84, 101, 114, 109, 105, 110, 97, 116, 101, 0, /*eglTerminate*/
    101, 103, 108, 85, 110, 108, 111, 99, 107, 83, 117, 114, 102, 97, 99, 101, 75, 72, 82, 0, /*eglUnlockSurfaceKHR*/
    101, 103, 108, 87, 97, 105, 116, 67, 108, 105, 101, 110, 116, 0, /*eglWaitClient*/
    101, 103, 108, 87, 97, 105, 116, 71, 76, 0, /*eglWaitGL*/
    101, 103, 108, 87, 97, 105, 116, 78, 97, 116, 105, 118, 101, 0, /*eglWaitNative*/
    101, 103, 108, 87, 97, 105, 116, 83, 121, 110, 99, 0, /*eglWaitSync*/
    101, 103, 108, 87, 97, 105, 116, 83, 121, 110, 99, 75, 72, 82, 0, /*eglWaitSyncKHR*/
};

static const struct dispatch_resolve_info egl_resolve_info_table[] = {
    {DISPATCH_RESOLVE_VERSION, 0, EGL_1_2, 0}, /* eglBindAPI */
    {DISPATCH_RESOLVE_VERSION, 1, EGL_1_1, 11}, /* eglBindTexImage */
    {DISPATCH_RESOLVE_DIRECT, 2, EGL_1_0, 27}, /* eglChooseConfig */
    {DISPATCH_RESOLVE_VERSION, 3, EGL_1_5, 43}, /* eglClientWaitSync */
    {DISPATCH_RESOLVE_EXTENSION, 3, 47 /* EGL_KHR_fence_sync */, 61}, /* eglClientWaitSyncKHR */
    {DISPATCH_RESOLVE_EXTENSION, 3, 66 /* EGL_KHR_reusable_sync */, 61}, /* eglClientWaitSyncKHR */
    {DISPATCH_RESOLVE_EXTENSION, 4, 47 /* EGL_KHR_fence_sync */, 61}, /* eglClientWaitSyncKHR */
    {DISPATCH_RESOLVE_EXTENSION, 4, 66 /* EGL_KHR_reusable_sync */, 61}, /* eglClientWaitSyncKHR */
    {DISPATCH_RESOLVE_VERSION, 4, EGL_1_5, 43}, /* eglClientWaitSync */
    {DISPATCH_RESOLVE_EXTENSION, 5, 96 /* EGL_NV_sync */, 82}, /* eglClientWaitSyncNV */
    {DISPATCH_RESOLVE_DIRECT, 6, EGL_1_0, 102}, /* eglCopyBuffers */
    {DISPATCH_RESOLVE_DIRECT, 7, EGL_1_0, 117}, /* eglCreateContext */
    {DISPATCH_RESOLVE_EXTENSION, 8, 77 /* EGL_MESA_drm_image */, 134}, /* eglCreateDRMImageMESA */
    {DISPATCH_RESOLVE_EXTENSION, 9, 96 /* EGL_NV_sync */, 156}, /* eglCreateFenceSyncNV */
    {DISPATCH_RESOLVE_VERSION, 10, EGL_1_5, 177}, /* eglCreateImage */
    {DISPATCH_RESOLVE_EXTENSION, 11, 54 /* EGL_KHR_image */, 192}, /* eglCreateImageKHR */
    {DISPATCH_RESOLVE_EXTENSION, 11, 55 /* EGL_KHR_image_base */, 192}, /* eglCreateImageKHR */
    {DISPATCH_RESOLVE_EXTENSION, 12, 1 /* EGL_ANDROID_create_native_client_buffer */, 210}, /* eglCreateNativeClientBufferANDROID */
    {DISPATCH_RESOLVE_VERSION, 13, EGL_1_2, 245}, /* eglCreatePbufferFromClientBuffer */
    {DISPATCH_RESOLVE_DIRECT, 14, EGL_1_0, 278}, /* eglCreatePbufferSurface */
    {DISPATCH_RESOLVE_DIRECT, 15, EGL_1_0, 302}, /* eglCreatePixmapSurface */
    {DISPATCH_RESOLVE_EXTENSION, 16, 36 /* EGL_HI_clientpixmap */, 325}, /* eglCreatePixmapSurfaceHI */
    {DISPATCH_RESOLVE_VERSION, 17, EGL_1_5, 350}, /* eglCreatePlatformPixmapSurface */
    {DISPATCH_RESOLVE_EXTENSION, 18, 27 /* EGL_EXT_platform_base */, 381}, /* eglCreatePlatformPixmapSurfaceEXT */
    {DISPATCH_RESOLVE_VERSION, 19, EGL_1_5, 415}, /* eglCreatePlatformWindowSurface */
    {DISPATCH_RESOLVE_EXTENSION, 20, 27 /* EGL_EXT_platform_base */, 446}, /* eglCreatePlatformWindowSurfaceEXT */
    {DISPATCH_RESOLVE_EXTENSION, 21, 69 /* EGL_KHR_stream_cross_process_fd */, 480}, /* eglCreateStreamFromFileDescriptorKHR */
    {DISPATCH_RESOLVE_EXTENSION, 22, 67 /* EGL_KHR_stream */, 517}, /* eglCreateStreamKHR */
    {DISPATCH_RESOLVE_EXTENSION, 23, 72 /* EGL_KHR_stream_producer_eglsurface */, 536}, /* eglCreateStreamProducerSurfaceKHR */
    {DISPATCH_RESOLVE_EXTENSION, 24, 95 /* EGL_NV_stream_sync */, 570}, /* eglCreateStreamSyncNV */
    {DISPATCH_RESOLVE_VERSION, 25, EGL_1_5, 592}, /* eglCreateSync */
    {DISPATCH_RESOLVE_EXTENSION, 25, 41 /* EGL_KHR_cl_event2 */, 606}, /* eglCreateSync64KHR */
    {DISPATCH_RESOLVE_EXTENSION, 26, 41 /* EGL_KHR_cl_event2 */, 606}, /* eglCreateSync64KHR */
    {DISPATCH_RESOLVE_VERSION, 26, EGL_1_5, 592}, /* eglCreateSync */
    {DISPATCH_RESOLVE_EXTENSION, 27, 47 /* EGL_KHR_fence_sync */, 625}, /* eglCreateSyncKHR */
    {DISPATCH_RESOLVE_EXTENSION, 27, 66 /* EGL_KHR_reusable_sync */, 625}, /* eglCreateSyncKHR */
    {DISPATCH_RESOLVE_DIRECT, 28, EGL_1_0, 642}, /* eglCreateWindowSurface */
    {DISPATCH_RESOLVE_EXTENSION, 29, 46 /* EGL_KHR_debug */, 665}, /* eglDebugMessageControlKHR */
    {DISPATCH_RESOLVE_DIRECT, 30, EGL_1_0, 691}, /* eglDestroyContext */
    {DISPATCH_RESOLVE_VERSION, 31, EGL_1_5, 709}, /* eglDestroyImage */
    {DISPATCH_RESOLVE_EXTENSION, 31, 54 /* EGL_KHR_image */, 725}, /* eglDestroyImageKHR */
    {DISPATCH_RESOLVE_EXTENSION, 31, 55 /* EGL_KHR_image_base */, 725}, /* eglDestroyImageKHR */
    {DISPATCH_RESOLVE_EXTENSION, 32, 54 /* EGL_KHR_image */, 725}, /* eglDestroyImageKHR */
    {DISPATCH_RESOLVE_EXTENSION, 32, 55 /* EGL_KHR_image_base */, 725}, /* eglDestroyImageKHR */
    {DISPATCH_RESOLVE_VERSION, 32, EGL_1_5, 709}, /* eglDestroyImage */
    {DISPATCH_RESOLVE_EXTENSION, 33, 67 /* EGL_KHR_stream */, 744}, /* eglDestroyStreamKHR */
    {DISPATCH_RESOLVE_DIRECT, 34, EGL_1_0, 764}, /* eglDestroySurface */
    {DISPATCH_RESOLVE_VERSION, 35, EGL_1_5, 782}, /* eglDestroySync */
    {DISPATCH_RESOLVE_EXTENSION, 35, 47 /* EGL_KHR_fence_sync */, 797}, /* eglDestroySyncKHR */
    {DISPATCH_RESOLVE_EXTENSION, 35, 66 /* EGL_KHR_reusable_sync */, 797}, /* eglDestroySyncKHR */
    {DISPATCH_RESOLVE_EXTENSION, 36, 47 /* EGL_KHR_fence_sync */, 797}, /* eglDestroySyncKHR */
    {DISPATCH_RESOLVE_EXTENSION, 36, 66 /* EGL_KHR_reusable_sync */, 797}, /* eglDestroySyncKHR */
    {DISPATCH_RESOLVE_VERSION, 36, EGL_1_5, 782}, /* eglDestroySync */
    {DISPATCH_RESOLVE_EXTENSION, 37, 96 /* EGL_NV_sync */, 815}, /* eglDestroySyncNV */
    {DISPATCH_RESOLVE_EXTENSION, 38, 5 /* EGL_ANDROID_native_fence_sync */, 832}, /* eglDupNativeFenceFDANDROID */
    {DISPATCH_RESOLVE_EXTENSION, 39, 78 /* EGL_MESA_image_dma_buf_export */, 859}, /* eglExportDMABUFImageMESA */
    {DISPATCH_RESOLVE_EXTENSION, 40, 78 /* EGL_MESA_image_dma_buf_export */, 884}, /* eglExportDMABUFImageQueryMESA */
    {DISPATCH_RESOLVE_EXTENSION, 41, 77 /* EGL_MESA_drm_image */, 914}, /* eglExportDRMImageMESA */
    {DISPATCH_RESOLVE_EXTENSION, 42, 96 /* EGL_NV_sync */, 936}, /* eglFenceNV */
    {DISPATCH_RESOLVE_DIRECT, 43, EGL_1_0, 947}, /* eglGetConfigAttrib */
    {DISPATCH_RESOLVE_DIRECT, 44, EGL_1_0, 966}, /* eglGetConfigs */
    {DISPATCH_RESOLVE_VERSION, 45, EGL_1_4, 980}, /* eglGetCurrentContext */
    {DISPATCH_RESOLVE_DIRECT, 46, EGL_1_0, 1001}, /* eglGetCurrentDisplay */
    {DISPATCH_RESOLVE_DIRECT, 47, EGL_1_0, 1022}, /* eglGetCurrentSurface */
    {DISPATCH_RESOLVE_DIRECT, 48, EGL_1_0, 1043}, /* eglGetDisplay */
    {DISPATCH_RESOLVE_DIRECT, 49, EGL_1_0, 1057}, /* eglGetError */
    {DISPATCH_RESOLVE_EXTENSION, 50, 24 /* EGL_EXT_output_base */, 1069}, /* eglGetOutputLayersEXT */
    {DISPATCH_RESOLVE_EXTENSION, 51, 24 /* EGL_EXT_output_base */, 1091}, /* eglGetOutputPortsEXT */
    {DISPATCH_RESOLVE_VERSION, 52, EGL_1_5, 1112}, /* eglGetPlatformDisplay */
    {DISPATCH_RESOLVE_EXTENSION, 53, 27 /* EGL_EXT_platform_base */, 1134}, /* eglGetPlatformDisplayEXT */
    {DISPATCH_RESOLVE_DIRECT, 54, EGL_1_0, 1159}, /* eglGetProcAddress */
    {DISPATCH_RESOLVE_EXTENSION, 55, 69 /* EGL_KHR_stream_cross_process_fd */, 1177}, /* eglGetStreamFileDescriptorKHR */
    {DISPATCH_RESOLVE_VERSION, 56, EGL_1_5, 1207}, /* eglGetSyncAttrib */
    {DISPATCH_RESOLVE_EXTENSION, 57, 47 /* EGL_KHR_fence_sync */, 1224}, /* eglGetSyncAttribKHR */
    {DISPATCH_RESOLVE_EXTENSION, 57, 66 /* EGL_KHR_reusable_sync */, 1224}, /* eglGetSyncAttribKHR */
    {DISPATCH_RESOLVE_EXTENSION, 58, 96 /* EGL_NV_sync */, 1244}, /* eglGetSyncAttribNV */
    {DISPATCH_RESOLVE_EXTENSION, 59, 97 /* EGL_NV_system_time */, 1263}, /* eglGetSystemTimeFrequencyNV */
    {DISPATCH_RESOLVE_EXTENSION, 60, 97 /* EGL_NV_system_time */, 1291}, /* eglGetSystemTimeNV */
    {DISPATCH_RESOLVE_DIRECT, 61, EGL_1_0, 1310}, /* eglInitialize */
    {DISPATCH_RESOLVE_EXTENSION, 62, 46 /* EGL_KHR_debug */, 1324}, /* eglLabelObjectKHR */
    {DISPATCH_RESOLVE_EXTENSION, 63, 57 /* EGL_KHR_lock_surface */, 1342}, /* eglLockSurfaceKHR */
    {DISPATCH_RESOLVE_EXTENSION, 63, 59 /* EGL_KHR_lock_surface3 */, 1342}, /* eglLockSurfaceKHR */
    {DISPATCH_RESOLVE_DIRECT, 64, EGL_1_0, 1360}, /* eglMakeCurrent */
    {DISPATCH_RESOLVE_EXTENSION, 65, 24 /* EGL_EXT_output_base */, 1375}, /* eglOutputLayerAttribEXT */
    {DISPATCH_RESOLVE_EXTENSION, 66, 24 /* EGL_EXT_output_base */, 1399}, /* eglOutputPortAttribEXT */
    {DISPATCH_RESOLVE_EXTENSION, 67, 91 /* EGL_NV_post_sub_buffer */, 1422}, /* eglPostSubBufferNV */
    {DISPATCH_RESOLVE_EXTENSION, 68, 6 /* EGL_ANDROID_presentation_time */, 1441}, /* eglPresentationTimeANDROID */
    {DISPATCH_RESOLVE_VERSION, 69, EGL_1_2, 1468}, /* eglQueryAPI */
    {DISPATCH_RESOLVE_DIRECT, 70, EGL_1_0, 1480}, /* eglQueryContext */
    {DISPATCH_RESOLVE_EXTENSION, 71, 46 /* EGL_KHR_debug */, 1496}, /* eglQueryDebugKHR */
    {DISPATCH_RESOLVE_EXTENSION, 72, 17 /* EGL_EXT_device_base */, 1513}, /* eglQueryDeviceAttribEXT */
    {DISPATCH_RESOLVE_EXTENSION, 72, 21 /* EGL_EXT_device_query */, 1513}, /* eglQueryDeviceAttribEXT */
    {DISPATCH_RESOLVE_EXTENSION, 73, 17 /* EGL_EXT_device_base */, 1537}, /* eglQueryDeviceStringEXT */
    {DISPATCH_RESOLVE_EXTENSION, 73, 21 /* EGL_EXT_device_query */, 1537}, /* eglQueryDeviceStringEXT */
    {DISPATCH_RESOLVE_EXTENSION, 74, 17 /* EGL_EXT_device_base */, 1561}, /* eglQueryDevicesEXT */
    {DISPATCH_RESOLVE_EXTENSION, 74, 19 /* EGL_EXT_device_enumeration */, 1561}, /* eglQueryDevicesEXT */
    {DISPATCH_RESOLVE_EXTENSION, 75, 17 /* EGL_EXT_device_base */, 1580}, /* eglQueryDisplayAttribEXT */
    {DISPATCH_RESOLVE_EXTENSION, 75, 21 /* EGL_EXT_device_query */, 1580}, /* eglQueryDisplayAttribEXT */
    {DISPATCH_RESOLVE_EXTENSION, 75, 94 /* EGL_NV_stream_metadata */, 1605}, /* eglQueryDisplayAttribNV */
    {DISPATCH_RESOLVE_EXTENSION, 76, 94 /* EGL_NV_stream_metadata */, 1605}, /* eglQueryDisplayAttribNV */
    {DISPATCH_RESOLVE_EXTENSION, 76, 17 /* EGL_EXT_device_base */, 1580}, /* eglQueryDisplayAttribEXT */
    {DISPATCH_RESOLVE_EXTENSION, 76, 21 /* EGL_EXT_device_query */, 1580}, /* eglQueryDisplayAttribEXT */
    {DISPATCH_RESOLVE_EXTENSION, 77, 89 /* EGL_NV_native_query */, 1629}, /* eglQueryNativeDisplayNV */
    {DISPATCH_RESOLVE_EXTENSION, 78, 89 /* EGL_NV_native_query */, 1653}, /* eglQueryNativePixmapNV */
    {DISPATCH_RESOLVE_EXTENSION, 79, 89 /* EGL_NV_native_query */, 1676}, /* eglQueryNativeWindowNV */
    {DISPATCH_RESOLVE_EXTENSION, 80, 24 /* EGL_EXT_output_base */, 1699}, /* eglQueryOutputLayerAttribEXT */
    {DISPATCH_RESOLVE_EXTENSION, 81, 24 /* EGL_EXT_output_base */, 1728}, /* eglQueryOutputLayerStringEXT */
    {DISPATCH_RESOLVE_EXTENSION, 82, 24 /* EGL_EXT_output_base */, 1757}, /* eglQueryOutputPortAttribEXT */
    {DISPATCH_RESOLVE_EXTENSION, 83, 24 /* EGL_EXT_output_base */, 1785}, /* eglQueryOutputPortStringEXT */
    {DISPATCH_RESOLVE_EXTENSION, 84, 67 /* EGL_KHR_stream */, 1813}, /* eglQueryStreamKHR */
    {DISPATCH_RESOLVE_EXTENSION, 85, 94 /* EGL_NV_stream_metadata */, 1831}, /* eglQueryStreamMetadataNV */
    {DISPATCH_RESOLVE_EXTENSION, 86, 70 /* EGL_KHR_stream_fifo */, 1856}, /* eglQueryStreamTimeKHR */
    {DISPATCH_RESOLVE_EXTENSION, 87, 67 /* EGL_KHR_stream */, 1878}, /* eglQueryStreamu64KHR */
    {DISPATCH_RESOLVE_DIRECT, 88, EGL_1_0, 1899}, /* eglQueryString */
    {DISPATCH_RESOLVE_DIRECT, 89, EGL_1_0, 1914}, /* eglQuerySurface */
    {DISPATCH_RESOLVE_EXTENSION, 90, 59 /* EGL_KHR_lock_surface3 */, 1930}, /* eglQuerySurface64KHR */
    {DISPATCH_RESOLVE_EXTENSION, 91, 10 /* EGL_ANGLE_query_surface_pointer */, 1951}, /* eglQuerySurfacePointerANGLE */
    {DISPATCH_RESOLVE_VERSION, 92, EGL_1_1, 1979}, /* eglReleaseTexImage */
    {DISPATCH_RESOLVE_VERSION, 93, EGL_1_2, 1998}, /* eglReleaseThread */
    {DISPATCH_RESOLVE_EXTENSION, 94, 0 /* EGL_ANDROID_blob_cache */, 2015}, /* eglSetBlobCacheFuncsANDROID */
    {DISPATCH_RESOLVE_EXTENSION, 95, 61 /* EGL_KHR_partial_update */, 2043}, /* eglSetDamageRegionKHR */
    {DISPATCH_RESOLVE_EXTENSION, 96, 94 /* EGL_NV_stream_metadata */, 2065}, /* eglSetStreamMetadataNV */
    {DISPATCH_RESOLVE_EXTENSION, 97, 66 /* EGL_KHR_reusable_sync */, 2088}, /* eglSignalSyncKHR */
    {DISPATCH_RESOLVE_EXTENSION, 98, 96 /* EGL_NV_sync */, 2105}, /* eglSignalSyncNV */
    {DISPATCH_RESOLVE_EXTENSION, 99, 67 /* EGL_KHR_stream */, 2121}, /* eglStreamAttribKHR */
    {DISPATCH_RESOLVE_EXTENSION, 100, 68 /* EGL_KHR_stream_consumer_gltexture */, 2140}, /* eglStreamConsumerAcquireKHR */
    {DISPATCH_RESOLVE_EXTENSION, 101, 93 /* EGL_NV_stream_consumer_gltexture_yuv */, 2168}, /* eglStreamConsumerGLTextureExternalAttribsNV */
    {DISPATCH_RESOLVE_EXTENSION, 102, 68 /* EGL_KHR_stream_consumer_gltexture */, 2212}, /* eglStreamConsumerGLTextureExternalKHR */
    {DISPATCH_RESOLVE_EXTENSION, 103, 33 /* EGL_EXT_stream_consumer_egloutput */, 2250}, /* eglStreamConsumerOutputEXT */
    {DISPATCH_RESOLVE_EXTENSION, 104, 68 /* EGL_KHR_stream_consumer_gltexture */, 2277}, /* eglStreamConsumerReleaseKHR */
    {DISPATCH_RESOLVE_VERSION, 105, EGL_1_1, 2305}, /* eglSurfaceAttrib */
    {DISPATCH_RESOLVE_DIRECT, 106, EGL_1_0, 2322}, /* eglSwapBuffers */
    {DISPATCH_RESOLVE_EXTENSION, 107, 81 /* EGL_NOK_swap_region2 */, 2337}, /* eglSwapBuffersRegion2NOK */
    {DISPATCH_RESOLVE_EXTENSION, 108, 80 /* EGL_NOK_swap_region */, 2362}, /* eglSwapBuffersRegionNOK */
    {DISPATCH_RESOLVE_EXTENSION, 109, 34 /* EGL_EXT_swap_buffers_with_damage */, 2386}, /* eglSwapBuffersWithDamageEXT */
    {DISPATCH_RESOLVE_EXTENSION, 110, 74 /* EGL_KHR_swap_buffers_with_damage */, 2414}, /* eglSwapBuffersWithDamageKHR */
    {DISPATCH_RESOLVE_VERSION, 111, EGL_1_1, 2442}, /* eglSwapInterval */
    {DISPATCH_RESOLVE_DIRECT, 112, EGL_1_0, 2458}, /* eglTerminate */
    {DISPATCH_RESOLVE_EXTENSION, 113, 57 /* EGL_KHR_lock_surface */, 2471}, /* eglUnlockSurfaceKHR */
    {DISPATCH_RESOLVE_EXTENSION, 113, 59 /* EGL_KHR_lock_surface3 */, 2471}, /* eglUnlockSurfaceKHR */
    {DISPATCH_RESOLVE_VERSION, 114, EGL_1_2, 2491}, /* eglWaitClient */
    {DISPATCH_RESOLVE_DIRECT, 115, EGL_1_0, 2505}, /* eglWaitGL */
    {DISPATCH_RESOLVE_DIRECT, 116, EGL_1_0, 2515}, /* eglWaitNative */
    {DISPATCH_RESOLVE_VERSION, 117, EGL_1_5, 2529}, /* eglWaitSync */
    {DISPATCH_RESOLVE_EXTENSION, 118, 76 /* EGL_KHR_wait_sync */, 2541}, /* eglWaitSyncKHR */
    {DISPATCH_RESOLVE_TERMINATOR, 119, 0, 0}
};

static khronos_uint16_t egl_resolve_offsets[119] = {0};
static khronos_uint32_t egl_method_name_offsets[119] = {0};

#define HAS_DISPATCH_RESOLVE_DIRECT 1
#define HAS_DISPATCH_RESOLVE_VERSION 1
#define current_resolve egl_resolve
#define current_glproxy_resolve_init egl_glproxy_resolve_init
#define current_glproxy_resolve_direct egl_glproxy_resolve_direct
#define current_glproxy_resolve_version egl_glproxy_resolve_version
#define current_glproxy_resolve_extension egl_glproxy_resolve_extension
#define current_dispatch_table egl_dispatch_table
#define current_metadata egl_metadata
#define current_glproxy_resolve_local egl_glproxy_resolve_local
#define current_glproxy_dispatch_metadata_init egl_glproxy_dispatch_metadata_init
#define current_extension_offsets egl_extension_offsets
#define current_extensions_count egl_extensions_count
#define current_extension_enum_strings egl_extension_enum_strings
#define current_entrypoint_strings egl_entrypoint_strings
#define current_resolve_info_table egl_resolve_info_table
#define current_resolve_offsets egl_resolve_offsets
#define current_method_name_offsets egl_method_name_offsets
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

GEN_THUNK_RET(egl, EGLBoolean, eglBindAPI, (EGLenum api), (api), 0, PFNEGLBINDAPIPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglBindTexImage, (EGLDisplay dpy, EGLSurface surface, EGLint buffer), (dpy, surface, buffer), 1, PFNEGLBINDTEXIMAGEPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglChooseConfig, (EGLDisplay dpy, const EGLint * attrib_list, EGLConfig * configs, EGLint config_size, EGLint * num_config), (dpy, attrib_list, configs, config_size, num_config), 2, PFNEGLCHOOSECONFIGPROC)
GEN_THUNK_RET(egl, EGLint, eglClientWaitSync, (EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout), (dpy, sync, flags, timeout), 3, PFNEGLCLIENTWAITSYNCPROC)
GEN_THUNK_RET(egl, EGLint, eglClientWaitSyncKHR, (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout), (dpy, sync, flags, timeout), 4, PFNEGLCLIENTWAITSYNCKHRPROC)
GEN_THUNK_RET(egl, EGLint, eglClientWaitSyncNV, (EGLSyncNV sync, EGLint flags, EGLTimeNV timeout), (sync, flags, timeout), 5, PFNEGLCLIENTWAITSYNCNVPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglCopyBuffers, (EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target), (dpy, surface, target), 6, PFNEGLCOPYBUFFERSPROC)
GEN_THUNK_RET(egl, EGLContext, eglCreateContext, (EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint * attrib_list), (dpy, config, share_context, attrib_list), 7, PFNEGLCREATECONTEXTPROC)
GEN_THUNK_RET(egl, EGLImageKHR, eglCreateDRMImageMESA, (EGLDisplay dpy, const EGLint * attrib_list), (dpy, attrib_list), 8, PFNEGLCREATEDRMIMAGEMESAPROC)
GEN_THUNK_RET(egl, EGLSyncNV, eglCreateFenceSyncNV, (EGLDisplay dpy, EGLenum condition, const EGLint * attrib_list), (dpy, condition, attrib_list), 9, PFNEGLCREATEFENCESYNCNVPROC)
GEN_THUNK_RET(egl, EGLImage, eglCreateImage, (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLAttrib * attrib_list), (dpy, ctx, target, buffer, attrib_list), 10, PFNEGLCREATEIMAGEPROC)
GEN_THUNK_RET(egl, EGLImageKHR, eglCreateImageKHR, (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint * attrib_list), (dpy, ctx, target, buffer, attrib_list), 11, PFNEGLCREATEIMAGEKHRPROC)
GEN_THUNK_RET(egl, EGLClientBuffer, eglCreateNativeClientBufferANDROID, (const EGLint * attrib_list), (attrib_list), 12, PFNEGLCREATENATIVECLIENTBUFFERANDROIDPROC)
GEN_THUNK_RET(egl, EGLSurface, eglCreatePbufferFromClientBuffer, (EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint * attrib_list), (dpy, buftype, buffer, config, attrib_list), 13, PFNEGLCREATEPBUFFERFROMCLIENTBUFFERPROC)
GEN_THUNK_RET(egl, EGLSurface, eglCreatePbufferSurface, (EGLDisplay dpy, EGLConfig config, const EGLint * attrib_list), (dpy, config, attrib_list), 14, PFNEGLCREATEPBUFFERSURFACEPROC)
GEN_THUNK_RET(egl, EGLSurface, eglCreatePixmapSurface, (EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint * attrib_list), (dpy, config, pixmap, attrib_list), 15, PFNEGLCREATEPIXMAPSURFACEPROC)
GEN_THUNK_RET(egl, EGLSurface, eglCreatePixmapSurfaceHI, (EGLDisplay dpy, EGLConfig config, struct EGLClientPixmapHI * pixmap), (dpy, config, pixmap), 16, PFNEGLCREATEPIXMAPSURFACEHIPROC)
GEN_THUNK_RET(egl, EGLSurface, eglCreatePlatformPixmapSurface, (EGLDisplay dpy, EGLConfig config, void * native_pixmap, const EGLAttrib * attrib_list), (dpy, config, native_pixmap, attrib_list), 17, PFNEGLCREATEPLATFORMPIXMAPSURFACEPROC)
GEN_THUNK_RET(egl, EGLSurface, eglCreatePlatformPixmapSurfaceEXT, (EGLDisplay dpy, EGLConfig config, void * native_pixmap, const EGLint * attrib_list), (dpy, config, native_pixmap, attrib_list), 18, PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC)
GEN_THUNK_RET(egl, EGLSurface, eglCreatePlatformWindowSurface, (EGLDisplay dpy, EGLConfig config, void * native_window, const EGLAttrib * attrib_list), (dpy, config, native_window, attrib_list), 19, PFNEGLCREATEPLATFORMWINDOWSURFACEPROC)
GEN_THUNK_RET(egl, EGLSurface, eglCreatePlatformWindowSurfaceEXT, (EGLDisplay dpy, EGLConfig config, void * native_window, const EGLint * attrib_list), (dpy, config, native_window, attrib_list), 20, PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC)
GEN_THUNK_RET(egl, EGLStreamKHR, eglCreateStreamFromFileDescriptorKHR, (EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor), (dpy, file_descriptor), 21, PFNEGLCREATESTREAMFROMFILEDESCRIPTORKHRPROC)
GEN_THUNK_RET(egl, EGLStreamKHR, eglCreateStreamKHR, (EGLDisplay dpy, const EGLint * attrib_list), (dpy, attrib_list), 22, PFNEGLCREATESTREAMKHRPROC)
GEN_THUNK_RET(egl, EGLSurface, eglCreateStreamProducerSurfaceKHR, (EGLDisplay dpy, EGLConfig config, EGLStreamKHR stream, const EGLint * attrib_list), (dpy, config, stream, attrib_list), 23, PFNEGLCREATESTREAMPRODUCERSURFACEKHRPROC)
GEN_THUNK_RET(egl, EGLSyncKHR, eglCreateStreamSyncNV, (EGLDisplay dpy, EGLStreamKHR stream, EGLenum type, const EGLint * attrib_list), (dpy, stream, type, attrib_list), 24, PFNEGLCREATESTREAMSYNCNVPROC)
GEN_THUNK_RET(egl, EGLSync, eglCreateSync, (EGLDisplay dpy, EGLenum type, const EGLAttrib * attrib_list), (dpy, type, attrib_list), 25, PFNEGLCREATESYNCPROC)
GEN_THUNK_RET(egl, EGLSyncKHR, eglCreateSync64KHR, (EGLDisplay dpy, EGLenum type, const EGLAttribKHR * attrib_list), (dpy, type, attrib_list), 26, PFNEGLCREATESYNC64KHRPROC)
GEN_THUNK_RET(egl, EGLSyncKHR, eglCreateSyncKHR, (EGLDisplay dpy, EGLenum type, const EGLint * attrib_list), (dpy, type, attrib_list), 27, PFNEGLCREATESYNCKHRPROC)
GEN_THUNK_RET(egl, EGLSurface, eglCreateWindowSurface, (EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint * attrib_list), (dpy, config, win, attrib_list), 28, PFNEGLCREATEWINDOWSURFACEPROC)
GEN_THUNK_RET(egl, EGLint, eglDebugMessageControlKHR, (EGLDEBUGPROCKHR callback, const EGLAttrib * attrib_list), (callback, attrib_list), 29, PFNEGLDEBUGMESSAGECONTROLKHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglDestroyContext, (EGLDisplay dpy, EGLContext ctx), (dpy, ctx), 30, PFNEGLDESTROYCONTEXTPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglDestroyImage, (EGLDisplay dpy, EGLImage image), (dpy, image), 31, PFNEGLDESTROYIMAGEPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglDestroyImageKHR, (EGLDisplay dpy, EGLImageKHR image), (dpy, image), 32, PFNEGLDESTROYIMAGEKHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglDestroyStreamKHR, (EGLDisplay dpy, EGLStreamKHR stream), (dpy, stream), 33, PFNEGLDESTROYSTREAMKHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglDestroySurface, (EGLDisplay dpy, EGLSurface surface), (dpy, surface), 34, PFNEGLDESTROYSURFACEPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglDestroySync, (EGLDisplay dpy, EGLSync sync), (dpy, sync), 35, PFNEGLDESTROYSYNCPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglDestroySyncKHR, (EGLDisplay dpy, EGLSyncKHR sync), (dpy, sync), 36, PFNEGLDESTROYSYNCKHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglDestroySyncNV, (EGLSyncNV sync), (sync), 37, PFNEGLDESTROYSYNCNVPROC)
GEN_THUNK_RET(egl, EGLint, eglDupNativeFenceFDANDROID, (EGLDisplay dpy, EGLSyncKHR sync), (dpy, sync), 38, PFNEGLDUPNATIVEFENCEFDANDROIDPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglExportDMABUFImageMESA, (EGLDisplay dpy, EGLImageKHR image, int * fds, EGLint * strides, EGLint * offsets), (dpy, image, fds, strides, offsets), 39, PFNEGLEXPORTDMABUFIMAGEMESAPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglExportDMABUFImageQueryMESA, (EGLDisplay dpy, EGLImageKHR image, int * fourcc, int * num_planes, EGLuint64KHR * modifiers), (dpy, image, fourcc, num_planes, modifiers), 40, PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglExportDRMImageMESA, (EGLDisplay dpy, EGLImageKHR image, EGLint * name, EGLint * handle, EGLint * stride), (dpy, image, name, handle, stride), 41, PFNEGLEXPORTDRMIMAGEMESAPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglFenceNV, (EGLSyncNV sync), (sync), 42, PFNEGLFENCENVPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglGetConfigAttrib, (EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint * value), (dpy, config, attribute, value), 43, PFNEGLGETCONFIGATTRIBPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglGetConfigs, (EGLDisplay dpy, EGLConfig * configs, EGLint config_size, EGLint * num_config), (dpy, configs, config_size, num_config), 44, PFNEGLGETCONFIGSPROC)
GEN_THUNK_RET(egl, EGLContext, eglGetCurrentContext, (void), (), 45, PFNEGLGETCURRENTCONTEXTPROC)
GEN_THUNK_RET(egl, EGLDisplay, eglGetCurrentDisplay, (void), (), 46, PFNEGLGETCURRENTDISPLAYPROC)
GEN_THUNK_RET(egl, EGLSurface, eglGetCurrentSurface, (EGLint readdraw), (readdraw), 47, PFNEGLGETCURRENTSURFACEPROC)
GEN_THUNK_RET(egl, EGLDisplay, eglGetDisplay, (EGLNativeDisplayType display_id), (display_id), 48, PFNEGLGETDISPLAYPROC)
GEN_THUNK_RET(egl, EGLint, eglGetError, (void), (), 49, PFNEGLGETERRORPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglGetOutputLayersEXT, (EGLDisplay dpy, const EGLAttrib * attrib_list, EGLOutputLayerEXT * layers, EGLint max_layers, EGLint * num_layers), (dpy, attrib_list, layers, max_layers, num_layers), 50, PFNEGLGETOUTPUTLAYERSEXTPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglGetOutputPortsEXT, (EGLDisplay dpy, const EGLAttrib * attrib_list, EGLOutputPortEXT * ports, EGLint max_ports, EGLint * num_ports), (dpy, attrib_list, ports, max_ports, num_ports), 51, PFNEGLGETOUTPUTPORTSEXTPROC)
GEN_THUNK_RET(egl, EGLDisplay, eglGetPlatformDisplay, (EGLenum platform, void * native_display, const EGLAttrib * attrib_list), (platform, native_display, attrib_list), 52, PFNEGLGETPLATFORMDISPLAYPROC)
GEN_THUNK_RET(egl, EGLDisplay, eglGetPlatformDisplayEXT, (EGLenum platform, void * native_display, const EGLint * attrib_list), (platform, native_display, attrib_list), 53, PFNEGLGETPLATFORMDISPLAYEXTPROC)
GEN_THUNK_RET(egl, __eglMustCastToProperFunctionPointerType, eglGetProcAddress, (const char * procname), (procname), 54, PFNEGLGETPROCADDRESSPROC)
GEN_THUNK_RET(egl, EGLNativeFileDescriptorKHR, eglGetStreamFileDescriptorKHR, (EGLDisplay dpy, EGLStreamKHR stream), (dpy, stream), 55, PFNEGLGETSTREAMFILEDESCRIPTORKHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglGetSyncAttrib, (EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib * value), (dpy, sync, attribute, value), 56, PFNEGLGETSYNCATTRIBPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglGetSyncAttribKHR, (EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint * value), (dpy, sync, attribute, value), 57, PFNEGLGETSYNCATTRIBKHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglGetSyncAttribNV, (EGLSyncNV sync, EGLint attribute, EGLint * value), (sync, attribute, value), 58, PFNEGLGETSYNCATTRIBNVPROC)
GEN_THUNK_RET(egl, EGLuint64NV, eglGetSystemTimeFrequencyNV, (void), (), 59, PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC)
GEN_THUNK_RET(egl, EGLuint64NV, eglGetSystemTimeNV, (void), (), 60, PFNEGLGETSYSTEMTIMENVPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglInitialize, (EGLDisplay dpy, EGLint * major, EGLint * minor), (dpy, major, minor), 61, PFNEGLINITIALIZEPROC)
GEN_THUNK_RET(egl, EGLint, eglLabelObjectKHR, (EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label), (display, objectType, object, label), 62, PFNEGLLABELOBJECTKHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglLockSurfaceKHR, (EGLDisplay dpy, EGLSurface surface, const EGLint * attrib_list), (dpy, surface, attrib_list), 63, PFNEGLLOCKSURFACEKHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglMakeCurrent, (EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx), (dpy, draw, read, ctx), 64, PFNEGLMAKECURRENTPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglOutputLayerAttribEXT, (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib value), (dpy, layer, attribute, value), 65, PFNEGLOUTPUTLAYERATTRIBEXTPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglOutputPortAttribEXT, (EGLDisplay dpy, EGLOutputPortEXT port, EGLint attribute, EGLAttrib value), (dpy, port, attribute, value), 66, PFNEGLOUTPUTPORTATTRIBEXTPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglPostSubBufferNV, (EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint width, EGLint height), (dpy, surface, x, y, width, height), 67, PFNEGLPOSTSUBBUFFERNVPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglPresentationTimeANDROID, (EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID time), (dpy, surface, time), 68, PFNEGLPRESENTATIONTIMEANDROIDPROC)
GEN_THUNK_RET(egl, EGLenum, eglQueryAPI, (void), (), 69, PFNEGLQUERYAPIPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglQueryContext, (EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint * value), (dpy, ctx, attribute, value), 70, PFNEGLQUERYCONTEXTPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglQueryDebugKHR, (EGLint attribute, EGLAttrib * value), (attribute, value), 71, PFNEGLQUERYDEBUGKHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglQueryDeviceAttribEXT, (EGLDeviceEXT device, EGLint attribute, EGLAttrib * value), (device, attribute, value), 72, PFNEGLQUERYDEVICEATTRIBEXTPROC)
GEN_THUNK_RET(egl, const char *, eglQueryDeviceStringEXT, (EGLDeviceEXT device, EGLint name), (device, name), 73, PFNEGLQUERYDEVICESTRINGEXTPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglQueryDevicesEXT, (EGLint max_devices, EGLDeviceEXT * devices, EGLint * num_devices), (max_devices, devices, num_devices), 74, PFNEGLQUERYDEVICESEXTPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglQueryDisplayAttribEXT, (EGLDisplay dpy, EGLint attribute, EGLAttrib * value), (dpy, attribute, value), 75, PFNEGLQUERYDISPLAYATTRIBEXTPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglQueryDisplayAttribNV, (EGLDisplay dpy, EGLint attribute, EGLAttrib * value), (dpy, attribute, value), 76, PFNEGLQUERYDISPLAYATTRIBNVPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglQueryNativeDisplayNV, (EGLDisplay dpy, EGLNativeDisplayType * display_id), (dpy, display_id), 77, PFNEGLQUERYNATIVEDISPLAYNVPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglQueryNativePixmapNV, (EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType * pixmap), (dpy, surf, pixmap), 78, PFNEGLQUERYNATIVEPIXMAPNVPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglQueryNativeWindowNV, (EGLDisplay dpy, EGLSurface surf, EGLNativeWindowType * window), (dpy, surf, window), 79, PFNEGLQUERYNATIVEWINDOWNVPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglQueryOutputLayerAttribEXT, (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib * value), (dpy, layer, attribute, value), 80, PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC)
GEN_THUNK_RET(egl, const char *, eglQueryOutputLayerStringEXT, (EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name), (dpy, layer, name), 81, PFNEGLQUERYOUTPUTLAYERSTRINGEXTPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglQueryOutputPortAttribEXT, (EGLDisplay dpy, EGLOutputPortEXT port, EGLint attribute, EGLAttrib * value), (dpy, port, attribute, value), 82, PFNEGLQUERYOUTPUTPORTATTRIBEXTPROC)
GEN_THUNK_RET(egl, const char *, eglQueryOutputPortStringEXT, (EGLDisplay dpy, EGLOutputPortEXT port, EGLint name), (dpy, port, name), 83, PFNEGLQUERYOUTPUTPORTSTRINGEXTPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglQueryStreamKHR, (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLint * value), (dpy, stream, attribute, value), 84, PFNEGLQUERYSTREAMKHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglQueryStreamMetadataNV, (EGLDisplay dpy, EGLStreamKHR stream, EGLenum name, EGLint n, EGLint offset, EGLint size, void * data), (dpy, stream, name, n, offset, size, data), 85, PFNEGLQUERYSTREAMMETADATANVPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglQueryStreamTimeKHR, (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLTimeKHR * value), (dpy, stream, attribute, value), 86, PFNEGLQUERYSTREAMTIMEKHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglQueryStreamu64KHR, (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLuint64KHR * value), (dpy, stream, attribute, value), 87, PFNEGLQUERYSTREAMU64KHRPROC)
GEN_THUNK_RET(egl, const char *, eglQueryString, (EGLDisplay dpy, EGLint name), (dpy, name), 88, PFNEGLQUERYSTRINGPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglQuerySurface, (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint * value), (dpy, surface, attribute, value), 89, PFNEGLQUERYSURFACEPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglQuerySurface64KHR, (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR * value), (dpy, surface, attribute, value), 90, PFNEGLQUERYSURFACE64KHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglQuerySurfacePointerANGLE, (EGLDisplay dpy, EGLSurface surface, EGLint attribute, void ** value), (dpy, surface, attribute, value), 91, PFNEGLQUERYSURFACEPOINTERANGLEPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglReleaseTexImage, (EGLDisplay dpy, EGLSurface surface, EGLint buffer), (dpy, surface, buffer), 92, PFNEGLRELEASETEXIMAGEPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglReleaseThread, (void), (), 93, PFNEGLRELEASETHREADPROC)
GEN_THUNK(egl, eglSetBlobCacheFuncsANDROID, (EGLDisplay dpy, EGLSetBlobFuncANDROID set, EGLGetBlobFuncANDROID get), (dpy, set, get), 94, PFNEGLSETBLOBCACHEFUNCSANDROIDPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglSetDamageRegionKHR, (EGLDisplay dpy, EGLSurface surface, EGLint * rects, EGLint n_rects), (dpy, surface, rects, n_rects), 95, PFNEGLSETDAMAGEREGIONKHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglSetStreamMetadataNV, (EGLDisplay dpy, EGLStreamKHR stream, EGLint n, EGLint offset, EGLint size, const void * data), (dpy, stream, n, offset, size, data), 96, PFNEGLSETSTREAMMETADATANVPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglSignalSyncKHR, (EGLDisplay dpy, EGLSyncKHR sync, EGLenum mode), (dpy, sync, mode), 97, PFNEGLSIGNALSYNCKHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglSignalSyncNV, (EGLSyncNV sync, EGLenum mode), (sync, mode), 98, PFNEGLSIGNALSYNCNVPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglStreamAttribKHR, (EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLint value), (dpy, stream, attribute, value), 99, PFNEGLSTREAMATTRIBKHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglStreamConsumerAcquireKHR, (EGLDisplay dpy, EGLStreamKHR stream), (dpy, stream), 100, PFNEGLSTREAMCONSUMERACQUIREKHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglStreamConsumerGLTextureExternalAttribsNV, (EGLDisplay dpy, EGLStreamKHR stream, EGLAttrib * attrib_list), (dpy, stream, attrib_list), 101, PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALATTRIBSNVPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglStreamConsumerGLTextureExternalKHR, (EGLDisplay dpy, EGLStreamKHR stream), (dpy, stream), 102, PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglStreamConsumerOutputEXT, (EGLDisplay dpy, EGLStreamKHR stream, EGLOutputLayerEXT layer), (dpy, stream, layer), 103, PFNEGLSTREAMCONSUMEROUTPUTEXTPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglStreamConsumerReleaseKHR, (EGLDisplay dpy, EGLStreamKHR stream), (dpy, stream), 104, PFNEGLSTREAMCONSUMERRELEASEKHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglSurfaceAttrib, (EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value), (dpy, surface, attribute, value), 105, PFNEGLSURFACEATTRIBPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglSwapBuffers, (EGLDisplay dpy, EGLSurface surface), (dpy, surface), 106, PFNEGLSWAPBUFFERSPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglSwapBuffersRegion2NOK, (EGLDisplay dpy, EGLSurface surface, EGLint numRects, const EGLint * rects), (dpy, surface, numRects, rects), 107, PFNEGLSWAPBUFFERSREGION2NOKPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglSwapBuffersRegionNOK, (EGLDisplay dpy, EGLSurface surface, EGLint numRects, const EGLint * rects), (dpy, surface, numRects, rects), 108, PFNEGLSWAPBUFFERSREGIONNOKPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglSwapBuffersWithDamageEXT, (EGLDisplay dpy, EGLSurface surface, EGLint * rects, EGLint n_rects), (dpy, surface, rects, n_rects), 109, PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglSwapBuffersWithDamageKHR, (EGLDisplay dpy, EGLSurface surface, EGLint * rects, EGLint n_rects), (dpy, surface, rects, n_rects), 110, PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglSwapInterval, (EGLDisplay dpy, EGLint interval), (dpy, interval), 111, PFNEGLSWAPINTERVALPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglTerminate, (EGLDisplay dpy), (dpy), 112, PFNEGLTERMINATEPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglUnlockSurfaceKHR, (EGLDisplay dpy, EGLSurface surface), (dpy, surface), 113, PFNEGLUNLOCKSURFACEKHRPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglWaitClient, (void), (), 114, PFNEGLWAITCLIENTPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglWaitGL, (void), (), 115, PFNEGLWAITGLPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglWaitNative, (EGLint engine), (engine), 116, PFNEGLWAITNATIVEPROC)
GEN_THUNK_RET(egl, EGLBoolean, eglWaitSync, (EGLDisplay dpy, EGLSync sync, EGLint flags), (dpy, sync, flags), 117, PFNEGLWAITSYNCPROC)
GEN_THUNK_RET(egl, EGLint, eglWaitSyncKHR, (EGLDisplay dpy, EGLSyncKHR sync, EGLint flags), (dpy, sync, flags), 118, PFNEGLWAITSYNCKHRPROC)

#endif /* PLATFORM_HAS_EGL */

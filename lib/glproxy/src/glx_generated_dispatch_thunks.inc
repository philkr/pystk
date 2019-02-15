/* GL dispatch code.
 * This is code-generated from the GL API XML files from Khronos.
 */
#include "dispatch_common.h"
#if PLATFORM_HAS_GLX

#define glx_extensions_count 62

static const char glx_extension_enum_strings[] =
    "GLX_3DFX_multisample\0"
    "GLX_AMD_gpu_association\0"
    "GLX_ARB_context_flush_control\0"
    "GLX_ARB_create_context\0"
    "GLX_ARB_create_context_profile\0"
    "GLX_ARB_create_context_robustness\0"
    "GLX_ARB_fbconfig_float\0"
    "GLX_ARB_framebuffer_sRGB\0"
    "GLX_ARB_get_proc_address\0"
    "GLX_ARB_multisample\0"
    "GLX_ARB_robustness_application_isolation\0"
    "GLX_ARB_robustness_share_group_isolation\0"
    "GLX_ARB_vertex_buffer_object\0"
    "GLX_EXT_buffer_age\0"
    "GLX_EXT_create_context_es2_profile\0"
    "GLX_EXT_create_context_es_profile\0"
    "GLX_EXT_fbconfig_packed_float\0"
    "GLX_EXT_framebuffer_sRGB\0"
    "GLX_EXT_import_context\0"
    "GLX_EXT_libglvnd\0"
    "GLX_EXT_stereo_tree\0"
    "GLX_EXT_swap_control\0"
    "GLX_EXT_swap_control_tear\0"
    "GLX_EXT_texture_from_pixmap\0"
    "GLX_EXT_visual_info\0"
    "GLX_EXT_visual_rating\0"
    "GLX_INTEL_swap_event\0"
    "GLX_MESA_agp_offset\0"
    "GLX_MESA_copy_sub_buffer\0"
    "GLX_MESA_pixmap_colormap\0"
    "GLX_MESA_query_renderer\0"
    "GLX_MESA_release_buffers\0"
    "GLX_MESA_set_3dfx_mode\0"
    "GLX_NV_copy_buffer\0"
    "GLX_NV_copy_image\0"
    "GLX_NV_delay_before_swap\0"
    "GLX_NV_float_buffer\0"
    "GLX_NV_multisample_coverage\0"
    "GLX_NV_present_video\0"
    "GLX_NV_robustness_video_memory_purge\0"
    "GLX_NV_swap_group\0"
    "GLX_NV_video_capture\0"
    "GLX_NV_video_out\0"
    "GLX_OML_swap_method\0"
    "GLX_OML_sync_control\0"
    "GLX_SGIS_blended_overlay\0"
    "GLX_SGIS_multisample\0"
    "GLX_SGIS_shared_multisample\0"
    "GLX_SGIX_dmbuffer\0"
    "GLX_SGIX_fbconfig\0"
    "GLX_SGIX_hyperpipe\0"
    "GLX_SGIX_pbuffer\0"
    "GLX_SGIX_swap_barrier\0"
    "GLX_SGIX_swap_group\0"
    "GLX_SGIX_video_resize\0"
    "GLX_SGIX_video_source\0"
    "GLX_SGIX_visual_select_group\0"
    "GLX_SGI_cushion\0"
    "GLX_SGI_make_current_read\0"
    "GLX_SGI_swap_control\0"
    "GLX_SGI_video_sync\0"
    "GLX_SUN_get_transparent_index\0"
;
static const khronos_uint16_t glx_extension_offsets[] = {
    0,
    21,
    45,
    75,
    98,
    129,
    163,
    186,
    211,
    236,
    256,
    297,
    338,
    367,
    386,
    421,
    455,
    485,
    510,
    533,
    550,
    570,
    591,
    617,
    645,
    665,
    687,
    708,
    728,
    753,
    778,
    802,
    827,
    850,
    869,
    887,
    912,
    932,
    960,
    981,
    1018,
    1036,
    1057,
    1074,
    1094,
    1115,
    1140,
    1161,
    1189,
    1207,
    1225,
    1244,
    1261,
    1283,
    1303,
    1325,
    1347,
    1376,
    1392,
    1418,
    1439,
    1458,
    1488
};

static const khronos_uint8_t glx_entrypoint_strings[] = {
    103, 108, 88, 66, 105, 110, 100, 67, 104, 97, 110, 110, 101, 108, 84, 111, 87, 105, 110, 100, 111, 119, 83, 71, 73, 88, 0, /*glXBindChannelToWindowSGIX*/
    103, 108, 88, 66, 105, 110, 100, 72, 121, 112, 101, 114, 112, 105, 112, 101, 83, 71, 73, 88, 0, /*glXBindHyperpipeSGIX*/
    103, 108, 88, 66, 105, 110, 100, 83, 119, 97, 112, 66, 97, 114, 114, 105, 101, 114, 78, 86, 0, /*glXBindSwapBarrierNV*/
    103, 108, 88, 66, 105, 110, 100, 83, 119, 97, 112, 66, 97, 114, 114, 105, 101, 114, 83, 71, 73, 88, 0, /*glXBindSwapBarrierSGIX*/
    103, 108, 88, 66, 105, 110, 100, 84, 101, 120, 73, 109, 97, 103, 101, 69, 88, 84, 0, /*glXBindTexImageEXT*/
    103, 108, 88, 66, 105, 110, 100, 86, 105, 100, 101, 111, 67, 97, 112, 116, 117, 114, 101, 68, 101, 118, 105, 99, 101, 78, 86, 0, /*glXBindVideoCaptureDeviceNV*/
    103, 108, 88, 66, 105, 110, 100, 86, 105, 100, 101, 111, 68, 101, 118, 105, 99, 101, 78, 86, 0, /*glXBindVideoDeviceNV*/
    103, 108, 88, 66, 105, 110, 100, 86, 105, 100, 101, 111, 73, 109, 97, 103, 101, 78, 86, 0, /*glXBindVideoImageNV*/
    103, 108, 88, 66, 108, 105, 116, 67, 111, 110, 116, 101, 120, 116, 70, 114, 97, 109, 101, 98, 117, 102, 102, 101, 114, 65, 77, 68, 0, /*glXBlitContextFramebufferAMD*/
    103, 108, 88, 67, 104, 97, 110, 110, 101, 108, 82, 101, 99, 116, 83, 71, 73, 88, 0, /*glXChannelRectSGIX*/
    103, 108, 88, 67, 104, 97, 110, 110, 101, 108, 82, 101, 99, 116, 83, 121, 110, 99, 83, 71, 73, 88, 0, /*glXChannelRectSyncSGIX*/
    103, 108, 88, 67, 104, 111, 111, 115, 101, 70, 66, 67, 111, 110, 102, 105, 103, 0, /*glXChooseFBConfig*/
    103, 108, 88, 67, 104, 111, 111, 115, 101, 70, 66, 67, 111, 110, 102, 105, 103, 83, 71, 73, 88, 0, /*glXChooseFBConfigSGIX*/
    103, 108, 88, 67, 104, 111, 111, 115, 101, 86, 105, 115, 117, 97, 108, 0, /*glXChooseVisual*/
    103, 108, 88, 67, 111, 112, 121, 66, 117, 102, 102, 101, 114, 83, 117, 98, 68, 97, 116, 97, 78, 86, 0, /*glXCopyBufferSubDataNV*/
    103, 108, 88, 67, 111, 112, 121, 67, 111, 110, 116, 101, 120, 116, 0, /*glXCopyContext*/
    103, 108, 88, 67, 111, 112, 121, 73, 109, 97, 103, 101, 83, 117, 98, 68, 97, 116, 97, 78, 86, 0, /*glXCopyImageSubDataNV*/
    103, 108, 88, 67, 111, 112, 121, 83, 117, 98, 66, 117, 102, 102, 101, 114, 77, 69, 83, 65, 0, /*glXCopySubBufferMESA*/
    103, 108, 88, 67, 114, 101, 97, 116, 101, 65, 115, 115, 111, 99, 105, 97, 116, 101, 100, 67, 111, 110, 116, 101, 120, 116, 65, 77, 68, 0, /*glXCreateAssociatedContextAMD*/
    103, 108, 88, 67, 114, 101, 97, 116, 101, 65, 115, 115, 111, 99, 105, 97, 116, 101, 100, 67, 111, 110, 116, 101, 120, 116, 65, 116, 116, 114, 105, 98, 115, 65, 77, 68, 0, /*glXCreateAssociatedContextAttribsAMD*/
    103, 108, 88, 67, 114, 101, 97, 116, 101, 67, 111, 110, 116, 101, 120, 116, 0, /*glXCreateContext*/
    103, 108, 88, 67, 114, 101, 97, 116, 101, 67, 111, 110, 116, 101, 120, 116, 65, 116, 116, 114, 105, 98, 115, 65, 82, 66, 0, /*glXCreateContextAttribsARB*/
    103, 108, 88, 67, 114, 101, 97, 116, 101, 67, 111, 110, 116, 101, 120, 116, 87, 105, 116, 104, 67, 111, 110, 102, 105, 103, 83, 71, 73, 88, 0, /*glXCreateContextWithConfigSGIX*/
    103, 108, 88, 67, 114, 101, 97, 116, 101, 71, 76, 88, 80, 98, 117, 102, 102, 101, 114, 83, 71, 73, 88, 0, /*glXCreateGLXPbufferSGIX*/
    103, 108, 88, 67, 114, 101, 97, 116, 101, 71, 76, 88, 80, 105, 120, 109, 97, 112, 0, /*glXCreateGLXPixmap*/
    103, 108, 88, 67, 114, 101, 97, 116, 101, 71, 76, 88, 80, 105, 120, 109, 97, 112, 77, 69, 83, 65, 0, /*glXCreateGLXPixmapMESA*/
    103, 108, 88, 67, 114, 101, 97, 116, 101, 71, 76, 88, 80, 105, 120, 109, 97, 112, 87, 105, 116, 104, 67, 111, 110, 102, 105, 103, 83, 71, 73, 88, 0, /*glXCreateGLXPixmapWithConfigSGIX*/
    103, 108, 88, 67, 114, 101, 97, 116, 101, 78, 101, 119, 67, 111, 110, 116, 101, 120, 116, 0, /*glXCreateNewContext*/
    103, 108, 88, 67, 114, 101, 97, 116, 101, 80, 98, 117, 102, 102, 101, 114, 0, /*glXCreatePbuffer*/
    103, 108, 88, 67, 114, 101, 97, 116, 101, 80, 105, 120, 109, 97, 112, 0, /*glXCreatePixmap*/
    103, 108, 88, 67, 114, 101, 97, 116, 101, 87, 105, 110, 100, 111, 119, 0, /*glXCreateWindow*/
    103, 108, 88, 67, 117, 115, 104, 105, 111, 110, 83, 71, 73, 0, /*glXCushionSGI*/
    103, 108, 88, 68, 101, 108, 97, 121, 66, 101, 102, 111, 114, 101, 83, 119, 97, 112, 78, 86, 0, /*glXDelayBeforeSwapNV*/
    103, 108, 88, 68, 101, 108, 101, 116, 101, 65, 115, 115, 111, 99, 105, 97, 116, 101, 100, 67, 111, 110, 116, 101, 120, 116, 65, 77, 68, 0, /*glXDeleteAssociatedContextAMD*/
    103, 108, 88, 68, 101, 115, 116, 114, 111, 121, 67, 111, 110, 116, 101, 120, 116, 0, /*glXDestroyContext*/
    103, 108, 88, 68, 101, 115, 116, 114, 111, 121, 71, 76, 88, 80, 98, 117, 102, 102, 101, 114, 83, 71, 73, 88, 0, /*glXDestroyGLXPbufferSGIX*/
    103, 108, 88, 68, 101, 115, 116, 114, 111, 121, 71, 76, 88, 80, 105, 120, 109, 97, 112, 0, /*glXDestroyGLXPixmap*/
    103, 108, 88, 68, 101, 115, 116, 114, 111, 121, 71, 76, 88, 86, 105, 100, 101, 111, 83, 111, 117, 114, 99, 101, 83, 71, 73, 88, 0, /*glXDestroyGLXVideoSourceSGIX*/
    103, 108, 88, 68, 101, 115, 116, 114, 111, 121, 72, 121, 112, 101, 114, 112, 105, 112, 101, 67, 111, 110, 102, 105, 103, 83, 71, 73, 88, 0, /*glXDestroyHyperpipeConfigSGIX*/
    103, 108, 88, 68, 101, 115, 116, 114, 111, 121, 80, 98, 117, 102, 102, 101, 114, 0, /*glXDestroyPbuffer*/
    103, 108, 88, 68, 101, 115, 116, 114, 111, 121, 80, 105, 120, 109, 97, 112, 0, /*glXDestroyPixmap*/
    103, 108, 88, 68, 101, 115, 116, 114, 111, 121, 87, 105, 110, 100, 111, 119, 0, /*glXDestroyWindow*/
    103, 108, 88, 69, 110, 117, 109, 101, 114, 97, 116, 101, 86, 105, 100, 101, 111, 67, 97, 112, 116, 117, 114, 101, 68, 101, 118, 105, 99, 101, 115, 78, 86, 0, /*glXEnumerateVideoCaptureDevicesNV*/
    103, 108, 88, 69, 110, 117, 109, 101, 114, 97, 116, 101, 86, 105, 100, 101, 111, 68, 101, 118, 105, 99, 101, 115, 78, 86, 0, /*glXEnumerateVideoDevicesNV*/
    103, 108, 88, 70, 114, 101, 101, 67, 111, 110, 116, 101, 120, 116, 69, 88, 84, 0, /*glXFreeContextEXT*/
    103, 108, 88, 71, 101, 116, 65, 71, 80, 79, 102, 102, 115, 101, 116, 77, 69, 83, 65, 0, /*glXGetAGPOffsetMESA*/
    103, 108, 88, 71, 101, 116, 67, 108, 105, 101, 110, 116, 83, 116, 114, 105, 110, 103, 0, /*glXGetClientString*/
    103, 108, 88, 71, 101, 116, 67, 111, 110, 102, 105, 103, 0, /*glXGetConfig*/
    103, 108, 88, 71, 101, 116, 67, 111, 110, 116, 101, 120, 116, 71, 80, 85, 73, 68, 65, 77, 68, 0, /*glXGetContextGPUIDAMD*/
    103, 108, 88, 71, 101, 116, 67, 111, 110, 116, 101, 120, 116, 73, 68, 69, 88, 84, 0, /*glXGetContextIDEXT*/
    103, 108, 88, 71, 101, 116, 67, 117, 114, 114, 101, 110, 116, 65, 115, 115, 111, 99, 105, 97, 116, 101, 100, 67, 111, 110, 116, 101, 120, 116, 65, 77, 68, 0, /*glXGetCurrentAssociatedContextAMD*/
    103, 108, 88, 71, 101, 116, 67, 117, 114, 114, 101, 110, 116, 67, 111, 110, 116, 101, 120, 116, 0, /*glXGetCurrentContext*/
    103, 108, 88, 71, 101, 116, 67, 117, 114, 114, 101, 110, 116, 68, 105, 115, 112, 108, 97, 121, 0, /*glXGetCurrentDisplay*/
    103, 108, 88, 71, 101, 116, 67, 117, 114, 114, 101, 110, 116, 68, 105, 115, 112, 108, 97, 121, 69, 88, 84, 0, /*glXGetCurrentDisplayEXT*/
    103, 108, 88, 71, 101, 116, 67, 117, 114, 114, 101, 110, 116, 68, 114, 97, 119, 97, 98, 108, 101, 0, /*glXGetCurrentDrawable*/
    103, 108, 88, 71, 101, 116, 67, 117, 114, 114, 101, 110, 116, 82, 101, 97, 100, 68, 114, 97, 119, 97, 98, 108, 101, 0, /*glXGetCurrentReadDrawable*/
    103, 108, 88, 71, 101, 116, 67, 117, 114, 114, 101, 110, 116, 82, 101, 97, 100, 68, 114, 97, 119, 97, 98, 108, 101, 83, 71, 73, 0, /*glXGetCurrentReadDrawableSGI*/
    103, 108, 88, 71, 101, 116, 70, 66, 67, 111, 110, 102, 105, 103, 65, 116, 116, 114, 105, 98, 0, /*glXGetFBConfigAttrib*/
    103, 108, 88, 71, 101, 116, 70, 66, 67, 111, 110, 102, 105, 103, 65, 116, 116, 114, 105, 98, 83, 71, 73, 88, 0, /*glXGetFBConfigAttribSGIX*/
    103, 108, 88, 71, 101, 116, 70, 66, 67, 111, 110, 102, 105, 103, 70, 114, 111, 109, 86, 105, 115, 117, 97, 108, 83, 71, 73, 88, 0, /*glXGetFBConfigFromVisualSGIX*/
    103, 108, 88, 71, 101, 116, 70, 66, 67, 111, 110, 102, 105, 103, 115, 0, /*glXGetFBConfigs*/
    103, 108, 88, 71, 101, 116, 71, 80, 85, 73, 68, 115, 65, 77, 68, 0, /*glXGetGPUIDsAMD*/
    103, 108, 88, 71, 101, 116, 71, 80, 85, 73, 110, 102, 111, 65, 77, 68, 0, /*glXGetGPUInfoAMD*/
    103, 108, 88, 71, 101, 116, 77, 115, 99, 82, 97, 116, 101, 79, 77, 76, 0, /*glXGetMscRateOML*/
    103, 108, 88, 71, 101, 116, 80, 114, 111, 99, 65, 100, 100, 114, 101, 115, 115, 0, /*glXGetProcAddress*/
    103, 108, 88, 71, 101, 116, 80, 114, 111, 99, 65, 100, 100, 114, 101, 115, 115, 65, 82, 66, 0, /*glXGetProcAddressARB*/
    103, 108, 88, 71, 101, 116, 83, 101, 108, 101, 99, 116, 101, 100, 69, 118, 101, 110, 116, 0, /*glXGetSelectedEvent*/
    103, 108, 88, 71, 101, 116, 83, 101, 108, 101, 99, 116, 101, 100, 69, 118, 101, 110, 116, 83, 71, 73, 88, 0, /*glXGetSelectedEventSGIX*/
    103, 108, 88, 71, 101, 116, 83, 121, 110, 99, 86, 97, 108, 117, 101, 115, 79, 77, 76, 0, /*glXGetSyncValuesOML*/
    103, 108, 88, 71, 101, 116, 84, 114, 97, 110, 115, 112, 97, 114, 101, 110, 116, 73, 110, 100, 101, 120, 83, 85, 78, 0, /*glXGetTransparentIndexSUN*/
    103, 108, 88, 71, 101, 116, 86, 105, 100, 101, 111, 68, 101, 118, 105, 99, 101, 78, 86, 0, /*glXGetVideoDeviceNV*/
    103, 108, 88, 71, 101, 116, 86, 105, 100, 101, 111, 73, 110, 102, 111, 78, 86, 0, /*glXGetVideoInfoNV*/
    103, 108, 88, 71, 101, 116, 86, 105, 100, 101, 111, 83, 121, 110, 99, 83, 71, 73, 0, /*glXGetVideoSyncSGI*/
    103, 108, 88, 71, 101, 116, 86, 105, 115, 117, 97, 108, 70, 114, 111, 109, 70, 66, 67, 111, 110, 102, 105, 103, 0, /*glXGetVisualFromFBConfig*/
    103, 108, 88, 71, 101, 116, 86, 105, 115, 117, 97, 108, 70, 114, 111, 109, 70, 66, 67, 111, 110, 102, 105, 103, 83, 71, 73, 88, 0, /*glXGetVisualFromFBConfigSGIX*/
    103, 108, 88, 72, 121, 112, 101, 114, 112, 105, 112, 101, 65, 116, 116, 114, 105, 98, 83, 71, 73, 88, 0, /*glXHyperpipeAttribSGIX*/
    103, 108, 88, 72, 121, 112, 101, 114, 112, 105, 112, 101, 67, 111, 110, 102, 105, 103, 83, 71, 73, 88, 0, /*glXHyperpipeConfigSGIX*/
    103, 108, 88, 73, 109, 112, 111, 114, 116, 67, 111, 110, 116, 101, 120, 116, 69, 88, 84, 0, /*glXImportContextEXT*/
    103, 108, 88, 73, 115, 68, 105, 114, 101, 99, 116, 0, /*glXIsDirect*/
    103, 108, 88, 74, 111, 105, 110, 83, 119, 97, 112, 71, 114, 111, 117, 112, 78, 86, 0, /*glXJoinSwapGroupNV*/
    103, 108, 88, 74, 111, 105, 110, 83, 119, 97, 112, 71, 114, 111, 117, 112, 83, 71, 73, 88, 0, /*glXJoinSwapGroupSGIX*/
    103, 108, 88, 76, 111, 99, 107, 86, 105, 100, 101, 111, 67, 97, 112, 116, 117, 114, 101, 68, 101, 118, 105, 99, 101, 78, 86, 0, /*glXLockVideoCaptureDeviceNV*/
    103, 108, 88, 77, 97, 107, 101, 65, 115, 115, 111, 99, 105, 97, 116, 101, 100, 67, 111, 110, 116, 101, 120, 116, 67, 117, 114, 114, 101, 110, 116, 65, 77, 68, 0, /*glXMakeAssociatedContextCurrentAMD*/
    103, 108, 88, 77, 97, 107, 101, 67, 111, 110, 116, 101, 120, 116, 67, 117, 114, 114, 101, 110, 116, 0, /*glXMakeContextCurrent*/
    103, 108, 88, 77, 97, 107, 101, 67, 117, 114, 114, 101, 110, 116, 0, /*glXMakeCurrent*/
    103, 108, 88, 77, 97, 107, 101, 67, 117, 114, 114, 101, 110, 116, 82, 101, 97, 100, 83, 71, 73, 0, /*glXMakeCurrentReadSGI*/
    103, 108, 88, 78, 97, 109, 101, 100, 67, 111, 112, 121, 66, 117, 102, 102, 101, 114, 83, 117, 98, 68, 97, 116, 97, 78, 86, 0, /*glXNamedCopyBufferSubDataNV*/
    103, 108, 88, 81, 117, 101, 114, 121, 67, 104, 97, 110, 110, 101, 108, 68, 101, 108, 116, 97, 115, 83, 71, 73, 88, 0, /*glXQueryChannelDeltasSGIX*/
    103, 108, 88, 81, 117, 101, 114, 121, 67, 104, 97, 110, 110, 101, 108, 82, 101, 99, 116, 83, 71, 73, 88, 0, /*glXQueryChannelRectSGIX*/
    103, 108, 88, 81, 117, 101, 114, 121, 67, 111, 110, 116, 101, 120, 116, 0, /*glXQueryContext*/
    103, 108, 88, 81, 117, 101, 114, 121, 67, 111, 110, 116, 101, 120, 116, 73, 110, 102, 111, 69, 88, 84, 0, /*glXQueryContextInfoEXT*/
    103, 108, 88, 81, 117, 101, 114, 121, 67, 117, 114, 114, 101, 110, 116, 82, 101, 110, 100, 101, 114, 101, 114, 73, 110, 116, 101, 103, 101, 114, 77, 69, 83, 65, 0, /*glXQueryCurrentRendererIntegerMESA*/
    103, 108, 88, 81, 117, 101, 114, 121, 67, 117, 114, 114, 101, 110, 116, 82, 101, 110, 100, 101, 114, 101, 114, 83, 116, 114, 105, 110, 103, 77, 69, 83, 65, 0, /*glXQueryCurrentRendererStringMESA*/
    103, 108, 88, 81, 117, 101, 114, 121, 68, 114, 97, 119, 97, 98, 108, 101, 0, /*glXQueryDrawable*/
    103, 108, 88, 81, 117, 101, 114, 121, 69, 120, 116, 101, 110, 115, 105, 111, 110, 0, /*glXQueryExtension*/
    103, 108, 88, 81, 117, 101, 114, 121, 69, 120, 116, 101, 110, 115, 105, 111, 110, 115, 83, 116, 114, 105, 110, 103, 0, /*glXQueryExtensionsString*/
    103, 108, 88, 81, 117, 101, 114, 121, 70, 114, 97, 109, 101, 67, 111, 117, 110, 116, 78, 86, 0, /*glXQueryFrameCountNV*/
    103, 108, 88, 81, 117, 101, 114, 121, 71, 76, 88, 80, 98, 117, 102, 102, 101, 114, 83, 71, 73, 88, 0, /*glXQueryGLXPbufferSGIX*/
    103, 108, 88, 81, 117, 101, 114, 121, 72, 121, 112, 101, 114, 112, 105, 112, 101, 65, 116, 116, 114, 105, 98, 83, 71, 73, 88, 0, /*glXQueryHyperpipeAttribSGIX*/
    103, 108, 88, 81, 117, 101, 114, 121, 72, 121, 112, 101, 114, 112, 105, 112, 101, 66, 101, 115, 116, 65, 116, 116, 114, 105, 98, 83, 71, 73, 88, 0, /*glXQueryHyperpipeBestAttribSGIX*/
    103, 108, 88, 81, 117, 101, 114, 121, 72, 121, 112, 101, 114, 112, 105, 112, 101, 67, 111, 110, 102, 105, 103, 83, 71, 73, 88, 0, /*glXQueryHyperpipeConfigSGIX*/
    103, 108, 88, 81, 117, 101, 114, 121, 72, 121, 112, 101, 114, 112, 105, 112, 101, 78, 101, 116, 119, 111, 114, 107, 83, 71, 73, 88, 0, /*glXQueryHyperpipeNetworkSGIX*/
    103, 108, 88, 81, 117, 101, 114, 121, 77, 97, 120, 83, 119, 97, 112, 66, 97, 114, 114, 105, 101, 114, 115, 83, 71, 73, 88, 0, /*glXQueryMaxSwapBarriersSGIX*/
    103, 108, 88, 81, 117, 101, 114, 121, 77, 97, 120, 83, 119, 97, 112, 71, 114, 111, 117, 112, 115, 78, 86, 0, /*glXQueryMaxSwapGroupsNV*/
    103, 108, 88, 81, 117, 101, 114, 121, 82, 101, 110, 100, 101, 114, 101, 114, 73, 110, 116, 101, 103, 101, 114, 77, 69, 83, 65, 0, /*glXQueryRendererIntegerMESA*/
    103, 108, 88, 81, 117, 101, 114, 121, 82, 101, 110, 100, 101, 114, 101, 114, 83, 116, 114, 105, 110, 103, 77, 69, 83, 65, 0, /*glXQueryRendererStringMESA*/
    103, 108, 88, 81, 117, 101, 114, 121, 83, 101, 114, 118, 101, 114, 83, 116, 114, 105, 110, 103, 0, /*glXQueryServerString*/
    103, 108, 88, 81, 117, 101, 114, 121, 83, 119, 97, 112, 71, 114, 111, 117, 112, 78, 86, 0, /*glXQuerySwapGroupNV*/
    103, 108, 88, 81, 117, 101, 114, 121, 86, 101, 114, 115, 105, 111, 110, 0, /*glXQueryVersion*/
    103, 108, 88, 81, 117, 101, 114, 121, 86, 105, 100, 101, 111, 67, 97, 112, 116, 117, 114, 101, 68, 101, 118, 105, 99, 101, 78, 86, 0, /*glXQueryVideoCaptureDeviceNV*/
    103, 108, 88, 82, 101, 108, 101, 97, 115, 101, 66, 117, 102, 102, 101, 114, 115, 77, 69, 83, 65, 0, /*glXReleaseBuffersMESA*/
    103, 108, 88, 82, 101, 108, 101, 97, 115, 101, 84, 101, 120, 73, 109, 97, 103, 101, 69, 88, 84, 0, /*glXReleaseTexImageEXT*/
    103, 108, 88, 82, 101, 108, 101, 97, 115, 101, 86, 105, 100, 101, 111, 67, 97, 112, 116, 117, 114, 101, 68, 101, 118, 105, 99, 101, 78, 86, 0, /*glXReleaseVideoCaptureDeviceNV*/
    103, 108, 88, 82, 101, 108, 101, 97, 115, 101, 86, 105, 100, 101, 111, 68, 101, 118, 105, 99, 101, 78, 86, 0, /*glXReleaseVideoDeviceNV*/
    103, 108, 88, 82, 101, 108, 101, 97, 115, 101, 86, 105, 100, 101, 111, 73, 109, 97, 103, 101, 78, 86, 0, /*glXReleaseVideoImageNV*/
    103, 108, 88, 82, 101, 115, 101, 116, 70, 114, 97, 109, 101, 67, 111, 117, 110, 116, 78, 86, 0, /*glXResetFrameCountNV*/
    103, 108, 88, 83, 101, 108, 101, 99, 116, 69, 118, 101, 110, 116, 0, /*glXSelectEvent*/
    103, 108, 88, 83, 101, 108, 101, 99, 116, 69, 118, 101, 110, 116, 83, 71, 73, 88, 0, /*glXSelectEventSGIX*/
    103, 108, 88, 83, 101, 110, 100, 80, 98, 117, 102, 102, 101, 114, 84, 111, 86, 105, 100, 101, 111, 78, 86, 0, /*glXSendPbufferToVideoNV*/
    103, 108, 88, 83, 101, 116, 51, 68, 102, 120, 77, 111, 100, 101, 77, 69, 83, 65, 0, /*glXSet3DfxModeMESA*/
    103, 108, 88, 83, 119, 97, 112, 66, 117, 102, 102, 101, 114, 115, 0, /*glXSwapBuffers*/
    103, 108, 88, 83, 119, 97, 112, 66, 117, 102, 102, 101, 114, 115, 77, 115, 99, 79, 77, 76, 0, /*glXSwapBuffersMscOML*/
    103, 108, 88, 83, 119, 97, 112, 73, 110, 116, 101, 114, 118, 97, 108, 69, 88, 84, 0, /*glXSwapIntervalEXT*/
    103, 108, 88, 83, 119, 97, 112, 73, 110, 116, 101, 114, 118, 97, 108, 83, 71, 73, 0, /*glXSwapIntervalSGI*/
    103, 108, 88, 85, 115, 101, 88, 70, 111, 110, 116, 0, /*glXUseXFont*/
    103, 108, 88, 87, 97, 105, 116, 70, 111, 114, 77, 115, 99, 79, 77, 76, 0, /*glXWaitForMscOML*/
    103, 108, 88, 87, 97, 105, 116, 70, 111, 114, 83, 98, 99, 79, 77, 76, 0, /*glXWaitForSbcOML*/
    103, 108, 88, 87, 97, 105, 116, 71, 76, 0, /*glXWaitGL*/
    103, 108, 88, 87, 97, 105, 116, 86, 105, 100, 101, 111, 83, 121, 110, 99, 83, 71, 73, 0, /*glXWaitVideoSyncSGI*/
    103, 108, 88, 87, 97, 105, 116, 88, 0, /*glXWaitX*/
};

static const struct dispatch_resolve_info glx_resolve_info_table[] = {
    {DISPATCH_RESOLVE_EXTENSION, 0, 54 /* GLX_SGIX_video_resize */, 0}, /* glXBindChannelToWindowSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 1, 50 /* GLX_SGIX_hyperpipe */, 27}, /* glXBindHyperpipeSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 2, 40 /* GLX_NV_swap_group */, 48}, /* glXBindSwapBarrierNV */
    {DISPATCH_RESOLVE_EXTENSION, 3, 52 /* GLX_SGIX_swap_barrier */, 69}, /* glXBindSwapBarrierSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 4, 23 /* GLX_EXT_texture_from_pixmap */, 92}, /* glXBindTexImageEXT */
    {DISPATCH_RESOLVE_EXTENSION, 5, 41 /* GLX_NV_video_capture */, 111}, /* glXBindVideoCaptureDeviceNV */
    {DISPATCH_RESOLVE_EXTENSION, 6, 38 /* GLX_NV_present_video */, 139}, /* glXBindVideoDeviceNV */
    {DISPATCH_RESOLVE_EXTENSION, 7, 42 /* GLX_NV_video_out */, 160}, /* glXBindVideoImageNV */
    {DISPATCH_RESOLVE_EXTENSION, 8, 1 /* GLX_AMD_gpu_association */, 180}, /* glXBlitContextFramebufferAMD */
    {DISPATCH_RESOLVE_EXTENSION, 9, 54 /* GLX_SGIX_video_resize */, 209}, /* glXChannelRectSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 10, 54 /* GLX_SGIX_video_resize */, 228}, /* glXChannelRectSyncSGIX */
    {DISPATCH_RESOLVE_DIRECT, 11, GLX_1_3, 251}, /* glXChooseFBConfig */
    {DISPATCH_RESOLVE_EXTENSION, 12, 49 /* GLX_SGIX_fbconfig */, 269}, /* glXChooseFBConfigSGIX */
    {DISPATCH_RESOLVE_DIRECT, 13, GLX_1_0, 291}, /* glXChooseVisual */
    {DISPATCH_RESOLVE_EXTENSION, 14, 33 /* GLX_NV_copy_buffer */, 307}, /* glXCopyBufferSubDataNV */
    {DISPATCH_RESOLVE_DIRECT, 15, GLX_1_0, 330}, /* glXCopyContext */
    {DISPATCH_RESOLVE_EXTENSION, 16, 34 /* GLX_NV_copy_image */, 345}, /* glXCopyImageSubDataNV */
    {DISPATCH_RESOLVE_EXTENSION, 17, 28 /* GLX_MESA_copy_sub_buffer */, 367}, /* glXCopySubBufferMESA */
    {DISPATCH_RESOLVE_EXTENSION, 18, 1 /* GLX_AMD_gpu_association */, 388}, /* glXCreateAssociatedContextAMD */
    {DISPATCH_RESOLVE_EXTENSION, 19, 1 /* GLX_AMD_gpu_association */, 418}, /* glXCreateAssociatedContextAttribsAMD */
    {DISPATCH_RESOLVE_DIRECT, 20, GLX_1_0, 455}, /* glXCreateContext */
    {DISPATCH_RESOLVE_EXTENSION, 21, 3 /* GLX_ARB_create_context */, 472}, /* glXCreateContextAttribsARB */
    {DISPATCH_RESOLVE_EXTENSION, 22, 49 /* GLX_SGIX_fbconfig */, 499}, /* glXCreateContextWithConfigSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 23, 51 /* GLX_SGIX_pbuffer */, 530}, /* glXCreateGLXPbufferSGIX */
    {DISPATCH_RESOLVE_DIRECT, 24, GLX_1_0, 554}, /* glXCreateGLXPixmap */
    {DISPATCH_RESOLVE_EXTENSION, 25, 29 /* GLX_MESA_pixmap_colormap */, 573}, /* glXCreateGLXPixmapMESA */
    {DISPATCH_RESOLVE_EXTENSION, 26, 49 /* GLX_SGIX_fbconfig */, 596}, /* glXCreateGLXPixmapWithConfigSGIX */
    {DISPATCH_RESOLVE_DIRECT, 27, GLX_1_3, 629}, /* glXCreateNewContext */
    {DISPATCH_RESOLVE_DIRECT, 28, GLX_1_3, 649}, /* glXCreatePbuffer */
    {DISPATCH_RESOLVE_DIRECT, 29, GLX_1_3, 666}, /* glXCreatePixmap */
    {DISPATCH_RESOLVE_DIRECT, 30, GLX_1_3, 682}, /* glXCreateWindow */
    {DISPATCH_RESOLVE_EXTENSION, 31, 57 /* GLX_SGI_cushion */, 698}, /* glXCushionSGI */
    {DISPATCH_RESOLVE_EXTENSION, 32, 35 /* GLX_NV_delay_before_swap */, 712}, /* glXDelayBeforeSwapNV */
    {DISPATCH_RESOLVE_EXTENSION, 33, 1 /* GLX_AMD_gpu_association */, 733}, /* glXDeleteAssociatedContextAMD */
    {DISPATCH_RESOLVE_DIRECT, 34, GLX_1_0, 763}, /* glXDestroyContext */
    {DISPATCH_RESOLVE_EXTENSION, 35, 51 /* GLX_SGIX_pbuffer */, 781}, /* glXDestroyGLXPbufferSGIX */
    {DISPATCH_RESOLVE_DIRECT, 36, GLX_1_0, 806}, /* glXDestroyGLXPixmap */
    {DISPATCH_RESOLVE_EXTENSION, 37, 55 /* GLX_SGIX_video_source */, 826}, /* glXDestroyGLXVideoSourceSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 38, 50 /* GLX_SGIX_hyperpipe */, 855}, /* glXDestroyHyperpipeConfigSGIX */
    {DISPATCH_RESOLVE_DIRECT, 39, GLX_1_3, 885}, /* glXDestroyPbuffer */
    {DISPATCH_RESOLVE_DIRECT, 40, GLX_1_3, 903}, /* glXDestroyPixmap */
    {DISPATCH_RESOLVE_DIRECT, 41, GLX_1_3, 920}, /* glXDestroyWindow */
    {DISPATCH_RESOLVE_EXTENSION, 42, 41 /* GLX_NV_video_capture */, 937}, /* glXEnumerateVideoCaptureDevicesNV */
    {DISPATCH_RESOLVE_EXTENSION, 43, 38 /* GLX_NV_present_video */, 971}, /* glXEnumerateVideoDevicesNV */
    {DISPATCH_RESOLVE_EXTENSION, 44, 18 /* GLX_EXT_import_context */, 998}, /* glXFreeContextEXT */
    {DISPATCH_RESOLVE_EXTENSION, 45, 27 /* GLX_MESA_agp_offset */, 1016}, /* glXGetAGPOffsetMESA */
    {DISPATCH_RESOLVE_DIRECT, 46, GLX_1_1, 1036}, /* glXGetClientString */
    {DISPATCH_RESOLVE_DIRECT, 47, GLX_1_0, 1055}, /* glXGetConfig */
    {DISPATCH_RESOLVE_EXTENSION, 48, 1 /* GLX_AMD_gpu_association */, 1068}, /* glXGetContextGPUIDAMD */
    {DISPATCH_RESOLVE_EXTENSION, 49, 18 /* GLX_EXT_import_context */, 1090}, /* glXGetContextIDEXT */
    {DISPATCH_RESOLVE_EXTENSION, 50, 1 /* GLX_AMD_gpu_association */, 1109}, /* glXGetCurrentAssociatedContextAMD */
    {DISPATCH_RESOLVE_DIRECT, 51, GLX_1_0, 1143}, /* glXGetCurrentContext */
    {DISPATCH_RESOLVE_DIRECT, 52, GLX_1_2, 1164}, /* glXGetCurrentDisplay */
    {DISPATCH_RESOLVE_EXTENSION, 53, 18 /* GLX_EXT_import_context */, 1185}, /* glXGetCurrentDisplayEXT */
    {DISPATCH_RESOLVE_DIRECT, 54, GLX_1_0, 1209}, /* glXGetCurrentDrawable */
    {DISPATCH_RESOLVE_DIRECT, 55, GLX_1_3, 1231}, /* glXGetCurrentReadDrawable */
    {DISPATCH_RESOLVE_EXTENSION, 56, 58 /* GLX_SGI_make_current_read */, 1257}, /* glXGetCurrentReadDrawableSGI */
    {DISPATCH_RESOLVE_DIRECT, 57, GLX_1_3, 1286}, /* glXGetFBConfigAttrib */
    {DISPATCH_RESOLVE_EXTENSION, 58, 49 /* GLX_SGIX_fbconfig */, 1307}, /* glXGetFBConfigAttribSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 59, 49 /* GLX_SGIX_fbconfig */, 1332}, /* glXGetFBConfigFromVisualSGIX */
    {DISPATCH_RESOLVE_DIRECT, 60, GLX_1_3, 1361}, /* glXGetFBConfigs */
    {DISPATCH_RESOLVE_EXTENSION, 61, 1 /* GLX_AMD_gpu_association */, 1377}, /* glXGetGPUIDsAMD */
    {DISPATCH_RESOLVE_EXTENSION, 62, 1 /* GLX_AMD_gpu_association */, 1393}, /* glXGetGPUInfoAMD */
    {DISPATCH_RESOLVE_EXTENSION, 63, 44 /* GLX_OML_sync_control */, 1410}, /* glXGetMscRateOML */
    {DISPATCH_RESOLVE_DIRECT, 64, GLX_1_4, 1427}, /* glXGetProcAddress */
    {DISPATCH_RESOLVE_EXTENSION, 65, 8 /* GLX_ARB_get_proc_address */, 1445}, /* glXGetProcAddressARB */
    {DISPATCH_RESOLVE_DIRECT, 66, GLX_1_3, 1466}, /* glXGetSelectedEvent */
    {DISPATCH_RESOLVE_EXTENSION, 67, 51 /* GLX_SGIX_pbuffer */, 1486}, /* glXGetSelectedEventSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 68, 44 /* GLX_OML_sync_control */, 1510}, /* glXGetSyncValuesOML */
    {DISPATCH_RESOLVE_EXTENSION, 69, 61 /* GLX_SUN_get_transparent_index */, 1530}, /* glXGetTransparentIndexSUN */
    {DISPATCH_RESOLVE_EXTENSION, 70, 42 /* GLX_NV_video_out */, 1556}, /* glXGetVideoDeviceNV */
    {DISPATCH_RESOLVE_EXTENSION, 71, 42 /* GLX_NV_video_out */, 1576}, /* glXGetVideoInfoNV */
    {DISPATCH_RESOLVE_EXTENSION, 72, 60 /* GLX_SGI_video_sync */, 1594}, /* glXGetVideoSyncSGI */
    {DISPATCH_RESOLVE_DIRECT, 73, GLX_1_3, 1613}, /* glXGetVisualFromFBConfig */
    {DISPATCH_RESOLVE_EXTENSION, 74, 49 /* GLX_SGIX_fbconfig */, 1638}, /* glXGetVisualFromFBConfigSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 75, 50 /* GLX_SGIX_hyperpipe */, 1667}, /* glXHyperpipeAttribSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 76, 50 /* GLX_SGIX_hyperpipe */, 1690}, /* glXHyperpipeConfigSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 77, 18 /* GLX_EXT_import_context */, 1713}, /* glXImportContextEXT */
    {DISPATCH_RESOLVE_DIRECT, 78, GLX_1_0, 1733}, /* glXIsDirect */
    {DISPATCH_RESOLVE_EXTENSION, 79, 40 /* GLX_NV_swap_group */, 1745}, /* glXJoinSwapGroupNV */
    {DISPATCH_RESOLVE_EXTENSION, 80, 53 /* GLX_SGIX_swap_group */, 1764}, /* glXJoinSwapGroupSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 81, 41 /* GLX_NV_video_capture */, 1785}, /* glXLockVideoCaptureDeviceNV */
    {DISPATCH_RESOLVE_EXTENSION, 82, 1 /* GLX_AMD_gpu_association */, 1813}, /* glXMakeAssociatedContextCurrentAMD */
    {DISPATCH_RESOLVE_DIRECT, 83, GLX_1_3, 1848}, /* glXMakeContextCurrent */
    {DISPATCH_RESOLVE_DIRECT, 84, GLX_1_0, 1870}, /* glXMakeCurrent */
    {DISPATCH_RESOLVE_EXTENSION, 85, 58 /* GLX_SGI_make_current_read */, 1885}, /* glXMakeCurrentReadSGI */
    {DISPATCH_RESOLVE_EXTENSION, 86, 33 /* GLX_NV_copy_buffer */, 1907}, /* glXNamedCopyBufferSubDataNV */
    {DISPATCH_RESOLVE_EXTENSION, 87, 54 /* GLX_SGIX_video_resize */, 1935}, /* glXQueryChannelDeltasSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 88, 54 /* GLX_SGIX_video_resize */, 1961}, /* glXQueryChannelRectSGIX */
    {DISPATCH_RESOLVE_DIRECT, 89, GLX_1_3, 1985}, /* glXQueryContext */
    {DISPATCH_RESOLVE_EXTENSION, 90, 18 /* GLX_EXT_import_context */, 2001}, /* glXQueryContextInfoEXT */
    {DISPATCH_RESOLVE_EXTENSION, 91, 30 /* GLX_MESA_query_renderer */, 2024}, /* glXQueryCurrentRendererIntegerMESA */
    {DISPATCH_RESOLVE_EXTENSION, 92, 30 /* GLX_MESA_query_renderer */, 2059}, /* glXQueryCurrentRendererStringMESA */
    {DISPATCH_RESOLVE_DIRECT, 93, GLX_1_3, 2093}, /* glXQueryDrawable */
    {DISPATCH_RESOLVE_DIRECT, 94, GLX_1_0, 2110}, /* glXQueryExtension */
    {DISPATCH_RESOLVE_DIRECT, 95, GLX_1_1, 2128}, /* glXQueryExtensionsString */
    {DISPATCH_RESOLVE_EXTENSION, 96, 40 /* GLX_NV_swap_group */, 2153}, /* glXQueryFrameCountNV */
    {DISPATCH_RESOLVE_EXTENSION, 97, 51 /* GLX_SGIX_pbuffer */, 2174}, /* glXQueryGLXPbufferSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 98, 50 /* GLX_SGIX_hyperpipe */, 2197}, /* glXQueryHyperpipeAttribSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 99, 50 /* GLX_SGIX_hyperpipe */, 2225}, /* glXQueryHyperpipeBestAttribSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 100, 50 /* GLX_SGIX_hyperpipe */, 2257}, /* glXQueryHyperpipeConfigSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 101, 50 /* GLX_SGIX_hyperpipe */, 2285}, /* glXQueryHyperpipeNetworkSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 102, 52 /* GLX_SGIX_swap_barrier */, 2314}, /* glXQueryMaxSwapBarriersSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 103, 40 /* GLX_NV_swap_group */, 2342}, /* glXQueryMaxSwapGroupsNV */
    {DISPATCH_RESOLVE_EXTENSION, 104, 30 /* GLX_MESA_query_renderer */, 2366}, /* glXQueryRendererIntegerMESA */
    {DISPATCH_RESOLVE_EXTENSION, 105, 30 /* GLX_MESA_query_renderer */, 2394}, /* glXQueryRendererStringMESA */
    {DISPATCH_RESOLVE_DIRECT, 106, GLX_1_1, 2421}, /* glXQueryServerString */
    {DISPATCH_RESOLVE_EXTENSION, 107, 40 /* GLX_NV_swap_group */, 2442}, /* glXQuerySwapGroupNV */
    {DISPATCH_RESOLVE_DIRECT, 108, GLX_1_0, 2462}, /* glXQueryVersion */
    {DISPATCH_RESOLVE_EXTENSION, 109, 41 /* GLX_NV_video_capture */, 2478}, /* glXQueryVideoCaptureDeviceNV */
    {DISPATCH_RESOLVE_EXTENSION, 110, 31 /* GLX_MESA_release_buffers */, 2507}, /* glXReleaseBuffersMESA */
    {DISPATCH_RESOLVE_EXTENSION, 111, 23 /* GLX_EXT_texture_from_pixmap */, 2529}, /* glXReleaseTexImageEXT */
    {DISPATCH_RESOLVE_EXTENSION, 112, 41 /* GLX_NV_video_capture */, 2551}, /* glXReleaseVideoCaptureDeviceNV */
    {DISPATCH_RESOLVE_EXTENSION, 113, 42 /* GLX_NV_video_out */, 2582}, /* glXReleaseVideoDeviceNV */
    {DISPATCH_RESOLVE_EXTENSION, 114, 42 /* GLX_NV_video_out */, 2606}, /* glXReleaseVideoImageNV */
    {DISPATCH_RESOLVE_EXTENSION, 115, 40 /* GLX_NV_swap_group */, 2629}, /* glXResetFrameCountNV */
    {DISPATCH_RESOLVE_DIRECT, 116, GLX_1_3, 2650}, /* glXSelectEvent */
    {DISPATCH_RESOLVE_EXTENSION, 117, 51 /* GLX_SGIX_pbuffer */, 2665}, /* glXSelectEventSGIX */
    {DISPATCH_RESOLVE_EXTENSION, 118, 42 /* GLX_NV_video_out */, 2684}, /* glXSendPbufferToVideoNV */
    {DISPATCH_RESOLVE_EXTENSION, 119, 32 /* GLX_MESA_set_3dfx_mode */, 2708}, /* glXSet3DfxModeMESA */
    {DISPATCH_RESOLVE_DIRECT, 120, GLX_1_0, 2727}, /* glXSwapBuffers */
    {DISPATCH_RESOLVE_EXTENSION, 121, 44 /* GLX_OML_sync_control */, 2742}, /* glXSwapBuffersMscOML */
    {DISPATCH_RESOLVE_EXTENSION, 122, 21 /* GLX_EXT_swap_control */, 2763}, /* glXSwapIntervalEXT */
    {DISPATCH_RESOLVE_EXTENSION, 123, 59 /* GLX_SGI_swap_control */, 2782}, /* glXSwapIntervalSGI */
    {DISPATCH_RESOLVE_DIRECT, 124, GLX_1_0, 2801}, /* glXUseXFont */
    {DISPATCH_RESOLVE_EXTENSION, 125, 44 /* GLX_OML_sync_control */, 2813}, /* glXWaitForMscOML */
    {DISPATCH_RESOLVE_EXTENSION, 126, 44 /* GLX_OML_sync_control */, 2830}, /* glXWaitForSbcOML */
    {DISPATCH_RESOLVE_DIRECT, 127, GLX_1_0, 2847}, /* glXWaitGL */
    {DISPATCH_RESOLVE_EXTENSION, 128, 60 /* GLX_SGI_video_sync */, 2857}, /* glXWaitVideoSyncSGI */
    {DISPATCH_RESOLVE_DIRECT, 129, GLX_1_0, 2877}, /* glXWaitX */
    {DISPATCH_RESOLVE_TERMINATOR, 130, 0, 0}
};

static khronos_uint16_t glx_resolve_offsets[130] = {0};
static khronos_uint32_t glx_method_name_offsets[130] = {0};

#define HAS_DISPATCH_RESOLVE_DIRECT 1
#define HAS_DISPATCH_RESOLVE_VERSION 0
#define current_resolve glx_resolve
#define current_glproxy_resolve_init glx_glproxy_resolve_init
#define current_glproxy_resolve_direct glx_glproxy_resolve_direct
#define current_glproxy_resolve_version glx_glproxy_resolve_version
#define current_glproxy_resolve_extension glx_glproxy_resolve_extension
#define current_dispatch_table glx_dispatch_table
#define current_metadata glx_metadata
#define current_glproxy_resolve_local glx_glproxy_resolve_local
#define current_glproxy_dispatch_metadata_init glx_glproxy_dispatch_metadata_init
#define current_extension_offsets glx_extension_offsets
#define current_extensions_count glx_extensions_count
#define current_extension_enum_strings glx_extension_enum_strings
#define current_entrypoint_strings glx_entrypoint_strings
#define current_resolve_info_table glx_resolve_info_table
#define current_resolve_offsets glx_resolve_offsets
#define current_method_name_offsets glx_method_name_offsets
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

GEN_THUNK_RET(glx, int, glXBindChannelToWindowSGIX, (Display * display, int screen, int channel, Window window), (display, screen, channel, window), 0, PFNGLXBINDCHANNELTOWINDOWSGIXPROC)
GEN_THUNK_RET(glx, int, glXBindHyperpipeSGIX, (Display * dpy, int hpId), (dpy, hpId), 1, PFNGLXBINDHYPERPIPESGIXPROC)
GEN_THUNK_RET(glx, Bool, glXBindSwapBarrierNV, (Display * dpy, GLuint group, GLuint barrier), (dpy, group, barrier), 2, PFNGLXBINDSWAPBARRIERNVPROC)
GEN_THUNK(glx, glXBindSwapBarrierSGIX, (Display * dpy, GLXDrawable drawable, int barrier), (dpy, drawable, barrier), 3, PFNGLXBINDSWAPBARRIERSGIXPROC)
GEN_THUNK(glx, glXBindTexImageEXT, (Display * dpy, GLXDrawable drawable, int buffer, const int * attrib_list), (dpy, drawable, buffer, attrib_list), 4, PFNGLXBINDTEXIMAGEEXTPROC)
GEN_THUNK_RET(glx, int, glXBindVideoCaptureDeviceNV, (Display * dpy, unsigned int video_capture_slot, GLXVideoCaptureDeviceNV device), (dpy, video_capture_slot, device), 5, PFNGLXBINDVIDEOCAPTUREDEVICENVPROC)
GEN_THUNK_RET(glx, int, glXBindVideoDeviceNV, (Display * dpy, unsigned int video_slot, unsigned int video_device, const int * attrib_list), (dpy, video_slot, video_device, attrib_list), 6, PFNGLXBINDVIDEODEVICENVPROC)
GEN_THUNK_RET(glx, int, glXBindVideoImageNV, (Display * dpy, GLXVideoDeviceNV VideoDevice, GLXPbuffer pbuf, int iVideoBuffer), (dpy, VideoDevice, pbuf, iVideoBuffer), 7, PFNGLXBINDVIDEOIMAGENVPROC)
GEN_THUNK(glx, glXBlitContextFramebufferAMD, (GLXContext dstCtx, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter), (dstCtx, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter), 8, PFNGLXBLITCONTEXTFRAMEBUFFERAMDPROC)
GEN_THUNK_RET(glx, int, glXChannelRectSGIX, (Display * display, int screen, int channel, int x, int y, int w, int h), (display, screen, channel, x, y, w, h), 9, PFNGLXCHANNELRECTSGIXPROC)
GEN_THUNK_RET(glx, int, glXChannelRectSyncSGIX, (Display * display, int screen, int channel, GLenum synctype), (display, screen, channel, synctype), 10, PFNGLXCHANNELRECTSYNCSGIXPROC)
GEN_THUNK_RET(glx, GLXFBConfig *, glXChooseFBConfig, (Display * dpy, int screen, const int * attrib_list, int * nelements), (dpy, screen, attrib_list, nelements), 11, PFNGLXCHOOSEFBCONFIGPROC)
GEN_THUNK_RET(glx, GLXFBConfigSGIX *, glXChooseFBConfigSGIX, (Display * dpy, int screen, int * attrib_list, int * nelements), (dpy, screen, attrib_list, nelements), 12, PFNGLXCHOOSEFBCONFIGSGIXPROC)
GEN_THUNK_RET(glx, XVisualInfo *, glXChooseVisual, (Display * dpy, int screen, int * attribList), (dpy, screen, attribList), 13, PFNGLXCHOOSEVISUALPROC)
GEN_THUNK(glx, glXCopyBufferSubDataNV, (Display * dpy, GLXContext readCtx, GLXContext writeCtx, GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size), (dpy, readCtx, writeCtx, readTarget, writeTarget, readOffset, writeOffset, size), 14, PFNGLXCOPYBUFFERSUBDATANVPROC)
GEN_THUNK(glx, glXCopyContext, (Display * dpy, GLXContext src, GLXContext dst, unsigned long mask), (dpy, src, dst, mask), 15, PFNGLXCOPYCONTEXTPROC)
GEN_THUNK(glx, glXCopyImageSubDataNV, (Display * dpy, GLXContext srcCtx, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLXContext dstCtx, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth), (dpy, srcCtx, srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstCtx, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, width, height, depth), 16, PFNGLXCOPYIMAGESUBDATANVPROC)
GEN_THUNK(glx, glXCopySubBufferMESA, (Display * dpy, GLXDrawable drawable, int x, int y, int width, int height), (dpy, drawable, x, y, width, height), 17, PFNGLXCOPYSUBBUFFERMESAPROC)
GEN_THUNK_RET(glx, GLXContext, glXCreateAssociatedContextAMD, (unsigned int id, GLXContext share_list), (id, share_list), 18, PFNGLXCREATEASSOCIATEDCONTEXTAMDPROC)
GEN_THUNK_RET(glx, GLXContext, glXCreateAssociatedContextAttribsAMD, (unsigned int id, GLXContext share_context, const int * attribList), (id, share_context, attribList), 19, PFNGLXCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC)
GEN_THUNK_RET(glx, GLXContext, glXCreateContext, (Display * dpy, XVisualInfo * vis, GLXContext shareList, Bool direct), (dpy, vis, shareList, direct), 20, PFNGLXCREATECONTEXTPROC)
GEN_THUNK_RET(glx, GLXContext, glXCreateContextAttribsARB, (Display * dpy, GLXFBConfig config, GLXContext share_context, Bool direct, const int * attrib_list), (dpy, config, share_context, direct, attrib_list), 21, PFNGLXCREATECONTEXTATTRIBSARBPROC)
GEN_THUNK_RET(glx, GLXContext, glXCreateContextWithConfigSGIX, (Display * dpy, GLXFBConfigSGIX config, int render_type, GLXContext share_list, Bool direct), (dpy, config, render_type, share_list, direct), 22, PFNGLXCREATECONTEXTWITHCONFIGSGIXPROC)
GEN_THUNK_RET(glx, GLXPbufferSGIX, glXCreateGLXPbufferSGIX, (Display * dpy, GLXFBConfigSGIX config, unsigned int width, unsigned int height, int * attrib_list), (dpy, config, width, height, attrib_list), 23, PFNGLXCREATEGLXPBUFFERSGIXPROC)
GEN_THUNK_RET(glx, GLXPixmap, glXCreateGLXPixmap, (Display * dpy, XVisualInfo * visual, Pixmap pixmap), (dpy, visual, pixmap), 24, PFNGLXCREATEGLXPIXMAPPROC)
GEN_THUNK_RET(glx, GLXPixmap, glXCreateGLXPixmapMESA, (Display * dpy, XVisualInfo * visual, Pixmap pixmap, Colormap cmap), (dpy, visual, pixmap, cmap), 25, PFNGLXCREATEGLXPIXMAPMESAPROC)
GEN_THUNK_RET(glx, GLXPixmap, glXCreateGLXPixmapWithConfigSGIX, (Display * dpy, GLXFBConfigSGIX config, Pixmap pixmap), (dpy, config, pixmap), 26, PFNGLXCREATEGLXPIXMAPWITHCONFIGSGIXPROC)
GEN_THUNK_RET(glx, GLXContext, glXCreateNewContext, (Display * dpy, GLXFBConfig config, int render_type, GLXContext share_list, Bool direct), (dpy, config, render_type, share_list, direct), 27, PFNGLXCREATENEWCONTEXTPROC)
GEN_THUNK_RET(glx, GLXPbuffer, glXCreatePbuffer, (Display * dpy, GLXFBConfig config, const int * attrib_list), (dpy, config, attrib_list), 28, PFNGLXCREATEPBUFFERPROC)
GEN_THUNK_RET(glx, GLXPixmap, glXCreatePixmap, (Display * dpy, GLXFBConfig config, Pixmap pixmap, const int * attrib_list), (dpy, config, pixmap, attrib_list), 29, PFNGLXCREATEPIXMAPPROC)
GEN_THUNK_RET(glx, GLXWindow, glXCreateWindow, (Display * dpy, GLXFBConfig config, Window win, const int * attrib_list), (dpy, config, win, attrib_list), 30, PFNGLXCREATEWINDOWPROC)
GEN_THUNK(glx, glXCushionSGI, (Display * dpy, Window window, float cushion), (dpy, window, cushion), 31, PFNGLXCUSHIONSGIPROC)
GEN_THUNK_RET(glx, Bool, glXDelayBeforeSwapNV, (Display * dpy, GLXDrawable drawable, GLfloat seconds), (dpy, drawable, seconds), 32, PFNGLXDELAYBEFORESWAPNVPROC)
GEN_THUNK_RET(glx, Bool, glXDeleteAssociatedContextAMD, (GLXContext ctx), (ctx), 33, PFNGLXDELETEASSOCIATEDCONTEXTAMDPROC)
GEN_THUNK(glx, glXDestroyContext, (Display * dpy, GLXContext ctx), (dpy, ctx), 34, PFNGLXDESTROYCONTEXTPROC)
GEN_THUNK(glx, glXDestroyGLXPbufferSGIX, (Display * dpy, GLXPbufferSGIX pbuf), (dpy, pbuf), 35, PFNGLXDESTROYGLXPBUFFERSGIXPROC)
GEN_THUNK(glx, glXDestroyGLXPixmap, (Display * dpy, GLXPixmap pixmap), (dpy, pixmap), 36, PFNGLXDESTROYGLXPIXMAPPROC)
GEN_THUNK(glx, glXDestroyGLXVideoSourceSGIX, (Display * dpy, GLXVideoSourceSGIX glxvideosource), (dpy, glxvideosource), 37, PFNGLXDESTROYGLXVIDEOSOURCESGIXPROC)
GEN_THUNK_RET(glx, int, glXDestroyHyperpipeConfigSGIX, (Display * dpy, int hpId), (dpy, hpId), 38, PFNGLXDESTROYHYPERPIPECONFIGSGIXPROC)
GEN_THUNK(glx, glXDestroyPbuffer, (Display * dpy, GLXPbuffer pbuf), (dpy, pbuf), 39, PFNGLXDESTROYPBUFFERPROC)
GEN_THUNK(glx, glXDestroyPixmap, (Display * dpy, GLXPixmap pixmap), (dpy, pixmap), 40, PFNGLXDESTROYPIXMAPPROC)
GEN_THUNK(glx, glXDestroyWindow, (Display * dpy, GLXWindow win), (dpy, win), 41, PFNGLXDESTROYWINDOWPROC)
GEN_THUNK_RET(glx, GLXVideoCaptureDeviceNV *, glXEnumerateVideoCaptureDevicesNV, (Display * dpy, int screen, int * nelements), (dpy, screen, nelements), 42, PFNGLXENUMERATEVIDEOCAPTUREDEVICESNVPROC)
GEN_THUNK_RET(glx, unsigned int *, glXEnumerateVideoDevicesNV, (Display * dpy, int screen, int * nelements), (dpy, screen, nelements), 43, PFNGLXENUMERATEVIDEODEVICESNVPROC)
GEN_THUNK(glx, glXFreeContextEXT, (Display * dpy, GLXContext context), (dpy, context), 44, PFNGLXFREECONTEXTEXTPROC)
GEN_THUNK_RET(glx, unsigned int, glXGetAGPOffsetMESA, (const void * pointer), (pointer), 45, PFNGLXGETAGPOFFSETMESAPROC)
GEN_THUNK_RET(glx, const char *, glXGetClientString, (Display * dpy, int name), (dpy, name), 46, PFNGLXGETCLIENTSTRINGPROC)
GEN_THUNK_RET(glx, int, glXGetConfig, (Display * dpy, XVisualInfo * visual, int attrib, int * value), (dpy, visual, attrib, value), 47, PFNGLXGETCONFIGPROC)
GEN_THUNK_RET(glx, unsigned int, glXGetContextGPUIDAMD, (GLXContext ctx), (ctx), 48, PFNGLXGETCONTEXTGPUIDAMDPROC)
GEN_THUNK_RET(glx, GLXContextID, glXGetContextIDEXT, (const GLXContext context), (context), 49, PFNGLXGETCONTEXTIDEXTPROC)
GEN_THUNK_RET(glx, GLXContext, glXGetCurrentAssociatedContextAMD, (void), (), 50, PFNGLXGETCURRENTASSOCIATEDCONTEXTAMDPROC)
GEN_THUNK_RET(glx, GLXContext, glXGetCurrentContext, (void), (), 51, PFNGLXGETCURRENTCONTEXTPROC)
GEN_THUNK_RET(glx, Display *, glXGetCurrentDisplay, (void), (), 52, PFNGLXGETCURRENTDISPLAYPROC)
GEN_THUNK_RET(glx, Display *, glXGetCurrentDisplayEXT, (void), (), 53, PFNGLXGETCURRENTDISPLAYEXTPROC)
GEN_THUNK_RET(glx, GLXDrawable, glXGetCurrentDrawable, (void), (), 54, PFNGLXGETCURRENTDRAWABLEPROC)
GEN_THUNK_RET(glx, GLXDrawable, glXGetCurrentReadDrawable, (void), (), 55, PFNGLXGETCURRENTREADDRAWABLEPROC)
GEN_THUNK_RET(glx, GLXDrawable, glXGetCurrentReadDrawableSGI, (void), (), 56, PFNGLXGETCURRENTREADDRAWABLESGIPROC)
GEN_THUNK_RET(glx, int, glXGetFBConfigAttrib, (Display * dpy, GLXFBConfig config, int attribute, int * value), (dpy, config, attribute, value), 57, PFNGLXGETFBCONFIGATTRIBPROC)
GEN_THUNK_RET(glx, int, glXGetFBConfigAttribSGIX, (Display * dpy, GLXFBConfigSGIX config, int attribute, int * value), (dpy, config, attribute, value), 58, PFNGLXGETFBCONFIGATTRIBSGIXPROC)
GEN_THUNK_RET(glx, GLXFBConfigSGIX, glXGetFBConfigFromVisualSGIX, (Display * dpy, XVisualInfo * vis), (dpy, vis), 59, PFNGLXGETFBCONFIGFROMVISUALSGIXPROC)
GEN_THUNK_RET(glx, GLXFBConfig *, glXGetFBConfigs, (Display * dpy, int screen, int * nelements), (dpy, screen, nelements), 60, PFNGLXGETFBCONFIGSPROC)
GEN_THUNK_RET(glx, unsigned int, glXGetGPUIDsAMD, (unsigned int maxCount, unsigned int * ids), (maxCount, ids), 61, PFNGLXGETGPUIDSAMDPROC)
GEN_THUNK_RET(glx, int, glXGetGPUInfoAMD, (unsigned int id, int property, GLenum dataType, unsigned int size, void * data), (id, property, dataType, size, data), 62, PFNGLXGETGPUINFOAMDPROC)
GEN_THUNK_RET(glx, Bool, glXGetMscRateOML, (Display * dpy, GLXDrawable drawable, int32_t * numerator, int32_t * denominator), (dpy, drawable, numerator, denominator), 63, PFNGLXGETMSCRATEOMLPROC)
GEN_THUNK_RET(glx, __GLXextFuncPtr, glXGetProcAddress, (const GLubyte * procName), (procName), 64, PFNGLXGETPROCADDRESSPROC)
GEN_THUNK_RET(glx, __GLXextFuncPtr, glXGetProcAddressARB, (const GLubyte * procName), (procName), 65, PFNGLXGETPROCADDRESSARBPROC)
GEN_THUNK(glx, glXGetSelectedEvent, (Display * dpy, GLXDrawable draw, unsigned long * event_mask), (dpy, draw, event_mask), 66, PFNGLXGETSELECTEDEVENTPROC)
GEN_THUNK(glx, glXGetSelectedEventSGIX, (Display * dpy, GLXDrawable drawable, unsigned long * mask), (dpy, drawable, mask), 67, PFNGLXGETSELECTEDEVENTSGIXPROC)
GEN_THUNK_RET(glx, Bool, glXGetSyncValuesOML, (Display * dpy, GLXDrawable drawable, int64_t * ust, int64_t * msc, int64_t * sbc), (dpy, drawable, ust, msc, sbc), 68, PFNGLXGETSYNCVALUESOMLPROC)
GEN_THUNK_RET(glx, Status, glXGetTransparentIndexSUN, (Display * dpy, Window overlay, Window underlay, long * pTransparentIndex), (dpy, overlay, underlay, pTransparentIndex), 69, PFNGLXGETTRANSPARENTINDEXSUNPROC)
GEN_THUNK_RET(glx, int, glXGetVideoDeviceNV, (Display * dpy, int screen, int numVideoDevices, GLXVideoDeviceNV * pVideoDevice), (dpy, screen, numVideoDevices, pVideoDevice), 70, PFNGLXGETVIDEODEVICENVPROC)
GEN_THUNK_RET(glx, int, glXGetVideoInfoNV, (Display * dpy, int screen, GLXVideoDeviceNV VideoDevice, unsigned long * pulCounterOutputPbuffer, unsigned long * pulCounterOutputVideo), (dpy, screen, VideoDevice, pulCounterOutputPbuffer, pulCounterOutputVideo), 71, PFNGLXGETVIDEOINFONVPROC)
GEN_THUNK_RET(glx, int, glXGetVideoSyncSGI, (unsigned int * count), (count), 72, PFNGLXGETVIDEOSYNCSGIPROC)
GEN_THUNK_RET(glx, XVisualInfo *, glXGetVisualFromFBConfig, (Display * dpy, GLXFBConfig config), (dpy, config), 73, PFNGLXGETVISUALFROMFBCONFIGPROC)
GEN_THUNK_RET(glx, XVisualInfo *, glXGetVisualFromFBConfigSGIX, (Display * dpy, GLXFBConfigSGIX config), (dpy, config), 74, PFNGLXGETVISUALFROMFBCONFIGSGIXPROC)
GEN_THUNK_RET(glx, int, glXHyperpipeAttribSGIX, (Display * dpy, int timeSlice, int attrib, int size, void * attribList), (dpy, timeSlice, attrib, size, attribList), 75, PFNGLXHYPERPIPEATTRIBSGIXPROC)
GEN_THUNK_RET(glx, int, glXHyperpipeConfigSGIX, (Display * dpy, int networkId, int npipes, GLXHyperpipeConfigSGIX * cfg, int * hpId), (dpy, networkId, npipes, cfg, hpId), 76, PFNGLXHYPERPIPECONFIGSGIXPROC)
GEN_THUNK_RET(glx, GLXContext, glXImportContextEXT, (Display * dpy, GLXContextID contextID), (dpy, contextID), 77, PFNGLXIMPORTCONTEXTEXTPROC)
GEN_THUNK_RET(glx, Bool, glXIsDirect, (Display * dpy, GLXContext ctx), (dpy, ctx), 78, PFNGLXISDIRECTPROC)
GEN_THUNK_RET(glx, Bool, glXJoinSwapGroupNV, (Display * dpy, GLXDrawable drawable, GLuint group), (dpy, drawable, group), 79, PFNGLXJOINSWAPGROUPNVPROC)
GEN_THUNK(glx, glXJoinSwapGroupSGIX, (Display * dpy, GLXDrawable drawable, GLXDrawable member), (dpy, drawable, member), 80, PFNGLXJOINSWAPGROUPSGIXPROC)
GEN_THUNK(glx, glXLockVideoCaptureDeviceNV, (Display * dpy, GLXVideoCaptureDeviceNV device), (dpy, device), 81, PFNGLXLOCKVIDEOCAPTUREDEVICENVPROC)
GEN_THUNK_RET(glx, Bool, glXMakeAssociatedContextCurrentAMD, (GLXContext ctx), (ctx), 82, PFNGLXMAKEASSOCIATEDCONTEXTCURRENTAMDPROC)
GEN_THUNK_RET(glx, Bool, glXMakeContextCurrent, (Display * dpy, GLXDrawable draw, GLXDrawable read, GLXContext ctx), (dpy, draw, read, ctx), 83, PFNGLXMAKECONTEXTCURRENTPROC)
GEN_THUNK_RET(glx, Bool, glXMakeCurrent, (Display * dpy, GLXDrawable drawable, GLXContext ctx), (dpy, drawable, ctx), 84, PFNGLXMAKECURRENTPROC)
GEN_THUNK_RET(glx, Bool, glXMakeCurrentReadSGI, (Display * dpy, GLXDrawable draw, GLXDrawable read, GLXContext ctx), (dpy, draw, read, ctx), 85, PFNGLXMAKECURRENTREADSGIPROC)
GEN_THUNK(glx, glXNamedCopyBufferSubDataNV, (Display * dpy, GLXContext readCtx, GLXContext writeCtx, GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size), (dpy, readCtx, writeCtx, readBuffer, writeBuffer, readOffset, writeOffset, size), 86, PFNGLXNAMEDCOPYBUFFERSUBDATANVPROC)
GEN_THUNK_RET(glx, int, glXQueryChannelDeltasSGIX, (Display * display, int screen, int channel, int * x, int * y, int * w, int * h), (display, screen, channel, x, y, w, h), 87, PFNGLXQUERYCHANNELDELTASSGIXPROC)
GEN_THUNK_RET(glx, int, glXQueryChannelRectSGIX, (Display * display, int screen, int channel, int * dx, int * dy, int * dw, int * dh), (display, screen, channel, dx, dy, dw, dh), 88, PFNGLXQUERYCHANNELRECTSGIXPROC)
GEN_THUNK_RET(glx, int, glXQueryContext, (Display * dpy, GLXContext ctx, int attribute, int * value), (dpy, ctx, attribute, value), 89, PFNGLXQUERYCONTEXTPROC)
GEN_THUNK_RET(glx, int, glXQueryContextInfoEXT, (Display * dpy, GLXContext context, int attribute, int * value), (dpy, context, attribute, value), 90, PFNGLXQUERYCONTEXTINFOEXTPROC)
GEN_THUNK_RET(glx, Bool, glXQueryCurrentRendererIntegerMESA, (int attribute, unsigned int * value), (attribute, value), 91, PFNGLXQUERYCURRENTRENDERERINTEGERMESAPROC)
GEN_THUNK_RET(glx, const char *, glXQueryCurrentRendererStringMESA, (int attribute), (attribute), 92, PFNGLXQUERYCURRENTRENDERERSTRINGMESAPROC)
GEN_THUNK(glx, glXQueryDrawable, (Display * dpy, GLXDrawable draw, int attribute, unsigned int * value), (dpy, draw, attribute, value), 93, PFNGLXQUERYDRAWABLEPROC)
GEN_THUNK_RET(glx, Bool, glXQueryExtension, (Display * dpy, int * errorb, int * event), (dpy, errorb, event), 94, PFNGLXQUERYEXTENSIONPROC)
GEN_THUNK_RET(glx, const char *, glXQueryExtensionsString, (Display * dpy, int screen), (dpy, screen), 95, PFNGLXQUERYEXTENSIONSSTRINGPROC)
GEN_THUNK_RET(glx, Bool, glXQueryFrameCountNV, (Display * dpy, int screen, GLuint * count), (dpy, screen, count), 96, PFNGLXQUERYFRAMECOUNTNVPROC)
GEN_THUNK_RET(glx, int, glXQueryGLXPbufferSGIX, (Display * dpy, GLXPbufferSGIX pbuf, int attribute, unsigned int * value), (dpy, pbuf, attribute, value), 97, PFNGLXQUERYGLXPBUFFERSGIXPROC)
GEN_THUNK_RET(glx, int, glXQueryHyperpipeAttribSGIX, (Display * dpy, int timeSlice, int attrib, int size, void * returnAttribList), (dpy, timeSlice, attrib, size, returnAttribList), 98, PFNGLXQUERYHYPERPIPEATTRIBSGIXPROC)
GEN_THUNK_RET(glx, int, glXQueryHyperpipeBestAttribSGIX, (Display * dpy, int timeSlice, int attrib, int size, void * attribList, void * returnAttribList), (dpy, timeSlice, attrib, size, attribList, returnAttribList), 99, PFNGLXQUERYHYPERPIPEBESTATTRIBSGIXPROC)
GEN_THUNK_RET(glx, GLXHyperpipeConfigSGIX *, glXQueryHyperpipeConfigSGIX, (Display * dpy, int hpId, int * npipes), (dpy, hpId, npipes), 100, PFNGLXQUERYHYPERPIPECONFIGSGIXPROC)
GEN_THUNK_RET(glx, GLXHyperpipeNetworkSGIX *, glXQueryHyperpipeNetworkSGIX, (Display * dpy, int * npipes), (dpy, npipes), 101, PFNGLXQUERYHYPERPIPENETWORKSGIXPROC)
GEN_THUNK_RET(glx, Bool, glXQueryMaxSwapBarriersSGIX, (Display * dpy, int screen, int * max), (dpy, screen, max), 102, PFNGLXQUERYMAXSWAPBARRIERSSGIXPROC)
GEN_THUNK_RET(glx, Bool, glXQueryMaxSwapGroupsNV, (Display * dpy, int screen, GLuint * maxGroups, GLuint * maxBarriers), (dpy, screen, maxGroups, maxBarriers), 103, PFNGLXQUERYMAXSWAPGROUPSNVPROC)
GEN_THUNK_RET(glx, Bool, glXQueryRendererIntegerMESA, (Display * dpy, int screen, int renderer, int attribute, unsigned int * value), (dpy, screen, renderer, attribute, value), 104, PFNGLXQUERYRENDERERINTEGERMESAPROC)
GEN_THUNK_RET(glx, const char *, glXQueryRendererStringMESA, (Display * dpy, int screen, int renderer, int attribute), (dpy, screen, renderer, attribute), 105, PFNGLXQUERYRENDERERSTRINGMESAPROC)
GEN_THUNK_RET(glx, const char *, glXQueryServerString, (Display * dpy, int screen, int name), (dpy, screen, name), 106, PFNGLXQUERYSERVERSTRINGPROC)
GEN_THUNK_RET(glx, Bool, glXQuerySwapGroupNV, (Display * dpy, GLXDrawable drawable, GLuint * group, GLuint * barrier), (dpy, drawable, group, barrier), 107, PFNGLXQUERYSWAPGROUPNVPROC)
GEN_THUNK_RET(glx, Bool, glXQueryVersion, (Display * dpy, int * maj, int * min), (dpy, maj, min), 108, PFNGLXQUERYVERSIONPROC)
GEN_THUNK_RET(glx, int, glXQueryVideoCaptureDeviceNV, (Display * dpy, GLXVideoCaptureDeviceNV device, int attribute, int * value), (dpy, device, attribute, value), 109, PFNGLXQUERYVIDEOCAPTUREDEVICENVPROC)
GEN_THUNK_RET(glx, Bool, glXReleaseBuffersMESA, (Display * dpy, GLXDrawable drawable), (dpy, drawable), 110, PFNGLXRELEASEBUFFERSMESAPROC)
GEN_THUNK(glx, glXReleaseTexImageEXT, (Display * dpy, GLXDrawable drawable, int buffer), (dpy, drawable, buffer), 111, PFNGLXRELEASETEXIMAGEEXTPROC)
GEN_THUNK(glx, glXReleaseVideoCaptureDeviceNV, (Display * dpy, GLXVideoCaptureDeviceNV device), (dpy, device), 112, PFNGLXRELEASEVIDEOCAPTUREDEVICENVPROC)
GEN_THUNK_RET(glx, int, glXReleaseVideoDeviceNV, (Display * dpy, int screen, GLXVideoDeviceNV VideoDevice), (dpy, screen, VideoDevice), 113, PFNGLXRELEASEVIDEODEVICENVPROC)
GEN_THUNK_RET(glx, int, glXReleaseVideoImageNV, (Display * dpy, GLXPbuffer pbuf), (dpy, pbuf), 114, PFNGLXRELEASEVIDEOIMAGENVPROC)
GEN_THUNK_RET(glx, Bool, glXResetFrameCountNV, (Display * dpy, int screen), (dpy, screen), 115, PFNGLXRESETFRAMECOUNTNVPROC)
GEN_THUNK(glx, glXSelectEvent, (Display * dpy, GLXDrawable draw, unsigned long event_mask), (dpy, draw, event_mask), 116, PFNGLXSELECTEVENTPROC)
GEN_THUNK(glx, glXSelectEventSGIX, (Display * dpy, GLXDrawable drawable, unsigned long mask), (dpy, drawable, mask), 117, PFNGLXSELECTEVENTSGIXPROC)
GEN_THUNK_RET(glx, int, glXSendPbufferToVideoNV, (Display * dpy, GLXPbuffer pbuf, int iBufferType, unsigned long * pulCounterPbuffer, GLboolean bBlock), (dpy, pbuf, iBufferType, pulCounterPbuffer, bBlock), 118, PFNGLXSENDPBUFFERTOVIDEONVPROC)
GEN_THUNK_RET(glx, Bool, glXSet3DfxModeMESA, (int mode), (mode), 119, PFNGLXSET3DFXMODEMESAPROC)
GEN_THUNK(glx, glXSwapBuffers, (Display * dpy, GLXDrawable drawable), (dpy, drawable), 120, PFNGLXSWAPBUFFERSPROC)
GEN_THUNK_RET(glx, int64_t, glXSwapBuffersMscOML, (Display * dpy, GLXDrawable drawable, int64_t target_msc, int64_t divisor, int64_t remainder), (dpy, drawable, target_msc, divisor, remainder), 121, PFNGLXSWAPBUFFERSMSCOMLPROC)
GEN_THUNK(glx, glXSwapIntervalEXT, (Display * dpy, GLXDrawable drawable, int interval), (dpy, drawable, interval), 122, PFNGLXSWAPINTERVALEXTPROC)
GEN_THUNK_RET(glx, int, glXSwapIntervalSGI, (int interval), (interval), 123, PFNGLXSWAPINTERVALSGIPROC)
GEN_THUNK(glx, glXUseXFont, (Font font, int first, int count, int list), (font, first, count, list), 124, PFNGLXUSEXFONTPROC)
GEN_THUNK_RET(glx, Bool, glXWaitForMscOML, (Display * dpy, GLXDrawable drawable, int64_t target_msc, int64_t divisor, int64_t remainder, int64_t * ust, int64_t * msc, int64_t * sbc), (dpy, drawable, target_msc, divisor, remainder, ust, msc, sbc), 125, PFNGLXWAITFORMSCOMLPROC)
GEN_THUNK_RET(glx, Bool, glXWaitForSbcOML, (Display * dpy, GLXDrawable drawable, int64_t target_sbc, int64_t * ust, int64_t * msc, int64_t * sbc), (dpy, drawable, target_sbc, ust, msc, sbc), 126, PFNGLXWAITFORSBCOMLPROC)
GEN_THUNK(glx, glXWaitGL, (void), (), 127, PFNGLXWAITGLPROC)
GEN_THUNK_RET(glx, int, glXWaitVideoSyncSGI, (int divisor, int remainder, unsigned int * count), (divisor, remainder, count), 128, PFNGLXWAITVIDEOSYNCSGIPROC)
GEN_THUNK(glx, glXWaitX, (void), (), 129, PFNGLXWAITXPROC)

#endif /* PLATFORM_HAS_GLX */

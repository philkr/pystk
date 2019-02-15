/* GL dispatch header.
 * This is code-generated from the GL API XML files from Khronos.
 */

#pragma once
#include <stddef.h>

typedef unsigned int EGLBoolean;
typedef unsigned int EGLenum;
typedef khronos_intptr_t EGLAttribKHR;
typedef khronos_intptr_t EGLAttrib;
typedef void *EGLClientBuffer;
typedef void *EGLConfig;
typedef void *EGLContext;
typedef void *EGLDeviceEXT;
typedef void *EGLDisplay;
typedef void *EGLImage;
typedef void *EGLImageKHR;
typedef void *EGLLabelKHR;
typedef void *EGLObjectKHR;
typedef void *EGLOutputLayerEXT;
typedef void *EGLOutputPortEXT;
typedef void *EGLStreamKHR;
typedef void *EGLSurface;
typedef void *EGLSync;
typedef void *EGLSyncKHR;
typedef void *EGLSyncNV;
typedef void (*__eglMustCastToProperFunctionPointerType)(void);
typedef khronos_utime_nanoseconds_t EGLTimeKHR;
typedef khronos_utime_nanoseconds_t EGLTime;
typedef khronos_utime_nanoseconds_t EGLTimeNV;
typedef khronos_utime_nanoseconds_t EGLuint64NV;
typedef khronos_uint64_t EGLuint64KHR;
typedef khronos_stime_nanoseconds_t EGLnsecsANDROID;
typedef int EGLNativeFileDescriptorKHR;
typedef khronos_ssize_t EGLsizeiANDROID;
typedef void (*EGLSetBlobFuncANDROID) (const void *key, EGLsizeiANDROID keySize, const void *value, EGLsizeiANDROID valueSize);
typedef EGLsizeiANDROID (*EGLGetBlobFuncANDROID) (const void *key, EGLsizeiANDROID keySize, void *value, EGLsizeiANDROID valueSize);
struct EGLClientPixmapHI {
    void  *pData;
    EGLint iWidth;
    EGLint iHeight;
    EGLint iStride;
};
typedef void (APIENTRY *EGLDEBUGPROCKHR)(EGLenum error,const char *command,EGLint messageType,EGLLabelKHR threadLabel,EGLLabelKHR objectLabel,const char* message);

#define EGL_VERSION_1_0 1
#define EGL_VERSION_1_1 1
#define EGL_VERSION_1_2 1
#define EGL_VERSION_1_3 1
#define EGL_VERSION_1_4 1
#define EGL_VERSION_1_5 1

#define EGL_ANDROID_blob_cache 1
#define EGL_ANDROID_create_native_client_buffer 1
#define EGL_ANDROID_framebuffer_target 1
#define EGL_ANDROID_front_buffer_auto_refresh 1
#define EGL_ANDROID_image_native_buffer 1
#define EGL_ANDROID_native_fence_sync 1
#define EGL_ANDROID_presentation_time 1
#define EGL_ANDROID_recordable 1
#define EGL_ANGLE_d3d_share_handle_client_buffer 1
#define EGL_ANGLE_device_d3d 1
#define EGL_ANGLE_query_surface_pointer 1
#define EGL_ANGLE_surface_d3d_texture_2d_share_handle 1
#define EGL_ANGLE_window_fixed_size 1
#define EGL_ARM_pixmap_multisample_discard 1
#define EGL_EXT_buffer_age 1
#define EGL_EXT_client_extensions 1
#define EGL_EXT_create_context_robustness 1
#define EGL_EXT_device_base 1
#define EGL_EXT_device_drm 1
#define EGL_EXT_device_enumeration 1
#define EGL_EXT_device_openwf 1
#define EGL_EXT_device_query 1
#define EGL_EXT_image_dma_buf_import 1
#define EGL_EXT_multiview_window 1
#define EGL_EXT_output_base 1
#define EGL_EXT_output_drm 1
#define EGL_EXT_output_openwf 1
#define EGL_EXT_platform_base 1
#define EGL_EXT_platform_device 1
#define EGL_EXT_platform_wayland 1
#define EGL_EXT_platform_x11 1
#define EGL_EXT_protected_content 1
#define EGL_EXT_protected_surface 1
#define EGL_EXT_stream_consumer_egloutput 1
#define EGL_EXT_swap_buffers_with_damage 1
#define EGL_EXT_yuv_surface 1
#define EGL_HI_clientpixmap 1
#define EGL_HI_colorformats 1
#define EGL_IMG_context_priority 1
#define EGL_IMG_image_plane_attribs 1
#define EGL_KHR_cl_event 1
#define EGL_KHR_cl_event2 1
#define EGL_KHR_client_get_all_proc_addresses 1
#define EGL_KHR_config_attribs 1
#define EGL_KHR_create_context 1
#define EGL_KHR_create_context_no_error 1
#define EGL_KHR_debug 1
#define EGL_KHR_fence_sync 1
#define EGL_KHR_get_all_proc_addresses 1
#define EGL_KHR_gl_colorspace 1
#define EGL_KHR_gl_renderbuffer_image 1
#define EGL_KHR_gl_texture_2D_image 1
#define EGL_KHR_gl_texture_3D_image 1
#define EGL_KHR_gl_texture_cubemap_image 1
#define EGL_KHR_image 1
#define EGL_KHR_image_base 1
#define EGL_KHR_image_pixmap 1
#define EGL_KHR_lock_surface 1
#define EGL_KHR_lock_surface2 1
#define EGL_KHR_lock_surface3 1
#define EGL_KHR_mutable_render_buffer 1
#define EGL_KHR_partial_update 1
#define EGL_KHR_platform_android 1
#define EGL_KHR_platform_gbm 1
#define EGL_KHR_platform_wayland 1
#define EGL_KHR_platform_x11 1
#define EGL_KHR_reusable_sync 1
#define EGL_KHR_stream 1
#define EGL_KHR_stream_consumer_gltexture 1
#define EGL_KHR_stream_cross_process_fd 1
#define EGL_KHR_stream_fifo 1
#define EGL_KHR_stream_producer_aldatalocator 1
#define EGL_KHR_stream_producer_eglsurface 1
#define EGL_KHR_surfaceless_context 1
#define EGL_KHR_swap_buffers_with_damage 1
#define EGL_KHR_vg_parent_image 1
#define EGL_KHR_wait_sync 1
#define EGL_MESA_drm_image 1
#define EGL_MESA_image_dma_buf_export 1
#define EGL_MESA_platform_gbm 1
#define EGL_NOK_swap_region 1
#define EGL_NOK_swap_region2 1
#define EGL_NOK_texture_from_pixmap 1
#define EGL_NV_3dvision_surface 1
#define EGL_NV_coverage_sample 1
#define EGL_NV_coverage_sample_resolve 1
#define EGL_NV_cuda_event 1
#define EGL_NV_depth_nonlinear 1
#define EGL_NV_device_cuda 1
#define EGL_NV_native_query 1
#define EGL_NV_post_convert_rounding 1
#define EGL_NV_post_sub_buffer 1
#define EGL_NV_robustness_video_memory_purge 1
#define EGL_NV_stream_consumer_gltexture_yuv 1
#define EGL_NV_stream_metadata 1
#define EGL_NV_stream_sync 1
#define EGL_NV_sync 1
#define EGL_NV_system_time 1
#define EGL_TIZEN_image_native_buffer 1
#define EGL_TIZEN_image_native_surface 1

#define EGL_NO_CONTEXT                                       ((EGLContext)0)
#define EGL_NO_DEVICE_EXT                                    ((EGLDeviceEXT)(0))
#define EGL_NO_DISPLAY                                       ((EGLDisplay)0)
#define EGL_NO_IMAGE                                         ((EGLImage)0)
#define EGL_NO_IMAGE_KHR                                     ((EGLImageKHR)0)
#define EGL_DEFAULT_DISPLAY                                  ((EGLNativeDisplayType)0)
#define EGL_NO_FILE_DESCRIPTOR_KHR                           ((EGLNativeFileDescriptorKHR)(-1))
#define EGL_NO_OUTPUT_LAYER_EXT                              ((EGLOutputLayerEXT)0)
#define EGL_NO_OUTPUT_PORT_EXT                               ((EGLOutputPortEXT)0)
#define EGL_NO_STREAM_KHR                                    ((EGLStreamKHR)0)
#define EGL_NO_SURFACE                                       ((EGLSurface)0)
#define EGL_NO_SYNC                                          ((EGLSync)0)
#define EGL_NO_SYNC_KHR                                      ((EGLSyncKHR)0)
#define EGL_NO_SYNC_NV                                       ((EGLSyncNV)0)
#define EGL_DONT_CARE                                        ((EGLint)-1)
#define EGL_UNKNOWN                                          ((EGLint)-1)
#define EGL_NO_NATIVE_FENCE_FD_ANDROID                       -1
#define EGL_DEPTH_ENCODING_NONE_NV                           0
#define EGL_FALSE                                            0
#define EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT                  0x00000001
#define EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT_KHR              0x00000001
#define EGL_CONTEXT_OPENGL_DEBUG_BIT_KHR                     0x00000001
#define EGL_DRM_BUFFER_USE_SCANOUT_MESA                      0x00000001
#define EGL_NATIVE_BUFFER_USAGE_PROTECTED_BIT_ANDROID        0x00000001
#define EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT         0x00000002
#define EGL_CONTEXT_OPENGL_COMPATIBILITY_PROFILE_BIT_KHR     0x00000002
#define EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE_BIT_KHR        0x00000002
#define EGL_DRM_BUFFER_USE_SHARE_MESA                        0x00000002
#define EGL_NATIVE_BUFFER_USAGE_RENDERBUFFER_BIT_ANDROID     0x00000002
#define EGL_CONTEXT_OPENGL_ROBUST_ACCESS_BIT_KHR             0x00000004
#define EGL_NATIVE_BUFFER_USAGE_TEXTURE_BIT_ANDROID          0x00000004
#define EGL_OPENGL_ES3_BIT                                   0x00000040
#define EGL_OPENGL_ES3_BIT_KHR                               0x00000040
#define EGL_OPENGL_ES_BIT                                    0x0001
#define EGL_PBUFFER_BIT                                      0x0001
#define EGL_READ_SURFACE_BIT_KHR                             0x0001
#define EGL_SYNC_FLUSH_COMMANDS_BIT                          0x0001
#define EGL_SYNC_FLUSH_COMMANDS_BIT_KHR                      0x0001
#define EGL_SYNC_FLUSH_COMMANDS_BIT_NV                       0x0001
#define EGL_OPENVG_BIT                                       0x0002
#define EGL_PIXMAP_BIT                                       0x0002
#define EGL_WRITE_SURFACE_BIT_KHR                            0x0002
#define EGL_OPENGL_ES2_BIT                                   0x0004
#define EGL_WINDOW_BIT                                       0x0004
#define EGL_OPENGL_BIT                                       0x0008
#define EGL_PBUFFER_IMAGE_BIT_TAO                            0x0008
#define EGL_INTEROP_BIT_KHR                                  0x0010
#define EGL_PBUFFER_PALETTE_IMAGE_BIT_TAO                    0x0010
#define EGL_OPENMAX_IL_BIT_KHR                               0x0020
#define EGL_VG_COLORSPACE_LINEAR_BIT                         0x0020
#define EGL_VG_COLORSPACE_LINEAR_BIT_KHR                     0x0020
#define EGL_VG_ALPHA_FORMAT_PRE_BIT                          0x0040
#define EGL_VG_ALPHA_FORMAT_PRE_BIT_KHR                      0x0040
#define EGL_LOCK_SURFACE_BIT_KHR                             0x0080
#define EGL_OPTIMAL_FORMAT_BIT_KHR                           0x0100
#define EGL_MULTISAMPLE_RESOLVE_BOX_BIT                      0x0200
#define EGL_SWAP_BEHAVIOR_PRESERVED_BIT                      0x0400
#define EGL_STREAM_BIT_KHR                                   0x0800
#define EGL_MUTABLE_RENDER_BUFFER_BIT_KHR                    0x1000
#define EGL_SUCCESS                                          0x3000
#define EGL_NOT_INITIALIZED                                  0x3001
#define EGL_BAD_ACCESS                                       0x3002
#define EGL_BAD_ALLOC                                        0x3003
#define EGL_BAD_ATTRIBUTE                                    0x3004
#define EGL_BAD_CONFIG                                       0x3005
#define EGL_BAD_CONTEXT                                      0x3006
#define EGL_BAD_CURRENT_SURFACE                              0x3007
#define EGL_BAD_DISPLAY                                      0x3008
#define EGL_BAD_MATCH                                        0x3009
#define EGL_BAD_NATIVE_PIXMAP                                0x300A
#define EGL_BAD_NATIVE_WINDOW                                0x300B
#define EGL_BAD_PARAMETER                                    0x300C
#define EGL_BAD_SURFACE                                      0x300D
#define EGL_CONTEXT_LOST                                     0x300E
#define EGL_BUFFER_SIZE                                      0x3020
#define EGL_ALPHA_SIZE                                       0x3021
#define EGL_BLUE_SIZE                                        0x3022
#define EGL_GREEN_SIZE                                       0x3023
#define EGL_RED_SIZE                                         0x3024
#define EGL_DEPTH_SIZE                                       0x3025
#define EGL_STENCIL_SIZE                                     0x3026
#define EGL_CONFIG_CAVEAT                                    0x3027
#define EGL_CONFIG_ID                                        0x3028
#define EGL_LEVEL                                            0x3029
#define EGL_MAX_PBUFFER_HEIGHT                               0x302A
#define EGL_MAX_PBUFFER_PIXELS                               0x302B
#define EGL_MAX_PBUFFER_WIDTH                                0x302C
#define EGL_NATIVE_RENDERABLE                                0x302D
#define EGL_NATIVE_VISUAL_ID                                 0x302E
#define EGL_NATIVE_VISUAL_TYPE                               0x302F
#define EGL_SAMPLES                                          0x3031
#define EGL_SAMPLE_BUFFERS                                   0x3032
#define EGL_SURFACE_TYPE                                     0x3033
#define EGL_TRANSPARENT_TYPE                                 0x3034
#define EGL_TRANSPARENT_BLUE_VALUE                           0x3035
#define EGL_TRANSPARENT_GREEN_VALUE                          0x3036
#define EGL_TRANSPARENT_RED_VALUE                            0x3037
#define EGL_NONE                                             0x3038
#define EGL_BIND_TO_TEXTURE_RGB                              0x3039
#define EGL_BIND_TO_TEXTURE_RGBA                             0x303A
#define EGL_MIN_SWAP_INTERVAL                                0x303B
#define EGL_MAX_SWAP_INTERVAL                                0x303C
#define EGL_LUMINANCE_SIZE                                   0x303D
#define EGL_ALPHA_MASK_SIZE                                  0x303E
#define EGL_COLOR_BUFFER_TYPE                                0x303F
#define EGL_RENDERABLE_TYPE                                  0x3040
#define EGL_MATCH_NATIVE_PIXMAP                              0x3041
#define EGL_CONFORMANT                                       0x3042
#define EGL_CONFORMANT_KHR                                   0x3042
#define EGL_MATCH_FORMAT_KHR                                 0x3043
#define EGL_SLOW_CONFIG                                      0x3050
#define EGL_NON_CONFORMANT_CONFIG                            0x3051
#define EGL_TRANSPARENT_RGB                                  0x3052
#define EGL_VENDOR                                           0x3053
#define EGL_VERSION                                          0x3054
#define EGL_EXTENSIONS                                       0x3055
#define EGL_HEIGHT                                           0x3056
#define EGL_WIDTH                                            0x3057
#define EGL_LARGEST_PBUFFER                                  0x3058
#define EGL_DRAW                                             0x3059
#define EGL_READ                                             0x305A
#define EGL_CORE_NATIVE_ENGINE                               0x305B
#define EGL_NO_TEXTURE                                       0x305C
#define EGL_TEXTURE_RGB                                      0x305D
#define EGL_TEXTURE_RGBA                                     0x305E
#define EGL_TEXTURE_2D                                       0x305F
#define EGL_Y_INVERTED_NOK                                   0x307F
#define EGL_TEXTURE_FORMAT                                   0x3080
#define EGL_TEXTURE_TARGET                                   0x3081
#define EGL_MIPMAP_TEXTURE                                   0x3082
#define EGL_MIPMAP_LEVEL                                     0x3083
#define EGL_BACK_BUFFER                                      0x3084
#define EGL_SINGLE_BUFFER                                    0x3085
#define EGL_RENDER_BUFFER                                    0x3086
#define EGL_COLORSPACE                                       0x3087
#define EGL_VG_COLORSPACE                                    0x3087
#define EGL_ALPHA_FORMAT                                     0x3088
#define EGL_VG_ALPHA_FORMAT                                  0x3088
#define EGL_COLORSPACE_sRGB                                  0x3089
#define EGL_GL_COLORSPACE_SRGB                               0x3089
#define EGL_GL_COLORSPACE_SRGB_KHR                           0x3089
#define EGL_VG_COLORSPACE_sRGB                               0x3089
#define EGL_COLORSPACE_LINEAR                                0x308A
#define EGL_GL_COLORSPACE_LINEAR                             0x308A
#define EGL_GL_COLORSPACE_LINEAR_KHR                         0x308A
#define EGL_VG_COLORSPACE_LINEAR                             0x308A
#define EGL_ALPHA_FORMAT_NONPRE                              0x308B
#define EGL_VG_ALPHA_FORMAT_NONPRE                           0x308B
#define EGL_ALPHA_FORMAT_PRE                                 0x308C
#define EGL_VG_ALPHA_FORMAT_PRE                              0x308C
#define EGL_CLIENT_APIS                                      0x308D
#define EGL_RGB_BUFFER                                       0x308E
#define EGL_LUMINANCE_BUFFER                                 0x308F
#define EGL_HORIZONTAL_RESOLUTION                            0x3090
#define EGL_VERTICAL_RESOLUTION                              0x3091
#define EGL_PIXEL_ASPECT_RATIO                               0x3092
#define EGL_SWAP_BEHAVIOR                                    0x3093
#define EGL_BUFFER_PRESERVED                                 0x3094
#define EGL_BUFFER_DESTROYED                                 0x3095
#define EGL_OPENVG_IMAGE                                     0x3096
#define EGL_CONTEXT_CLIENT_TYPE                              0x3097
#define EGL_CONTEXT_CLIENT_VERSION                           0x3098
#define EGL_CONTEXT_MAJOR_VERSION                            0x3098
#define EGL_CONTEXT_MAJOR_VERSION_KHR                        0x3098
#define EGL_MULTISAMPLE_RESOLVE                              0x3099
#define EGL_MULTISAMPLE_RESOLVE_DEFAULT                      0x309A
#define EGL_MULTISAMPLE_RESOLVE_BOX                          0x309B
#define EGL_CL_EVENT_HANDLE                                  0x309C
#define EGL_CL_EVENT_HANDLE_KHR                              0x309C
#define EGL_GL_COLORSPACE                                    0x309D
#define EGL_GL_COLORSPACE_KHR                                0x309D
#define EGL_OPENGL_ES_API                                    0x30A0
#define EGL_OPENVG_API                                       0x30A1
#define EGL_OPENGL_API                                       0x30A2
#define EGL_NATIVE_PIXMAP_KHR                                0x30B0
#define EGL_GL_TEXTURE_2D                                    0x30B1
#define EGL_GL_TEXTURE_2D_KHR                                0x30B1
#define EGL_GL_TEXTURE_3D                                    0x30B2
#define EGL_GL_TEXTURE_3D_KHR                                0x30B2
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_X                   0x30B3
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_X_KHR               0x30B3
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X                   0x30B4
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_X_KHR               0x30B4
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Y                   0x30B5
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Y_KHR               0x30B5
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y                   0x30B6
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_KHR               0x30B6
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Z                   0x30B7
#define EGL_GL_TEXTURE_CUBE_MAP_POSITIVE_Z_KHR               0x30B7
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z                   0x30B8
#define EGL_GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_KHR               0x30B8
#define EGL_GL_RENDERBUFFER                                  0x30B9
#define EGL_GL_RENDERBUFFER_KHR                              0x30B9
#define EGL_VG_PARENT_IMAGE_KHR                              0x30BA
#define EGL_GL_TEXTURE_LEVEL                                 0x30BC
#define EGL_GL_TEXTURE_LEVEL_KHR                             0x30BC
#define EGL_GL_TEXTURE_ZOFFSET                               0x30BD
#define EGL_GL_TEXTURE_ZOFFSET_KHR                           0x30BD
#define EGL_POST_SUB_BUFFER_SUPPORTED_NV                     0x30BE
#define EGL_CONTEXT_OPENGL_ROBUST_ACCESS_EXT                 0x30BF
#define EGL_FORMAT_RGB_565_EXACT_KHR                         0x30C0
#define EGL_FORMAT_RGB_565_KHR                               0x30C1
#define EGL_FORMAT_RGBA_8888_EXACT_KHR                       0x30C2
#define EGL_FORMAT_RGBA_8888_KHR                             0x30C3
#define EGL_MAP_PRESERVE_PIXELS_KHR                          0x30C4
#define EGL_LOCK_USAGE_HINT_KHR                              0x30C5
#define EGL_BITMAP_POINTER_KHR                               0x30C6
#define EGL_BITMAP_PITCH_KHR                                 0x30C7
#define EGL_BITMAP_ORIGIN_KHR                                0x30C8
#define EGL_BITMAP_PIXEL_RED_OFFSET_KHR                      0x30C9
#define EGL_BITMAP_PIXEL_GREEN_OFFSET_KHR                    0x30CA
#define EGL_BITMAP_PIXEL_BLUE_OFFSET_KHR                     0x30CB
#define EGL_BITMAP_PIXEL_ALPHA_OFFSET_KHR                    0x30CC
#define EGL_BITMAP_PIXEL_LUMINANCE_OFFSET_KHR                0x30CD
#define EGL_LOWER_LEFT_KHR                                   0x30CE
#define EGL_UPPER_LEFT_KHR                                   0x30CF
#define EGL_IMAGE_PRESERVED                                  0x30D2
#define EGL_IMAGE_PRESERVED_KHR                              0x30D2
#define EGL_SHARED_IMAGE_NOK                                 0x30DA
#define EGL_COVERAGE_BUFFERS_NV                              0x30E0
#define EGL_COVERAGE_SAMPLES_NV                              0x30E1
#define EGL_DEPTH_ENCODING_NV                                0x30E2
#define EGL_DEPTH_ENCODING_NONLINEAR_NV                      0x30E3
#define EGL_SYNC_PRIOR_COMMANDS_COMPLETE_NV                  0x30E6
#define EGL_SYNC_STATUS_NV                                   0x30E7
#define EGL_SIGNALED_NV                                      0x30E8
#define EGL_UNSIGNALED_NV                                    0x30E9
#define EGL_ALREADY_SIGNALED_NV                              0x30EA
#define EGL_TIMEOUT_EXPIRED_NV                               0x30EB
#define EGL_CONDITION_SATISFIED_NV                           0x30EC
#define EGL_SYNC_TYPE_NV                                     0x30ED
#define EGL_SYNC_CONDITION_NV                                0x30EE
#define EGL_SYNC_FENCE_NV                                    0x30EF
#define EGL_SYNC_PRIOR_COMMANDS_COMPLETE                     0x30F0
#define EGL_SYNC_PRIOR_COMMANDS_COMPLETE_KHR                 0x30F0
#define EGL_SYNC_STATUS                                      0x30F1
#define EGL_SYNC_STATUS_KHR                                  0x30F1
#define EGL_SIGNALED                                         0x30F2
#define EGL_SIGNALED_KHR                                     0x30F2
#define EGL_UNSIGNALED                                       0x30F3
#define EGL_UNSIGNALED_KHR                                   0x30F3
#define EGL_TIMEOUT_EXPIRED                                  0x30F5
#define EGL_TIMEOUT_EXPIRED_KHR                              0x30F5
#define EGL_CONDITION_SATISFIED                              0x30F6
#define EGL_CONDITION_SATISFIED_KHR                          0x30F6
#define EGL_SYNC_TYPE                                        0x30F7
#define EGL_SYNC_TYPE_KHR                                    0x30F7
#define EGL_SYNC_CONDITION                                   0x30F8
#define EGL_SYNC_CONDITION_KHR                               0x30F8
#define EGL_SYNC_FENCE                                       0x30F9
#define EGL_SYNC_FENCE_KHR                                   0x30F9
#define EGL_SYNC_REUSABLE_KHR                                0x30FA
#define EGL_CONTEXT_MINOR_VERSION                            0x30FB
#define EGL_CONTEXT_MINOR_VERSION_KHR                        0x30FB
#define EGL_CONTEXT_FLAGS_KHR                                0x30FC
#define EGL_CONTEXT_OPENGL_PROFILE_MASK                      0x30FD
#define EGL_CONTEXT_OPENGL_PROFILE_MASK_KHR                  0x30FD
#define EGL_SYNC_CL_EVENT                                    0x30FE
#define EGL_SYNC_CL_EVENT_KHR                                0x30FE
#define EGL_SYNC_CL_EVENT_COMPLETE                           0x30FF
#define EGL_SYNC_CL_EVENT_COMPLETE_KHR                       0x30FF
#define EGL_CONTEXT_PRIORITY_LEVEL_IMG                       0x3100
#define EGL_CONTEXT_PRIORITY_HIGH_IMG                        0x3101
#define EGL_CONTEXT_PRIORITY_MEDIUM_IMG                      0x3102
#define EGL_CONTEXT_PRIORITY_LOW_IMG                         0x3103
#define EGL_NATIVE_BUFFER_MULTIPLANE_SEPARATE_IMG            0x3105
#define EGL_NATIVE_BUFFER_PLANE_OFFSET_IMG                   0x3106
#define EGL_BITMAP_PIXEL_SIZE_KHR                            0x3110
#define EGL_COVERAGE_SAMPLE_RESOLVE_NV                       0x3131
#define EGL_COVERAGE_SAMPLE_RESOLVE_DEFAULT_NV               0x3132
#define EGL_COVERAGE_SAMPLE_RESOLVE_NONE_NV                  0x3133
#define EGL_MULTIVIEW_VIEW_COUNT_EXT                         0x3134
#define EGL_AUTO_STEREO_NV                                   0x3136
#define EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_EXT   0x3138
#define EGL_BUFFER_AGE_EXT                                   0x313D
#define EGL_BUFFER_AGE_KHR                                   0x313D
#define EGL_PLATFORM_DEVICE_EXT                              0x313F
#define EGL_NATIVE_BUFFER_ANDROID                            0x3140
#define EGL_PLATFORM_ANDROID_KHR                             0x3141
#define EGL_RECORDABLE_ANDROID                               0x3142
#define EGL_NATIVE_BUFFER_USAGE_ANDROID                      0x3143
#define EGL_SYNC_NATIVE_FENCE_ANDROID                        0x3144
#define EGL_SYNC_NATIVE_FENCE_FD_ANDROID                     0x3145
#define EGL_SYNC_NATIVE_FENCE_SIGNALED_ANDROID               0x3146
#define EGL_FRAMEBUFFER_TARGET_ANDROID                       0x3147
#define EGL_FRONT_BUFFER_AUTO_REFRESH_ANDROID                0x314C
#define EGL_CONTEXT_OPENGL_DEBUG                             0x31B0
#define EGL_CONTEXT_OPENGL_FORWARD_COMPATIBLE                0x31B1
#define EGL_CONTEXT_OPENGL_ROBUST_ACCESS                     0x31B2
#define EGL_CONTEXT_OPENGL_NO_ERROR_KHR                      0x31B3
#define EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY       0x31BD
#define EGL_CONTEXT_OPENGL_RESET_NOTIFICATION_STRATEGY_KHR   0x31BD
#define EGL_NO_RESET_NOTIFICATION                            0x31BE
#define EGL_NO_RESET_NOTIFICATION_EXT                        0x31BE
#define EGL_NO_RESET_NOTIFICATION_KHR                        0x31BE
#define EGL_LOSE_CONTEXT_ON_RESET                            0x31BF
#define EGL_LOSE_CONTEXT_ON_RESET_EXT                        0x31BF
#define EGL_LOSE_CONTEXT_ON_RESET_KHR                        0x31BF
#define EGL_DRM_BUFFER_FORMAT_MESA                           0x31D0
#define EGL_DRM_BUFFER_USE_MESA                              0x31D1
#define EGL_DRM_BUFFER_FORMAT_ARGB32_MESA                    0x31D2
#define EGL_DRM_BUFFER_MESA                                  0x31D3
#define EGL_DRM_BUFFER_STRIDE_MESA                           0x31D4
#define EGL_PLATFORM_X11_EXT                                 0x31D5
#define EGL_PLATFORM_X11_KHR                                 0x31D5
#define EGL_PLATFORM_X11_SCREEN_EXT                          0x31D6
#define EGL_PLATFORM_X11_SCREEN_KHR                          0x31D6
#define EGL_PLATFORM_GBM_KHR                                 0x31D7
#define EGL_PLATFORM_GBM_MESA                                0x31D7
#define EGL_PLATFORM_WAYLAND_EXT                             0x31D8
#define EGL_PLATFORM_WAYLAND_KHR                             0x31D8
#define EGL_STREAM_FIFO_LENGTH_KHR                           0x31FC
#define EGL_STREAM_TIME_NOW_KHR                              0x31FD
#define EGL_STREAM_TIME_CONSUMER_KHR                         0x31FE
#define EGL_STREAM_TIME_PRODUCER_KHR                         0x31FF
#define EGL_D3D_TEXTURE_2D_SHARE_HANDLE_ANGLE                0x3200
#define EGL_FIXED_SIZE_ANGLE                                 0x3201
#define EGL_CONSUMER_LATENCY_USEC_KHR                        0x3210
#define EGL_PRODUCER_FRAME_KHR                               0x3212
#define EGL_CONSUMER_FRAME_KHR                               0x3213
#define EGL_STREAM_STATE_KHR                                 0x3214
#define EGL_STREAM_STATE_CREATED_KHR                         0x3215
#define EGL_STREAM_STATE_CONNECTING_KHR                      0x3216
#define EGL_STREAM_STATE_EMPTY_KHR                           0x3217
#define EGL_STREAM_STATE_NEW_FRAME_AVAILABLE_KHR             0x3218
#define EGL_STREAM_STATE_OLD_FRAME_AVAILABLE_KHR             0x3219
#define EGL_STREAM_STATE_DISCONNECTED_KHR                    0x321A
#define EGL_BAD_STREAM_KHR                                   0x321B
#define EGL_BAD_STATE_KHR                                    0x321C
#define EGL_BUFFER_COUNT_NV                                  0x321D
#define EGL_CONSUMER_ACQUIRE_TIMEOUT_USEC_KHR                0x321E
#define EGL_SYNC_NEW_FRAME_NV                                0x321F
#define EGL_BAD_DEVICE_EXT                                   0x322B
#define EGL_DEVICE_EXT                                       0x322C
#define EGL_BAD_OUTPUT_LAYER_EXT                             0x322D
#define EGL_BAD_OUTPUT_PORT_EXT                              0x322E
#define EGL_SWAP_INTERVAL_EXT                                0x322F
#define EGL_DRM_DEVICE_FILE_EXT                              0x3233
#define EGL_DRM_CRTC_EXT                                     0x3234
#define EGL_DRM_PLANE_EXT                                    0x3235
#define EGL_DRM_CONNECTOR_EXT                                0x3236
#define EGL_OPENWF_DEVICE_ID_EXT                             0x3237
#define EGL_OPENWF_PIPELINE_ID_EXT                           0x3238
#define EGL_OPENWF_PORT_ID_EXT                               0x3239
#define EGL_CUDA_DEVICE_NV                                   0x323A
#define EGL_CUDA_EVENT_HANDLE_NV                             0x323B
#define EGL_SYNC_CUDA_EVENT_NV                               0x323C
#define EGL_SYNC_CUDA_EVENT_COMPLETE_NV                      0x323D
#define EGL_MAX_STREAM_METADATA_BLOCKS_NV                    0x3250
#define EGL_MAX_STREAM_METADATA_BLOCK_SIZE_NV                0x3251
#define EGL_MAX_STREAM_METADATA_TOTAL_SIZE_NV                0x3252
#define EGL_PRODUCER_METADATA_NV                             0x3253
#define EGL_CONSUMER_METADATA_NV                             0x3254
#define EGL_METADATA0_SIZE_NV                                0x3255
#define EGL_METADATA1_SIZE_NV                                0x3256
#define EGL_METADATA2_SIZE_NV                                0x3257
#define EGL_METADATA3_SIZE_NV                                0x3258
#define EGL_METADATA0_TYPE_NV                                0x3259
#define EGL_METADATA1_TYPE_NV                                0x325A
#define EGL_METADATA2_TYPE_NV                                0x325B
#define EGL_METADATA3_TYPE_NV                                0x325C
#define EGL_LINUX_DMA_BUF_EXT                                0x3270
#define EGL_LINUX_DRM_FOURCC_EXT                             0x3271
#define EGL_DMA_BUF_PLANE0_FD_EXT                            0x3272
#define EGL_DMA_BUF_PLANE0_OFFSET_EXT                        0x3273
#define EGL_DMA_BUF_PLANE0_PITCH_EXT                         0x3274
#define EGL_DMA_BUF_PLANE1_FD_EXT                            0x3275
#define EGL_DMA_BUF_PLANE1_OFFSET_EXT                        0x3276
#define EGL_DMA_BUF_PLANE1_PITCH_EXT                         0x3277
#define EGL_DMA_BUF_PLANE2_FD_EXT                            0x3278
#define EGL_DMA_BUF_PLANE2_OFFSET_EXT                        0x3279
#define EGL_DMA_BUF_PLANE2_PITCH_EXT                         0x327A
#define EGL_YUV_COLOR_SPACE_HINT_EXT                         0x327B
#define EGL_SAMPLE_RANGE_HINT_EXT                            0x327C
#define EGL_YUV_CHROMA_HORIZONTAL_SITING_HINT_EXT            0x327D
#define EGL_YUV_CHROMA_VERTICAL_SITING_HINT_EXT              0x327E
#define EGL_ITU_REC601_EXT                                   0x327F
#define EGL_ITU_REC709_EXT                                   0x3280
#define EGL_ITU_REC2020_EXT                                  0x3281
#define EGL_YUV_FULL_RANGE_EXT                               0x3282
#define EGL_YUV_NARROW_RANGE_EXT                             0x3283
#define EGL_YUV_CHROMA_SITING_0_EXT                          0x3284
#define EGL_YUV_CHROMA_SITING_0_5_EXT                        0x3285
#define EGL_DISCARD_SAMPLES_ARM                              0x3286
#define EGL_NATIVE_BUFFER_TIZEN                              0x32A0
#define EGL_NATIVE_SURFACE_TIZEN                             0x32A1
#define EGL_PROTECTED_CONTENT_EXT                            0x32C0
#define EGL_YUV_BUFFER_EXT                                   0x3300
#define EGL_YUV_ORDER_EXT                                    0x3301
#define EGL_YUV_ORDER_YUV_EXT                                0x3302
#define EGL_YUV_ORDER_YVU_EXT                                0x3303
#define EGL_YUV_ORDER_YUYV_EXT                               0x3304
#define EGL_YUV_ORDER_UYVY_EXT                               0x3305
#define EGL_YUV_ORDER_YVYU_EXT                               0x3306
#define EGL_YUV_ORDER_VYUY_EXT                               0x3307
#define EGL_YUV_ORDER_AYUV_EXT                               0x3308
#define EGL_YUV_CSC_STANDARD_EXT                             0x330A
#define EGL_YUV_CSC_STANDARD_601_EXT                         0x330B
#define EGL_YUV_CSC_STANDARD_709_EXT                         0x330C
#define EGL_YUV_CSC_STANDARD_2020_EXT                        0x330D
#define EGL_YUV_NUMBER_OF_PLANES_EXT                         0x3311
#define EGL_YUV_SUBSAMPLE_EXT                                0x3312
#define EGL_YUV_SUBSAMPLE_4_2_0_EXT                          0x3313
#define EGL_YUV_SUBSAMPLE_4_2_2_EXT                          0x3314
#define EGL_YUV_SUBSAMPLE_4_4_4_EXT                          0x3315
#define EGL_YUV_DEPTH_RANGE_EXT                              0x3317
#define EGL_YUV_DEPTH_RANGE_LIMITED_EXT                      0x3318
#define EGL_YUV_DEPTH_RANGE_FULL_EXT                         0x3319
#define EGL_YUV_PLANE_BPP_EXT                                0x331A
#define EGL_YUV_PLANE_BPP_0_EXT                              0x331B
#define EGL_YUV_PLANE_BPP_8_EXT                              0x331C
#define EGL_YUV_PLANE_BPP_10_EXT                             0x331D
#define EGL_PENDING_METADATA_NV                              0x3328
#define EGL_YUV_PLANE0_TEXTURE_UNIT_NV                       0x332C
#define EGL_YUV_PLANE1_TEXTURE_UNIT_NV                       0x332D
#define EGL_YUV_PLANE2_TEXTURE_UNIT_NV                       0x332E
#define EGL_GENERATE_RESET_ON_VIDEO_MEMORY_PURGE_NV          0x334C
#define EGL_D3D9_DEVICE_ANGLE                                0x33A0
#define EGL_D3D11_DEVICE_ANGLE                               0x33A1
#define EGL_OBJECT_THREAD_KHR                                0x33B0
#define EGL_OBJECT_DISPLAY_KHR                               0x33B1
#define EGL_OBJECT_CONTEXT_KHR                               0x33B2
#define EGL_OBJECT_SURFACE_KHR                               0x33B3
#define EGL_OBJECT_IMAGE_KHR                                 0x33B4
#define EGL_OBJECT_SYNC_KHR                                  0x33B5
#define EGL_OBJECT_STREAM_KHR                                0x33B6
#define EGL_DEBUG_CALLBACK_KHR                               0x33B8
#define EGL_DEBUG_MSG_CRITICAL_KHR                           0x33B9
#define EGL_DEBUG_MSG_ERROR_KHR                              0x33BA
#define EGL_DEBUG_MSG_WARN_KHR                               0x33BB
#define EGL_DEBUG_MSG_INFO_KHR                               0x33BC
#define EGL_COLOR_FORMAT_HI                                  0x8F70
#define EGL_COLOR_RGB_HI                                     0x8F71
#define EGL_COLOR_RGBA_HI                                    0x8F72
#define EGL_COLOR_ARGB_HI                                    0x8F73
#define EGL_CLIENT_PIXMAP_POINTER_HI                         0x8F74
#define EGL_FOREVER                                          0xFFFFFFFFFFFFFFFF
#define EGL_FOREVER_KHR                                      0xFFFFFFFFFFFFFFFF
#define EGL_FOREVER_NV                                       0xFFFFFFFFFFFFFFFF
#define EGL_TRUE                                             1
#define EGL_DISPLAY_SCALING                                  10000

typedef EGLBoolean (GLAPIENTRY *PFNEGLBINDAPIPROC)(EGLenum api);
typedef EGLBoolean (GLAPIENTRY *PFNEGLBINDTEXIMAGEPROC)(EGLDisplay dpy, EGLSurface surface, EGLint buffer);
typedef EGLBoolean (GLAPIENTRY *PFNEGLCHOOSECONFIGPROC)(EGLDisplay dpy, const EGLint * attrib_list, EGLConfig * configs, EGLint config_size, EGLint * num_config);
typedef EGLint (GLAPIENTRY *PFNEGLCLIENTWAITSYNCPROC)(EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout);
typedef EGLint (GLAPIENTRY *PFNEGLCLIENTWAITSYNCKHRPROC)(EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);
typedef EGLint (GLAPIENTRY *PFNEGLCLIENTWAITSYNCNVPROC)(EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);
typedef EGLBoolean (GLAPIENTRY *PFNEGLCOPYBUFFERSPROC)(EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target);
typedef EGLContext (GLAPIENTRY *PFNEGLCREATECONTEXTPROC)(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint * attrib_list);
typedef EGLImageKHR (GLAPIENTRY *PFNEGLCREATEDRMIMAGEMESAPROC)(EGLDisplay dpy, const EGLint * attrib_list);
typedef EGLSyncNV (GLAPIENTRY *PFNEGLCREATEFENCESYNCNVPROC)(EGLDisplay dpy, EGLenum condition, const EGLint * attrib_list);
typedef EGLImage (GLAPIENTRY *PFNEGLCREATEIMAGEPROC)(EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLAttrib * attrib_list);
typedef EGLImageKHR (GLAPIENTRY *PFNEGLCREATEIMAGEKHRPROC)(EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint * attrib_list);
typedef EGLClientBuffer (GLAPIENTRY *PFNEGLCREATENATIVECLIENTBUFFERANDROIDPROC)(const EGLint * attrib_list);
typedef EGLSurface (GLAPIENTRY *PFNEGLCREATEPBUFFERFROMCLIENTBUFFERPROC)(EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint * attrib_list);
typedef EGLSurface (GLAPIENTRY *PFNEGLCREATEPBUFFERSURFACEPROC)(EGLDisplay dpy, EGLConfig config, const EGLint * attrib_list);
typedef EGLSurface (GLAPIENTRY *PFNEGLCREATEPIXMAPSURFACEPROC)(EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint * attrib_list);
typedef EGLSurface (GLAPIENTRY *PFNEGLCREATEPIXMAPSURFACEHIPROC)(EGLDisplay dpy, EGLConfig config, struct EGLClientPixmapHI * pixmap);
typedef EGLSurface (GLAPIENTRY *PFNEGLCREATEPLATFORMPIXMAPSURFACEPROC)(EGLDisplay dpy, EGLConfig config, void * native_pixmap, const EGLAttrib * attrib_list);
typedef EGLSurface (GLAPIENTRY *PFNEGLCREATEPLATFORMPIXMAPSURFACEEXTPROC)(EGLDisplay dpy, EGLConfig config, void * native_pixmap, const EGLint * attrib_list);
typedef EGLSurface (GLAPIENTRY *PFNEGLCREATEPLATFORMWINDOWSURFACEPROC)(EGLDisplay dpy, EGLConfig config, void * native_window, const EGLAttrib * attrib_list);
typedef EGLSurface (GLAPIENTRY *PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC)(EGLDisplay dpy, EGLConfig config, void * native_window, const EGLint * attrib_list);
typedef EGLStreamKHR (GLAPIENTRY *PFNEGLCREATESTREAMFROMFILEDESCRIPTORKHRPROC)(EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);
typedef EGLStreamKHR (GLAPIENTRY *PFNEGLCREATESTREAMKHRPROC)(EGLDisplay dpy, const EGLint * attrib_list);
typedef EGLSurface (GLAPIENTRY *PFNEGLCREATESTREAMPRODUCERSURFACEKHRPROC)(EGLDisplay dpy, EGLConfig config, EGLStreamKHR stream, const EGLint * attrib_list);
typedef EGLSyncKHR (GLAPIENTRY *PFNEGLCREATESTREAMSYNCNVPROC)(EGLDisplay dpy, EGLStreamKHR stream, EGLenum type, const EGLint * attrib_list);
typedef EGLSync (GLAPIENTRY *PFNEGLCREATESYNCPROC)(EGLDisplay dpy, EGLenum type, const EGLAttrib * attrib_list);
typedef EGLSyncKHR (GLAPIENTRY *PFNEGLCREATESYNC64KHRPROC)(EGLDisplay dpy, EGLenum type, const EGLAttribKHR * attrib_list);
typedef EGLSyncKHR (GLAPIENTRY *PFNEGLCREATESYNCKHRPROC)(EGLDisplay dpy, EGLenum type, const EGLint * attrib_list);
typedef EGLSurface (GLAPIENTRY *PFNEGLCREATEWINDOWSURFACEPROC)(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint * attrib_list);
typedef EGLint (GLAPIENTRY *PFNEGLDEBUGMESSAGECONTROLKHRPROC)(EGLDEBUGPROCKHR callback, const EGLAttrib * attrib_list);
typedef EGLBoolean (GLAPIENTRY *PFNEGLDESTROYCONTEXTPROC)(EGLDisplay dpy, EGLContext ctx);
typedef EGLBoolean (GLAPIENTRY *PFNEGLDESTROYIMAGEPROC)(EGLDisplay dpy, EGLImage image);
typedef EGLBoolean (GLAPIENTRY *PFNEGLDESTROYIMAGEKHRPROC)(EGLDisplay dpy, EGLImageKHR image);
typedef EGLBoolean (GLAPIENTRY *PFNEGLDESTROYSTREAMKHRPROC)(EGLDisplay dpy, EGLStreamKHR stream);
typedef EGLBoolean (GLAPIENTRY *PFNEGLDESTROYSURFACEPROC)(EGLDisplay dpy, EGLSurface surface);
typedef EGLBoolean (GLAPIENTRY *PFNEGLDESTROYSYNCPROC)(EGLDisplay dpy, EGLSync sync);
typedef EGLBoolean (GLAPIENTRY *PFNEGLDESTROYSYNCKHRPROC)(EGLDisplay dpy, EGLSyncKHR sync);
typedef EGLBoolean (GLAPIENTRY *PFNEGLDESTROYSYNCNVPROC)(EGLSyncNV sync);
typedef EGLint (GLAPIENTRY *PFNEGLDUPNATIVEFENCEFDANDROIDPROC)(EGLDisplay dpy, EGLSyncKHR sync);
typedef EGLBoolean (GLAPIENTRY *PFNEGLEXPORTDMABUFIMAGEMESAPROC)(EGLDisplay dpy, EGLImageKHR image, int * fds, EGLint * strides, EGLint * offsets);
typedef EGLBoolean (GLAPIENTRY *PFNEGLEXPORTDMABUFIMAGEQUERYMESAPROC)(EGLDisplay dpy, EGLImageKHR image, int * fourcc, int * num_planes, EGLuint64KHR * modifiers);
typedef EGLBoolean (GLAPIENTRY *PFNEGLEXPORTDRMIMAGEMESAPROC)(EGLDisplay dpy, EGLImageKHR image, EGLint * name, EGLint * handle, EGLint * stride);
typedef EGLBoolean (GLAPIENTRY *PFNEGLFENCENVPROC)(EGLSyncNV sync);
typedef EGLBoolean (GLAPIENTRY *PFNEGLGETCONFIGATTRIBPROC)(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint * value);
typedef EGLBoolean (GLAPIENTRY *PFNEGLGETCONFIGSPROC)(EGLDisplay dpy, EGLConfig * configs, EGLint config_size, EGLint * num_config);
typedef EGLContext (GLAPIENTRY *PFNEGLGETCURRENTCONTEXTPROC)(void);
typedef EGLDisplay (GLAPIENTRY *PFNEGLGETCURRENTDISPLAYPROC)(void);
typedef EGLSurface (GLAPIENTRY *PFNEGLGETCURRENTSURFACEPROC)(EGLint readdraw);
typedef EGLDisplay (GLAPIENTRY *PFNEGLGETDISPLAYPROC)(EGLNativeDisplayType display_id);
typedef EGLint (GLAPIENTRY *PFNEGLGETERRORPROC)(void);
typedef EGLBoolean (GLAPIENTRY *PFNEGLGETOUTPUTLAYERSEXTPROC)(EGLDisplay dpy, const EGLAttrib * attrib_list, EGLOutputLayerEXT * layers, EGLint max_layers, EGLint * num_layers);
typedef EGLBoolean (GLAPIENTRY *PFNEGLGETOUTPUTPORTSEXTPROC)(EGLDisplay dpy, const EGLAttrib * attrib_list, EGLOutputPortEXT * ports, EGLint max_ports, EGLint * num_ports);
typedef EGLDisplay (GLAPIENTRY *PFNEGLGETPLATFORMDISPLAYPROC)(EGLenum platform, void * native_display, const EGLAttrib * attrib_list);
typedef EGLDisplay (GLAPIENTRY *PFNEGLGETPLATFORMDISPLAYEXTPROC)(EGLenum platform, void * native_display, const EGLint * attrib_list);
typedef __eglMustCastToProperFunctionPointerType (GLAPIENTRY *PFNEGLGETPROCADDRESSPROC)(const char * procname);
typedef EGLNativeFileDescriptorKHR (GLAPIENTRY *PFNEGLGETSTREAMFILEDESCRIPTORKHRPROC)(EGLDisplay dpy, EGLStreamKHR stream);
typedef EGLBoolean (GLAPIENTRY *PFNEGLGETSYNCATTRIBPROC)(EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib * value);
typedef EGLBoolean (GLAPIENTRY *PFNEGLGETSYNCATTRIBKHRPROC)(EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint * value);
typedef EGLBoolean (GLAPIENTRY *PFNEGLGETSYNCATTRIBNVPROC)(EGLSyncNV sync, EGLint attribute, EGLint * value);
typedef EGLuint64NV (GLAPIENTRY *PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC)(void);
typedef EGLuint64NV (GLAPIENTRY *PFNEGLGETSYSTEMTIMENVPROC)(void);
typedef EGLBoolean (GLAPIENTRY *PFNEGLINITIALIZEPROC)(EGLDisplay dpy, EGLint * major, EGLint * minor);
typedef EGLint (GLAPIENTRY *PFNEGLLABELOBJECTKHRPROC)(EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);
typedef EGLBoolean (GLAPIENTRY *PFNEGLLOCKSURFACEKHRPROC)(EGLDisplay dpy, EGLSurface surface, const EGLint * attrib_list);
typedef EGLBoolean (GLAPIENTRY *PFNEGLMAKECURRENTPROC)(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);
typedef EGLBoolean (GLAPIENTRY *PFNEGLOUTPUTLAYERATTRIBEXTPROC)(EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib value);
typedef EGLBoolean (GLAPIENTRY *PFNEGLOUTPUTPORTATTRIBEXTPROC)(EGLDisplay dpy, EGLOutputPortEXT port, EGLint attribute, EGLAttrib value);
typedef EGLBoolean (GLAPIENTRY *PFNEGLPOSTSUBBUFFERNVPROC)(EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint width, EGLint height);
typedef EGLBoolean (GLAPIENTRY *PFNEGLPRESENTATIONTIMEANDROIDPROC)(EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID time);
typedef EGLenum (GLAPIENTRY *PFNEGLQUERYAPIPROC)(void);
typedef EGLBoolean (GLAPIENTRY *PFNEGLQUERYCONTEXTPROC)(EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint * value);
typedef EGLBoolean (GLAPIENTRY *PFNEGLQUERYDEBUGKHRPROC)(EGLint attribute, EGLAttrib * value);
typedef EGLBoolean (GLAPIENTRY *PFNEGLQUERYDEVICEATTRIBEXTPROC)(EGLDeviceEXT device, EGLint attribute, EGLAttrib * value);
typedef const char * (GLAPIENTRY *PFNEGLQUERYDEVICESTRINGEXTPROC)(EGLDeviceEXT device, EGLint name);
typedef EGLBoolean (GLAPIENTRY *PFNEGLQUERYDEVICESEXTPROC)(EGLint max_devices, EGLDeviceEXT * devices, EGLint * num_devices);
typedef EGLBoolean (GLAPIENTRY *PFNEGLQUERYDISPLAYATTRIBEXTPROC)(EGLDisplay dpy, EGLint attribute, EGLAttrib * value);
typedef EGLBoolean (GLAPIENTRY *PFNEGLQUERYDISPLAYATTRIBNVPROC)(EGLDisplay dpy, EGLint attribute, EGLAttrib * value);
typedef EGLBoolean (GLAPIENTRY *PFNEGLQUERYNATIVEDISPLAYNVPROC)(EGLDisplay dpy, EGLNativeDisplayType * display_id);
typedef EGLBoolean (GLAPIENTRY *PFNEGLQUERYNATIVEPIXMAPNVPROC)(EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType * pixmap);
typedef EGLBoolean (GLAPIENTRY *PFNEGLQUERYNATIVEWINDOWNVPROC)(EGLDisplay dpy, EGLSurface surf, EGLNativeWindowType * window);
typedef EGLBoolean (GLAPIENTRY *PFNEGLQUERYOUTPUTLAYERATTRIBEXTPROC)(EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib * value);
typedef const char * (GLAPIENTRY *PFNEGLQUERYOUTPUTLAYERSTRINGEXTPROC)(EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);
typedef EGLBoolean (GLAPIENTRY *PFNEGLQUERYOUTPUTPORTATTRIBEXTPROC)(EGLDisplay dpy, EGLOutputPortEXT port, EGLint attribute, EGLAttrib * value);
typedef const char * (GLAPIENTRY *PFNEGLQUERYOUTPUTPORTSTRINGEXTPROC)(EGLDisplay dpy, EGLOutputPortEXT port, EGLint name);
typedef EGLBoolean (GLAPIENTRY *PFNEGLQUERYSTREAMKHRPROC)(EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLint * value);
typedef EGLBoolean (GLAPIENTRY *PFNEGLQUERYSTREAMMETADATANVPROC)(EGLDisplay dpy, EGLStreamKHR stream, EGLenum name, EGLint n, EGLint offset, EGLint size, void * data);
typedef EGLBoolean (GLAPIENTRY *PFNEGLQUERYSTREAMTIMEKHRPROC)(EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLTimeKHR * value);
typedef EGLBoolean (GLAPIENTRY *PFNEGLQUERYSTREAMU64KHRPROC)(EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLuint64KHR * value);
typedef const char * (GLAPIENTRY *PFNEGLQUERYSTRINGPROC)(EGLDisplay dpy, EGLint name);
typedef EGLBoolean (GLAPIENTRY *PFNEGLQUERYSURFACEPROC)(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint * value);
typedef EGLBoolean (GLAPIENTRY *PFNEGLQUERYSURFACE64KHRPROC)(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR * value);
typedef EGLBoolean (GLAPIENTRY *PFNEGLQUERYSURFACEPOINTERANGLEPROC)(EGLDisplay dpy, EGLSurface surface, EGLint attribute, void ** value);
typedef EGLBoolean (GLAPIENTRY *PFNEGLRELEASETEXIMAGEPROC)(EGLDisplay dpy, EGLSurface surface, EGLint buffer);
typedef EGLBoolean (GLAPIENTRY *PFNEGLRELEASETHREADPROC)(void);
typedef void (GLAPIENTRY *PFNEGLSETBLOBCACHEFUNCSANDROIDPROC)(EGLDisplay dpy, EGLSetBlobFuncANDROID set, EGLGetBlobFuncANDROID get);
typedef EGLBoolean (GLAPIENTRY *PFNEGLSETDAMAGEREGIONKHRPROC)(EGLDisplay dpy, EGLSurface surface, EGLint * rects, EGLint n_rects);
typedef EGLBoolean (GLAPIENTRY *PFNEGLSETSTREAMMETADATANVPROC)(EGLDisplay dpy, EGLStreamKHR stream, EGLint n, EGLint offset, EGLint size, const void * data);
typedef EGLBoolean (GLAPIENTRY *PFNEGLSIGNALSYNCKHRPROC)(EGLDisplay dpy, EGLSyncKHR sync, EGLenum mode);
typedef EGLBoolean (GLAPIENTRY *PFNEGLSIGNALSYNCNVPROC)(EGLSyncNV sync, EGLenum mode);
typedef EGLBoolean (GLAPIENTRY *PFNEGLSTREAMATTRIBKHRPROC)(EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLint value);
typedef EGLBoolean (GLAPIENTRY *PFNEGLSTREAMCONSUMERACQUIREKHRPROC)(EGLDisplay dpy, EGLStreamKHR stream);
typedef EGLBoolean (GLAPIENTRY *PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALATTRIBSNVPROC)(EGLDisplay dpy, EGLStreamKHR stream, EGLAttrib * attrib_list);
typedef EGLBoolean (GLAPIENTRY *PFNEGLSTREAMCONSUMERGLTEXTUREEXTERNALKHRPROC)(EGLDisplay dpy, EGLStreamKHR stream);
typedef EGLBoolean (GLAPIENTRY *PFNEGLSTREAMCONSUMEROUTPUTEXTPROC)(EGLDisplay dpy, EGLStreamKHR stream, EGLOutputLayerEXT layer);
typedef EGLBoolean (GLAPIENTRY *PFNEGLSTREAMCONSUMERRELEASEKHRPROC)(EGLDisplay dpy, EGLStreamKHR stream);
typedef EGLBoolean (GLAPIENTRY *PFNEGLSURFACEATTRIBPROC)(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value);
typedef EGLBoolean (GLAPIENTRY *PFNEGLSWAPBUFFERSPROC)(EGLDisplay dpy, EGLSurface surface);
typedef EGLBoolean (GLAPIENTRY *PFNEGLSWAPBUFFERSREGION2NOKPROC)(EGLDisplay dpy, EGLSurface surface, EGLint numRects, const EGLint * rects);
typedef EGLBoolean (GLAPIENTRY *PFNEGLSWAPBUFFERSREGIONNOKPROC)(EGLDisplay dpy, EGLSurface surface, EGLint numRects, const EGLint * rects);
typedef EGLBoolean (GLAPIENTRY *PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC)(EGLDisplay dpy, EGLSurface surface, EGLint * rects, EGLint n_rects);
typedef EGLBoolean (GLAPIENTRY *PFNEGLSWAPBUFFERSWITHDAMAGEKHRPROC)(EGLDisplay dpy, EGLSurface surface, EGLint * rects, EGLint n_rects);
typedef EGLBoolean (GLAPIENTRY *PFNEGLSWAPINTERVALPROC)(EGLDisplay dpy, EGLint interval);
typedef EGLBoolean (GLAPIENTRY *PFNEGLTERMINATEPROC)(EGLDisplay dpy);
typedef EGLBoolean (GLAPIENTRY *PFNEGLUNLOCKSURFACEKHRPROC)(EGLDisplay dpy, EGLSurface surface);
typedef EGLBoolean (GLAPIENTRY *PFNEGLWAITCLIENTPROC)(void);
typedef EGLBoolean (GLAPIENTRY *PFNEGLWAITGLPROC)(void);
typedef EGLBoolean (GLAPIENTRY *PFNEGLWAITNATIVEPROC)(EGLint engine);
typedef EGLBoolean (GLAPIENTRY *PFNEGLWAITSYNCPROC)(EGLDisplay dpy, EGLSync sync, EGLint flags);
typedef EGLint (GLAPIENTRY *PFNEGLWAITSYNCKHRPROC)(EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);
GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglBindAPI(EGLenum api);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglBindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglChooseConfig(EGLDisplay dpy, const EGLint * attrib_list, EGLConfig * configs, EGLint config_size, EGLint * num_config);

GLPROXY_IMPORTEXPORT EGLint GLPROXY_CALLSPEC glproxy_eglClientWaitSync(EGLDisplay dpy, EGLSync sync, EGLint flags, EGLTime timeout);

GLPROXY_IMPORTEXPORT EGLint GLPROXY_CALLSPEC glproxy_eglClientWaitSyncKHR(EGLDisplay dpy, EGLSyncKHR sync, EGLint flags, EGLTimeKHR timeout);

GLPROXY_IMPORTEXPORT EGLint GLPROXY_CALLSPEC glproxy_eglClientWaitSyncNV(EGLSyncNV sync, EGLint flags, EGLTimeNV timeout);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglCopyBuffers(EGLDisplay dpy, EGLSurface surface, EGLNativePixmapType target);

GLPROXY_IMPORTEXPORT EGLContext GLPROXY_CALLSPEC glproxy_eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint * attrib_list);

GLPROXY_IMPORTEXPORT EGLImageKHR GLPROXY_CALLSPEC glproxy_eglCreateDRMImageMESA(EGLDisplay dpy, const EGLint * attrib_list);

GLPROXY_IMPORTEXPORT EGLSyncNV GLPROXY_CALLSPEC glproxy_eglCreateFenceSyncNV(EGLDisplay dpy, EGLenum condition, const EGLint * attrib_list);

GLPROXY_IMPORTEXPORT EGLImage GLPROXY_CALLSPEC glproxy_eglCreateImage(EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLAttrib * attrib_list);

GLPROXY_IMPORTEXPORT EGLImageKHR GLPROXY_CALLSPEC glproxy_eglCreateImageKHR(EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint * attrib_list);

GLPROXY_IMPORTEXPORT EGLClientBuffer GLPROXY_CALLSPEC glproxy_eglCreateNativeClientBufferANDROID(const EGLint * attrib_list);

GLPROXY_IMPORTEXPORT EGLSurface GLPROXY_CALLSPEC glproxy_eglCreatePbufferFromClientBuffer(EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint * attrib_list);

GLPROXY_IMPORTEXPORT EGLSurface GLPROXY_CALLSPEC glproxy_eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint * attrib_list);

GLPROXY_IMPORTEXPORT EGLSurface GLPROXY_CALLSPEC glproxy_eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config, EGLNativePixmapType pixmap, const EGLint * attrib_list);

GLPROXY_IMPORTEXPORT EGLSurface GLPROXY_CALLSPEC glproxy_eglCreatePixmapSurfaceHI(EGLDisplay dpy, EGLConfig config, struct EGLClientPixmapHI * pixmap);

GLPROXY_IMPORTEXPORT EGLSurface GLPROXY_CALLSPEC glproxy_eglCreatePlatformPixmapSurface(EGLDisplay dpy, EGLConfig config, void * native_pixmap, const EGLAttrib * attrib_list);

GLPROXY_IMPORTEXPORT EGLSurface GLPROXY_CALLSPEC glproxy_eglCreatePlatformPixmapSurfaceEXT(EGLDisplay dpy, EGLConfig config, void * native_pixmap, const EGLint * attrib_list);

GLPROXY_IMPORTEXPORT EGLSurface GLPROXY_CALLSPEC glproxy_eglCreatePlatformWindowSurface(EGLDisplay dpy, EGLConfig config, void * native_window, const EGLAttrib * attrib_list);

GLPROXY_IMPORTEXPORT EGLSurface GLPROXY_CALLSPEC glproxy_eglCreatePlatformWindowSurfaceEXT(EGLDisplay dpy, EGLConfig config, void * native_window, const EGLint * attrib_list);

GLPROXY_IMPORTEXPORT EGLStreamKHR GLPROXY_CALLSPEC glproxy_eglCreateStreamFromFileDescriptorKHR(EGLDisplay dpy, EGLNativeFileDescriptorKHR file_descriptor);

GLPROXY_IMPORTEXPORT EGLStreamKHR GLPROXY_CALLSPEC glproxy_eglCreateStreamKHR(EGLDisplay dpy, const EGLint * attrib_list);

GLPROXY_IMPORTEXPORT EGLSurface GLPROXY_CALLSPEC glproxy_eglCreateStreamProducerSurfaceKHR(EGLDisplay dpy, EGLConfig config, EGLStreamKHR stream, const EGLint * attrib_list);

GLPROXY_IMPORTEXPORT EGLSyncKHR GLPROXY_CALLSPEC glproxy_eglCreateStreamSyncNV(EGLDisplay dpy, EGLStreamKHR stream, EGLenum type, const EGLint * attrib_list);

GLPROXY_IMPORTEXPORT EGLSync GLPROXY_CALLSPEC glproxy_eglCreateSync(EGLDisplay dpy, EGLenum type, const EGLAttrib * attrib_list);

GLPROXY_IMPORTEXPORT EGLSyncKHR GLPROXY_CALLSPEC glproxy_eglCreateSync64KHR(EGLDisplay dpy, EGLenum type, const EGLAttribKHR * attrib_list);

GLPROXY_IMPORTEXPORT EGLSyncKHR GLPROXY_CALLSPEC glproxy_eglCreateSyncKHR(EGLDisplay dpy, EGLenum type, const EGLint * attrib_list);

GLPROXY_IMPORTEXPORT EGLSurface GLPROXY_CALLSPEC glproxy_eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, EGLNativeWindowType win, const EGLint * attrib_list);

GLPROXY_IMPORTEXPORT EGLint GLPROXY_CALLSPEC glproxy_eglDebugMessageControlKHR(EGLDEBUGPROCKHR callback, const EGLAttrib * attrib_list);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglDestroyContext(EGLDisplay dpy, EGLContext ctx);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglDestroyImage(EGLDisplay dpy, EGLImage image);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglDestroyImageKHR(EGLDisplay dpy, EGLImageKHR image);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglDestroyStreamKHR(EGLDisplay dpy, EGLStreamKHR stream);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglDestroySurface(EGLDisplay dpy, EGLSurface surface);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglDestroySync(EGLDisplay dpy, EGLSync sync);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglDestroySyncKHR(EGLDisplay dpy, EGLSyncKHR sync);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglDestroySyncNV(EGLSyncNV sync);

GLPROXY_IMPORTEXPORT EGLint GLPROXY_CALLSPEC glproxy_eglDupNativeFenceFDANDROID(EGLDisplay dpy, EGLSyncKHR sync);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglExportDMABUFImageMESA(EGLDisplay dpy, EGLImageKHR image, int * fds, EGLint * strides, EGLint * offsets);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglExportDMABUFImageQueryMESA(EGLDisplay dpy, EGLImageKHR image, int * fourcc, int * num_planes, EGLuint64KHR * modifiers);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglExportDRMImageMESA(EGLDisplay dpy, EGLImageKHR image, EGLint * name, EGLint * handle, EGLint * stride);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglFenceNV(EGLSyncNV sync);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint * value);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglGetConfigs(EGLDisplay dpy, EGLConfig * configs, EGLint config_size, EGLint * num_config);

GLPROXY_IMPORTEXPORT EGLContext GLPROXY_CALLSPEC glproxy_eglGetCurrentContext(void);

GLPROXY_IMPORTEXPORT EGLDisplay GLPROXY_CALLSPEC glproxy_eglGetCurrentDisplay(void);

GLPROXY_IMPORTEXPORT EGLSurface GLPROXY_CALLSPEC glproxy_eglGetCurrentSurface(EGLint readdraw);

GLPROXY_IMPORTEXPORT EGLDisplay GLPROXY_CALLSPEC glproxy_eglGetDisplay(EGLNativeDisplayType display_id);

GLPROXY_IMPORTEXPORT EGLint GLPROXY_CALLSPEC glproxy_eglGetError(void);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglGetOutputLayersEXT(EGLDisplay dpy, const EGLAttrib * attrib_list, EGLOutputLayerEXT * layers, EGLint max_layers, EGLint * num_layers);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglGetOutputPortsEXT(EGLDisplay dpy, const EGLAttrib * attrib_list, EGLOutputPortEXT * ports, EGLint max_ports, EGLint * num_ports);

GLPROXY_IMPORTEXPORT EGLDisplay GLPROXY_CALLSPEC glproxy_eglGetPlatformDisplay(EGLenum platform, void * native_display, const EGLAttrib * attrib_list);

GLPROXY_IMPORTEXPORT EGLDisplay GLPROXY_CALLSPEC glproxy_eglGetPlatformDisplayEXT(EGLenum platform, void * native_display, const EGLint * attrib_list);

GLPROXY_IMPORTEXPORT __eglMustCastToProperFunctionPointerType GLPROXY_CALLSPEC glproxy_eglGetProcAddress(const char * procname);

GLPROXY_IMPORTEXPORT EGLNativeFileDescriptorKHR GLPROXY_CALLSPEC glproxy_eglGetStreamFileDescriptorKHR(EGLDisplay dpy, EGLStreamKHR stream);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglGetSyncAttrib(EGLDisplay dpy, EGLSync sync, EGLint attribute, EGLAttrib * value);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglGetSyncAttribKHR(EGLDisplay dpy, EGLSyncKHR sync, EGLint attribute, EGLint * value);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglGetSyncAttribNV(EGLSyncNV sync, EGLint attribute, EGLint * value);

GLPROXY_IMPORTEXPORT EGLuint64NV GLPROXY_CALLSPEC glproxy_eglGetSystemTimeFrequencyNV(void);

GLPROXY_IMPORTEXPORT EGLuint64NV GLPROXY_CALLSPEC glproxy_eglGetSystemTimeNV(void);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglInitialize(EGLDisplay dpy, EGLint * major, EGLint * minor);

GLPROXY_IMPORTEXPORT EGLint GLPROXY_CALLSPEC glproxy_eglLabelObjectKHR(EGLDisplay display, EGLenum objectType, EGLObjectKHR object, EGLLabelKHR label);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglLockSurfaceKHR(EGLDisplay dpy, EGLSurface surface, const EGLint * attrib_list);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglOutputLayerAttribEXT(EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib value);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglOutputPortAttribEXT(EGLDisplay dpy, EGLOutputPortEXT port, EGLint attribute, EGLAttrib value);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglPostSubBufferNV(EGLDisplay dpy, EGLSurface surface, EGLint x, EGLint y, EGLint width, EGLint height);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglPresentationTimeANDROID(EGLDisplay dpy, EGLSurface surface, EGLnsecsANDROID time);

GLPROXY_IMPORTEXPORT EGLenum GLPROXY_CALLSPEC glproxy_eglQueryAPI(void);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglQueryContext(EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint * value);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglQueryDebugKHR(EGLint attribute, EGLAttrib * value);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglQueryDeviceAttribEXT(EGLDeviceEXT device, EGLint attribute, EGLAttrib * value);

GLPROXY_IMPORTEXPORT const char * GLPROXY_CALLSPEC glproxy_eglQueryDeviceStringEXT(EGLDeviceEXT device, EGLint name);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglQueryDevicesEXT(EGLint max_devices, EGLDeviceEXT * devices, EGLint * num_devices);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglQueryDisplayAttribEXT(EGLDisplay dpy, EGLint attribute, EGLAttrib * value);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglQueryDisplayAttribNV(EGLDisplay dpy, EGLint attribute, EGLAttrib * value);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglQueryNativeDisplayNV(EGLDisplay dpy, EGLNativeDisplayType * display_id);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglQueryNativePixmapNV(EGLDisplay dpy, EGLSurface surf, EGLNativePixmapType * pixmap);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglQueryNativeWindowNV(EGLDisplay dpy, EGLSurface surf, EGLNativeWindowType * window);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglQueryOutputLayerAttribEXT(EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint attribute, EGLAttrib * value);

GLPROXY_IMPORTEXPORT const char * GLPROXY_CALLSPEC glproxy_eglQueryOutputLayerStringEXT(EGLDisplay dpy, EGLOutputLayerEXT layer, EGLint name);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglQueryOutputPortAttribEXT(EGLDisplay dpy, EGLOutputPortEXT port, EGLint attribute, EGLAttrib * value);

GLPROXY_IMPORTEXPORT const char * GLPROXY_CALLSPEC glproxy_eglQueryOutputPortStringEXT(EGLDisplay dpy, EGLOutputPortEXT port, EGLint name);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglQueryStreamKHR(EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLint * value);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglQueryStreamMetadataNV(EGLDisplay dpy, EGLStreamKHR stream, EGLenum name, EGLint n, EGLint offset, EGLint size, void * data);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglQueryStreamTimeKHR(EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLTimeKHR * value);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglQueryStreamu64KHR(EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLuint64KHR * value);

GLPROXY_IMPORTEXPORT const char * GLPROXY_CALLSPEC glproxy_eglQueryString(EGLDisplay dpy, EGLint name);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglQuerySurface(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint * value);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglQuerySurface64KHR(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLAttribKHR * value);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglQuerySurfacePointerANGLE(EGLDisplay dpy, EGLSurface surface, EGLint attribute, void ** value);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglReleaseThread(void);

GLPROXY_IMPORTEXPORT void GLPROXY_CALLSPEC glproxy_eglSetBlobCacheFuncsANDROID(EGLDisplay dpy, EGLSetBlobFuncANDROID set, EGLGetBlobFuncANDROID get);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglSetDamageRegionKHR(EGLDisplay dpy, EGLSurface surface, EGLint * rects, EGLint n_rects);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglSetStreamMetadataNV(EGLDisplay dpy, EGLStreamKHR stream, EGLint n, EGLint offset, EGLint size, const void * data);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglSignalSyncKHR(EGLDisplay dpy, EGLSyncKHR sync, EGLenum mode);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglSignalSyncNV(EGLSyncNV sync, EGLenum mode);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglStreamAttribKHR(EGLDisplay dpy, EGLStreamKHR stream, EGLenum attribute, EGLint value);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglStreamConsumerAcquireKHR(EGLDisplay dpy, EGLStreamKHR stream);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglStreamConsumerGLTextureExternalAttribsNV(EGLDisplay dpy, EGLStreamKHR stream, EGLAttrib * attrib_list);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglStreamConsumerGLTextureExternalKHR(EGLDisplay dpy, EGLStreamKHR stream);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglStreamConsumerOutputEXT(EGLDisplay dpy, EGLStreamKHR stream, EGLOutputLayerEXT layer);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglStreamConsumerReleaseKHR(EGLDisplay dpy, EGLStreamKHR stream);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglSwapBuffersRegion2NOK(EGLDisplay dpy, EGLSurface surface, EGLint numRects, const EGLint * rects);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglSwapBuffersRegionNOK(EGLDisplay dpy, EGLSurface surface, EGLint numRects, const EGLint * rects);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglSwapBuffersWithDamageEXT(EGLDisplay dpy, EGLSurface surface, EGLint * rects, EGLint n_rects);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglSwapBuffersWithDamageKHR(EGLDisplay dpy, EGLSurface surface, EGLint * rects, EGLint n_rects);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglSwapInterval(EGLDisplay dpy, EGLint interval);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglTerminate(EGLDisplay dpy);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglUnlockSurfaceKHR(EGLDisplay dpy, EGLSurface surface);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglWaitClient(void);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglWaitGL(void);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglWaitNative(EGLint engine);

GLPROXY_IMPORTEXPORT EGLBoolean GLPROXY_CALLSPEC glproxy_eglWaitSync(EGLDisplay dpy, EGLSync sync, EGLint flags);

GLPROXY_IMPORTEXPORT EGLint GLPROXY_CALLSPEC glproxy_eglWaitSyncKHR(EGLDisplay dpy, EGLSyncKHR sync, EGLint flags);

#define eglBindAPI glproxy_eglBindAPI
#define eglBindTexImage glproxy_eglBindTexImage
#define eglChooseConfig glproxy_eglChooseConfig
#define eglClientWaitSync glproxy_eglClientWaitSync
#define eglClientWaitSyncKHR glproxy_eglClientWaitSyncKHR
#define eglClientWaitSyncNV glproxy_eglClientWaitSyncNV
#define eglCopyBuffers glproxy_eglCopyBuffers
#define eglCreateContext glproxy_eglCreateContext
#define eglCreateDRMImageMESA glproxy_eglCreateDRMImageMESA
#define eglCreateFenceSyncNV glproxy_eglCreateFenceSyncNV
#define eglCreateImage glproxy_eglCreateImage
#define eglCreateImageKHR glproxy_eglCreateImageKHR
#define eglCreateNativeClientBufferANDROID glproxy_eglCreateNativeClientBufferANDROID
#define eglCreatePbufferFromClientBuffer glproxy_eglCreatePbufferFromClientBuffer
#define eglCreatePbufferSurface glproxy_eglCreatePbufferSurface
#define eglCreatePixmapSurface glproxy_eglCreatePixmapSurface
#define eglCreatePixmapSurfaceHI glproxy_eglCreatePixmapSurfaceHI
#define eglCreatePlatformPixmapSurface glproxy_eglCreatePlatformPixmapSurface
#define eglCreatePlatformPixmapSurfaceEXT glproxy_eglCreatePlatformPixmapSurfaceEXT
#define eglCreatePlatformWindowSurface glproxy_eglCreatePlatformWindowSurface
#define eglCreatePlatformWindowSurfaceEXT glproxy_eglCreatePlatformWindowSurfaceEXT
#define eglCreateStreamFromFileDescriptorKHR glproxy_eglCreateStreamFromFileDescriptorKHR
#define eglCreateStreamKHR glproxy_eglCreateStreamKHR
#define eglCreateStreamProducerSurfaceKHR glproxy_eglCreateStreamProducerSurfaceKHR
#define eglCreateStreamSyncNV glproxy_eglCreateStreamSyncNV
#define eglCreateSync glproxy_eglCreateSync
#define eglCreateSync64KHR glproxy_eglCreateSync64KHR
#define eglCreateSyncKHR glproxy_eglCreateSyncKHR
#define eglCreateWindowSurface glproxy_eglCreateWindowSurface
#define eglDebugMessageControlKHR glproxy_eglDebugMessageControlKHR
#define eglDestroyContext glproxy_eglDestroyContext
#define eglDestroyImage glproxy_eglDestroyImage
#define eglDestroyImageKHR glproxy_eglDestroyImageKHR
#define eglDestroyStreamKHR glproxy_eglDestroyStreamKHR
#define eglDestroySurface glproxy_eglDestroySurface
#define eglDestroySync glproxy_eglDestroySync
#define eglDestroySyncKHR glproxy_eglDestroySyncKHR
#define eglDestroySyncNV glproxy_eglDestroySyncNV
#define eglDupNativeFenceFDANDROID glproxy_eglDupNativeFenceFDANDROID
#define eglExportDMABUFImageMESA glproxy_eglExportDMABUFImageMESA
#define eglExportDMABUFImageQueryMESA glproxy_eglExportDMABUFImageQueryMESA
#define eglExportDRMImageMESA glproxy_eglExportDRMImageMESA
#define eglFenceNV glproxy_eglFenceNV
#define eglGetConfigAttrib glproxy_eglGetConfigAttrib
#define eglGetConfigs glproxy_eglGetConfigs
#define eglGetCurrentContext glproxy_eglGetCurrentContext
#define eglGetCurrentDisplay glproxy_eglGetCurrentDisplay
#define eglGetCurrentSurface glproxy_eglGetCurrentSurface
#define eglGetDisplay glproxy_eglGetDisplay
#define eglGetError glproxy_eglGetError
#define eglGetOutputLayersEXT glproxy_eglGetOutputLayersEXT
#define eglGetOutputPortsEXT glproxy_eglGetOutputPortsEXT
#define eglGetPlatformDisplay glproxy_eglGetPlatformDisplay
#define eglGetPlatformDisplayEXT glproxy_eglGetPlatformDisplayEXT
#define eglGetProcAddress glproxy_eglGetProcAddress
#define eglGetStreamFileDescriptorKHR glproxy_eglGetStreamFileDescriptorKHR
#define eglGetSyncAttrib glproxy_eglGetSyncAttrib
#define eglGetSyncAttribKHR glproxy_eglGetSyncAttribKHR
#define eglGetSyncAttribNV glproxy_eglGetSyncAttribNV
#define eglGetSystemTimeFrequencyNV glproxy_eglGetSystemTimeFrequencyNV
#define eglGetSystemTimeNV glproxy_eglGetSystemTimeNV
#define eglInitialize glproxy_eglInitialize
#define eglLabelObjectKHR glproxy_eglLabelObjectKHR
#define eglLockSurfaceKHR glproxy_eglLockSurfaceKHR
#define eglMakeCurrent glproxy_eglMakeCurrent
#define eglOutputLayerAttribEXT glproxy_eglOutputLayerAttribEXT
#define eglOutputPortAttribEXT glproxy_eglOutputPortAttribEXT
#define eglPostSubBufferNV glproxy_eglPostSubBufferNV
#define eglPresentationTimeANDROID glproxy_eglPresentationTimeANDROID
#define eglQueryAPI glproxy_eglQueryAPI
#define eglQueryContext glproxy_eglQueryContext
#define eglQueryDebugKHR glproxy_eglQueryDebugKHR
#define eglQueryDeviceAttribEXT glproxy_eglQueryDeviceAttribEXT
#define eglQueryDeviceStringEXT glproxy_eglQueryDeviceStringEXT
#define eglQueryDevicesEXT glproxy_eglQueryDevicesEXT
#define eglQueryDisplayAttribEXT glproxy_eglQueryDisplayAttribEXT
#define eglQueryDisplayAttribNV glproxy_eglQueryDisplayAttribNV
#define eglQueryNativeDisplayNV glproxy_eglQueryNativeDisplayNV
#define eglQueryNativePixmapNV glproxy_eglQueryNativePixmapNV
#define eglQueryNativeWindowNV glproxy_eglQueryNativeWindowNV
#define eglQueryOutputLayerAttribEXT glproxy_eglQueryOutputLayerAttribEXT
#define eglQueryOutputLayerStringEXT glproxy_eglQueryOutputLayerStringEXT
#define eglQueryOutputPortAttribEXT glproxy_eglQueryOutputPortAttribEXT
#define eglQueryOutputPortStringEXT glproxy_eglQueryOutputPortStringEXT
#define eglQueryStreamKHR glproxy_eglQueryStreamKHR
#define eglQueryStreamMetadataNV glproxy_eglQueryStreamMetadataNV
#define eglQueryStreamTimeKHR glproxy_eglQueryStreamTimeKHR
#define eglQueryStreamu64KHR glproxy_eglQueryStreamu64KHR
#define eglQueryString glproxy_eglQueryString
#define eglQuerySurface glproxy_eglQuerySurface
#define eglQuerySurface64KHR glproxy_eglQuerySurface64KHR
#define eglQuerySurfacePointerANGLE glproxy_eglQuerySurfacePointerANGLE
#define eglReleaseTexImage glproxy_eglReleaseTexImage
#define eglReleaseThread glproxy_eglReleaseThread
#define eglSetBlobCacheFuncsANDROID glproxy_eglSetBlobCacheFuncsANDROID
#define eglSetDamageRegionKHR glproxy_eglSetDamageRegionKHR
#define eglSetStreamMetadataNV glproxy_eglSetStreamMetadataNV
#define eglSignalSyncKHR glproxy_eglSignalSyncKHR
#define eglSignalSyncNV glproxy_eglSignalSyncNV
#define eglStreamAttribKHR glproxy_eglStreamAttribKHR
#define eglStreamConsumerAcquireKHR glproxy_eglStreamConsumerAcquireKHR
#define eglStreamConsumerGLTextureExternalAttribsNV glproxy_eglStreamConsumerGLTextureExternalAttribsNV
#define eglStreamConsumerGLTextureExternalKHR glproxy_eglStreamConsumerGLTextureExternalKHR
#define eglStreamConsumerOutputEXT glproxy_eglStreamConsumerOutputEXT
#define eglStreamConsumerReleaseKHR glproxy_eglStreamConsumerReleaseKHR
#define eglSurfaceAttrib glproxy_eglSurfaceAttrib
#define eglSwapBuffers glproxy_eglSwapBuffers
#define eglSwapBuffersRegion2NOK glproxy_eglSwapBuffersRegion2NOK
#define eglSwapBuffersRegionNOK glproxy_eglSwapBuffersRegionNOK
#define eglSwapBuffersWithDamageEXT glproxy_eglSwapBuffersWithDamageEXT
#define eglSwapBuffersWithDamageKHR glproxy_eglSwapBuffersWithDamageKHR
#define eglSwapInterval glproxy_eglSwapInterval
#define eglTerminate glproxy_eglTerminate
#define eglUnlockSurfaceKHR glproxy_eglUnlockSurfaceKHR
#define eglWaitClient glproxy_eglWaitClient
#define eglWaitGL glproxy_eglWaitGL
#define eglWaitNative glproxy_eglWaitNative
#define eglWaitSync glproxy_eglWaitSync
#define eglWaitSyncKHR glproxy_eglWaitSyncKHR

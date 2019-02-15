/* GL dispatch header.
 * This is code-generated from the GL API XML files from Khronos.
 */

#pragma once
#include <stddef.h>

struct _GPU_DEVICE {
    DWORD  cb;
    CHAR   DeviceName[32];
    CHAR   DeviceString[128];
    DWORD  Flags;
    RECT   rcVirtualScreen;
};
DECLARE_HANDLE(HPBUFFERARB);
DECLARE_HANDLE(HPBUFFEREXT);
DECLARE_HANDLE(HVIDEOOUTPUTDEVICENV);
DECLARE_HANDLE(HPVIDEODEV);
DECLARE_HANDLE(HPGPUNV);
DECLARE_HANDLE(HGPUNV);
DECLARE_HANDLE(HVIDEOINPUTDEVICENV);
typedef struct _GPU_DEVICE GPU_DEVICE;
typedef struct _GPU_DEVICE *PGPU_DEVICE;

#define WGL_VERSION_1_0 1

#define WGL_3DFX_multisample 1
#define WGL_3DL_stereo_control 1
#define WGL_AMD_gpu_association 1
#define WGL_ARB_buffer_region 1
#define WGL_ARB_context_flush_control 1
#define WGL_ARB_create_context 1
#define WGL_ARB_create_context_profile 1
#define WGL_ARB_create_context_robustness 1
#define WGL_ARB_extensions_string 1
#define WGL_ARB_framebuffer_sRGB 1
#define WGL_ARB_make_current_read 1
#define WGL_ARB_multisample 1
#define WGL_ARB_pbuffer 1
#define WGL_ARB_pixel_format 1
#define WGL_ARB_pixel_format_float 1
#define WGL_ARB_render_texture 1
#define WGL_ARB_robustness_application_isolation 1
#define WGL_ARB_robustness_share_group_isolation 1
#define WGL_ATI_pixel_format_float 1
#define WGL_EXT_create_context_es2_profile 1
#define WGL_EXT_create_context_es_profile 1
#define WGL_EXT_depth_float 1
#define WGL_EXT_display_color_table 1
#define WGL_EXT_extensions_string 1
#define WGL_EXT_framebuffer_sRGB 1
#define WGL_EXT_make_current_read 1
#define WGL_EXT_multisample 1
#define WGL_EXT_pbuffer 1
#define WGL_EXT_pixel_format 1
#define WGL_EXT_pixel_format_packed_float 1
#define WGL_EXT_swap_control 1
#define WGL_EXT_swap_control_tear 1
#define WGL_I3D_digital_video_control 1
#define WGL_I3D_gamma 1
#define WGL_I3D_genlock 1
#define WGL_I3D_image_buffer 1
#define WGL_I3D_swap_frame_lock 1
#define WGL_I3D_swap_frame_usage 1
#define WGL_NV_DX_interop 1
#define WGL_NV_DX_interop2 1
#define WGL_NV_copy_image 1
#define WGL_NV_delay_before_swap 1
#define WGL_NV_float_buffer 1
#define WGL_NV_gpu_affinity 1
#define WGL_NV_multisample_coverage 1
#define WGL_NV_present_video 1
#define WGL_NV_render_depth_texture 1
#define WGL_NV_render_texture_rectangle 1
#define WGL_NV_swap_group 1
#define WGL_NV_vertex_array_range 1
#define WGL_NV_video_capture 1
#define WGL_NV_video_output 1
#define WGL_OML_sync_control 1

#define WGL_CONTEXT_RELEASE_BEHAVIOR_NONE_ARB            0
#define WGL_FONT_LINES                                   0
#define WGL_ACCESS_READ_ONLY_NV                          0x00000000
#define WGL_ACCESS_READ_WRITE_NV                         0x00000001
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB                 0x00000001
#define WGL_CONTEXT_DEBUG_BIT_ARB                        0x00000001
#define WGL_FRONT_COLOR_BUFFER_BIT_ARB                   0x00000001
#define WGL_IMAGE_BUFFER_MIN_ACCESS_I3D                  0x00000001
#define WGL_ACCESS_WRITE_DISCARD_NV                      0x00000002
#define WGL_BACK_COLOR_BUFFER_BIT_ARB                    0x00000002
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB        0x00000002
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB           0x00000002
#define WGL_IMAGE_BUFFER_LOCK_I3D                        0x00000002
#define WGL_CONTEXT_ES2_PROFILE_BIT_EXT                  0x00000004
#define WGL_CONTEXT_ES_PROFILE_BIT_EXT                   0x00000004
#define WGL_CONTEXT_ROBUST_ACCESS_BIT_ARB                0x00000004
#define WGL_DEPTH_BUFFER_BIT_ARB                         0x00000004
#define WGL_CONTEXT_RESET_ISOLATION_BIT_ARB              0x00000008
#define WGL_STENCIL_BUFFER_BIT_ARB                       0x00000008
#define WGL_GPU_VENDOR_AMD                               0x1F00
#define WGL_GPU_RENDERER_STRING_AMD                      0x1F01
#define WGL_GPU_OPENGL_VERSION_STRING_AMD                0x1F02
#define WGL_NUMBER_PIXEL_FORMATS_ARB                     0x2000
#define WGL_NUMBER_PIXEL_FORMATS_EXT                     0x2000
#define WGL_DRAW_TO_WINDOW_ARB                           0x2001
#define WGL_DRAW_TO_WINDOW_EXT                           0x2001
#define WGL_DRAW_TO_BITMAP_ARB                           0x2002
#define WGL_DRAW_TO_BITMAP_EXT                           0x2002
#define WGL_ACCELERATION_ARB                             0x2003
#define WGL_ACCELERATION_EXT                             0x2003
#define WGL_NEED_PALETTE_ARB                             0x2004
#define WGL_NEED_PALETTE_EXT                             0x2004
#define WGL_NEED_SYSTEM_PALETTE_ARB                      0x2005
#define WGL_NEED_SYSTEM_PALETTE_EXT                      0x2005
#define WGL_SWAP_LAYER_BUFFERS_ARB                       0x2006
#define WGL_SWAP_LAYER_BUFFERS_EXT                       0x2006
#define WGL_SWAP_METHOD_ARB                              0x2007
#define WGL_SWAP_METHOD_EXT                              0x2007
#define WGL_NUMBER_OVERLAYS_ARB                          0x2008
#define WGL_NUMBER_OVERLAYS_EXT                          0x2008
#define WGL_NUMBER_UNDERLAYS_ARB                         0x2009
#define WGL_NUMBER_UNDERLAYS_EXT                         0x2009
#define WGL_TRANSPARENT_ARB                              0x200A
#define WGL_TRANSPARENT_EXT                              0x200A
#define WGL_TRANSPARENT_VALUE_EXT                        0x200B
#define WGL_SHARE_DEPTH_ARB                              0x200C
#define WGL_SHARE_DEPTH_EXT                              0x200C
#define WGL_SHARE_STENCIL_ARB                            0x200D
#define WGL_SHARE_STENCIL_EXT                            0x200D
#define WGL_SHARE_ACCUM_ARB                              0x200E
#define WGL_SHARE_ACCUM_EXT                              0x200E
#define WGL_SUPPORT_GDI_ARB                              0x200F
#define WGL_SUPPORT_GDI_EXT                              0x200F
#define WGL_SUPPORT_OPENGL_ARB                           0x2010
#define WGL_SUPPORT_OPENGL_EXT                           0x2010
#define WGL_DOUBLE_BUFFER_ARB                            0x2011
#define WGL_DOUBLE_BUFFER_EXT                            0x2011
#define WGL_STEREO_ARB                                   0x2012
#define WGL_STEREO_EXT                                   0x2012
#define WGL_PIXEL_TYPE_ARB                               0x2013
#define WGL_PIXEL_TYPE_EXT                               0x2013
#define WGL_COLOR_BITS_ARB                               0x2014
#define WGL_COLOR_BITS_EXT                               0x2014
#define WGL_RED_BITS_ARB                                 0x2015
#define WGL_RED_BITS_EXT                                 0x2015
#define WGL_RED_SHIFT_ARB                                0x2016
#define WGL_RED_SHIFT_EXT                                0x2016
#define WGL_GREEN_BITS_ARB                               0x2017
#define WGL_GREEN_BITS_EXT                               0x2017
#define WGL_GREEN_SHIFT_ARB                              0x2018
#define WGL_GREEN_SHIFT_EXT                              0x2018
#define WGL_BLUE_BITS_ARB                                0x2019
#define WGL_BLUE_BITS_EXT                                0x2019
#define WGL_BLUE_SHIFT_ARB                               0x201A
#define WGL_BLUE_SHIFT_EXT                               0x201A
#define WGL_ALPHA_BITS_ARB                               0x201B
#define WGL_ALPHA_BITS_EXT                               0x201B
#define WGL_ALPHA_SHIFT_ARB                              0x201C
#define WGL_ALPHA_SHIFT_EXT                              0x201C
#define WGL_ACCUM_BITS_ARB                               0x201D
#define WGL_ACCUM_BITS_EXT                               0x201D
#define WGL_ACCUM_RED_BITS_ARB                           0x201E
#define WGL_ACCUM_RED_BITS_EXT                           0x201E
#define WGL_ACCUM_GREEN_BITS_ARB                         0x201F
#define WGL_ACCUM_GREEN_BITS_EXT                         0x201F
#define WGL_ACCUM_BLUE_BITS_ARB                          0x2020
#define WGL_ACCUM_BLUE_BITS_EXT                          0x2020
#define WGL_ACCUM_ALPHA_BITS_ARB                         0x2021
#define WGL_ACCUM_ALPHA_BITS_EXT                         0x2021
#define WGL_DEPTH_BITS_ARB                               0x2022
#define WGL_DEPTH_BITS_EXT                               0x2022
#define WGL_STENCIL_BITS_ARB                             0x2023
#define WGL_STENCIL_BITS_EXT                             0x2023
#define WGL_AUX_BUFFERS_ARB                              0x2024
#define WGL_AUX_BUFFERS_EXT                              0x2024
#define WGL_NO_ACCELERATION_ARB                          0x2025
#define WGL_NO_ACCELERATION_EXT                          0x2025
#define WGL_GENERIC_ACCELERATION_ARB                     0x2026
#define WGL_GENERIC_ACCELERATION_EXT                     0x2026
#define WGL_FULL_ACCELERATION_ARB                        0x2027
#define WGL_FULL_ACCELERATION_EXT                        0x2027
#define WGL_SWAP_EXCHANGE_ARB                            0x2028
#define WGL_SWAP_EXCHANGE_EXT                            0x2028
#define WGL_SWAP_COPY_ARB                                0x2029
#define WGL_SWAP_COPY_EXT                                0x2029
#define WGL_SWAP_UNDEFINED_ARB                           0x202A
#define WGL_SWAP_UNDEFINED_EXT                           0x202A
#define WGL_TYPE_RGBA_ARB                                0x202B
#define WGL_TYPE_RGBA_EXT                                0x202B
#define WGL_TYPE_COLORINDEX_ARB                          0x202C
#define WGL_TYPE_COLORINDEX_EXT                          0x202C
#define WGL_DRAW_TO_PBUFFER_ARB                          0x202D
#define WGL_DRAW_TO_PBUFFER_EXT                          0x202D
#define WGL_MAX_PBUFFER_PIXELS_ARB                       0x202E
#define WGL_MAX_PBUFFER_PIXELS_EXT                       0x202E
#define WGL_MAX_PBUFFER_WIDTH_ARB                        0x202F
#define WGL_MAX_PBUFFER_WIDTH_EXT                        0x202F
#define WGL_MAX_PBUFFER_HEIGHT_ARB                       0x2030
#define WGL_MAX_PBUFFER_HEIGHT_EXT                       0x2030
#define WGL_OPTIMAL_PBUFFER_WIDTH_EXT                    0x2031
#define WGL_OPTIMAL_PBUFFER_HEIGHT_EXT                   0x2032
#define WGL_PBUFFER_LARGEST_ARB                          0x2033
#define WGL_PBUFFER_LARGEST_EXT                          0x2033
#define WGL_PBUFFER_WIDTH_ARB                            0x2034
#define WGL_PBUFFER_WIDTH_EXT                            0x2034
#define WGL_PBUFFER_HEIGHT_ARB                           0x2035
#define WGL_PBUFFER_HEIGHT_EXT                           0x2035
#define WGL_PBUFFER_LOST_ARB                             0x2036
#define WGL_TRANSPARENT_RED_VALUE_ARB                    0x2037
#define WGL_TRANSPARENT_GREEN_VALUE_ARB                  0x2038
#define WGL_TRANSPARENT_BLUE_VALUE_ARB                   0x2039
#define WGL_TRANSPARENT_ALPHA_VALUE_ARB                  0x203A
#define WGL_TRANSPARENT_INDEX_VALUE_ARB                  0x203B
#define WGL_DEPTH_FLOAT_EXT                              0x2040
#define WGL_SAMPLE_BUFFERS_ARB                           0x2041
#define WGL_SAMPLE_BUFFERS_EXT                           0x2041
#define WGL_COVERAGE_SAMPLES_NV                          0x2042
#define WGL_SAMPLES_ARB                                  0x2042
#define WGL_SAMPLES_EXT                                  0x2042
#define ERROR_INVALID_PIXEL_TYPE_ARB                     0x2043
#define ERROR_INVALID_PIXEL_TYPE_EXT                     0x2043
#define WGL_GENLOCK_SOURCE_MULTIVIEW_I3D                 0x2044
#define WGL_GENLOCK_SOURCE_EXTERNAL_SYNC_I3D             0x2045
#define WGL_GENLOCK_SOURCE_EXTERNAL_FIELD_I3D            0x2046
#define WGL_GENLOCK_SOURCE_EXTERNAL_TTL_I3D              0x2047
#define WGL_GENLOCK_SOURCE_DIGITAL_SYNC_I3D              0x2048
#define WGL_GENLOCK_SOURCE_DIGITAL_FIELD_I3D             0x2049
#define WGL_GENLOCK_SOURCE_EDGE_FALLING_I3D              0x204A
#define WGL_GENLOCK_SOURCE_EDGE_RISING_I3D               0x204B
#define WGL_GENLOCK_SOURCE_EDGE_BOTH_I3D                 0x204C
#define WGL_GAMMA_TABLE_SIZE_I3D                         0x204E
#define WGL_GAMMA_EXCLUDE_DESKTOP_I3D                    0x204F
#define WGL_DIGITAL_VIDEO_CURSOR_ALPHA_FRAMEBUFFER_I3D   0x2050
#define WGL_DIGITAL_VIDEO_CURSOR_ALPHA_VALUE_I3D         0x2051
#define WGL_DIGITAL_VIDEO_CURSOR_INCLUDED_I3D            0x2052
#define WGL_DIGITAL_VIDEO_GAMMA_CORRECTED_I3D            0x2053
#define ERROR_INCOMPATIBLE_DEVICE_CONTEXTS_ARB           0x2054
#define WGL_STEREO_EMITTER_ENABLE_3DL                    0x2055
#define WGL_STEREO_EMITTER_DISABLE_3DL                   0x2056
#define WGL_STEREO_POLARITY_NORMAL_3DL                   0x2057
#define WGL_STEREO_POLARITY_INVERT_3DL                   0x2058
#define WGL_SAMPLE_BUFFERS_3DFX                          0x2060
#define WGL_SAMPLES_3DFX                                 0x2061
#define WGL_BIND_TO_TEXTURE_RGB_ARB                      0x2070
#define WGL_BIND_TO_TEXTURE_RGBA_ARB                     0x2071
#define WGL_TEXTURE_FORMAT_ARB                           0x2072
#define WGL_TEXTURE_TARGET_ARB                           0x2073
#define WGL_MIPMAP_TEXTURE_ARB                           0x2074
#define WGL_TEXTURE_RGB_ARB                              0x2075
#define WGL_TEXTURE_RGBA_ARB                             0x2076
#define WGL_NO_TEXTURE_ARB                               0x2077
#define WGL_TEXTURE_CUBE_MAP_ARB                         0x2078
#define WGL_TEXTURE_1D_ARB                               0x2079
#define WGL_TEXTURE_2D_ARB                               0x207A
#define WGL_MIPMAP_LEVEL_ARB                             0x207B
#define WGL_CUBE_MAP_FACE_ARB                            0x207C
#define WGL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB              0x207D
#define WGL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB              0x207E
#define WGL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB              0x207F
#define WGL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB              0x2080
#define WGL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB              0x2081
#define WGL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB              0x2082
#define WGL_FRONT_LEFT_ARB                               0x2083
#define WGL_FRONT_RIGHT_ARB                              0x2084
#define WGL_BACK_LEFT_ARB                                0x2085
#define WGL_BACK_RIGHT_ARB                               0x2086
#define WGL_AUX0_ARB                                     0x2087
#define WGL_AUX1_ARB                                     0x2088
#define WGL_AUX2_ARB                                     0x2089
#define WGL_AUX3_ARB                                     0x208A
#define WGL_AUX4_ARB                                     0x208B
#define WGL_AUX5_ARB                                     0x208C
#define WGL_AUX6_ARB                                     0x208D
#define WGL_AUX7_ARB                                     0x208E
#define WGL_AUX8_ARB                                     0x208F
#define WGL_AUX9_ARB                                     0x2090
#define WGL_CONTEXT_MAJOR_VERSION_ARB                    0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB                    0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB                      0x2093
#define WGL_CONTEXT_FLAGS_ARB                            0x2094
#define ERROR_INVALID_VERSION_ARB                        0x2095
#define ERROR_INVALID_PROFILE_ARB                        0x2096
#define WGL_CONTEXT_RELEASE_BEHAVIOR_ARB                 0x2097
#define WGL_CONTEXT_RELEASE_BEHAVIOR_FLUSH_ARB           0x2098
#define WGL_BIND_TO_TEXTURE_RECTANGLE_RGB_NV             0x20A0
#define WGL_BIND_TO_TEXTURE_RECTANGLE_RGBA_NV            0x20A1
#define WGL_TEXTURE_RECTANGLE_NV                         0x20A2
#define WGL_BIND_TO_TEXTURE_DEPTH_NV                     0x20A3
#define WGL_BIND_TO_TEXTURE_RECTANGLE_DEPTH_NV           0x20A4
#define WGL_DEPTH_TEXTURE_FORMAT_NV                      0x20A5
#define WGL_TEXTURE_DEPTH_COMPONENT_NV                   0x20A6
#define WGL_DEPTH_COMPONENT_NV                           0x20A7
#define WGL_TYPE_RGBA_UNSIGNED_FLOAT_EXT                 0x20A8
#define WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB                 0x20A9
#define WGL_FRAMEBUFFER_SRGB_CAPABLE_EXT                 0x20A9
#define WGL_FLOAT_COMPONENTS_NV                          0x20B0
#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_R_NV         0x20B1
#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RG_NV        0x20B2
#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RGB_NV       0x20B3
#define WGL_BIND_TO_TEXTURE_RECTANGLE_FLOAT_RGBA_NV      0x20B4
#define WGL_TEXTURE_FLOAT_R_NV                           0x20B5
#define WGL_TEXTURE_FLOAT_RG_NV                          0x20B6
#define WGL_TEXTURE_FLOAT_RGB_NV                         0x20B7
#define WGL_TEXTURE_FLOAT_RGBA_NV                        0x20B8
#define WGL_COLOR_SAMPLES_NV                             0x20B9
#define WGL_BIND_TO_VIDEO_RGB_NV                         0x20C0
#define WGL_BIND_TO_VIDEO_RGBA_NV                        0x20C1
#define WGL_BIND_TO_VIDEO_RGB_AND_DEPTH_NV               0x20C2
#define WGL_VIDEO_OUT_COLOR_NV                           0x20C3
#define WGL_VIDEO_OUT_ALPHA_NV                           0x20C4
#define WGL_VIDEO_OUT_DEPTH_NV                           0x20C5
#define WGL_VIDEO_OUT_COLOR_AND_ALPHA_NV                 0x20C6
#define WGL_VIDEO_OUT_COLOR_AND_DEPTH_NV                 0x20C7
#define WGL_VIDEO_OUT_FRAME                              0x20C8
#define WGL_VIDEO_OUT_FIELD_1                            0x20C9
#define WGL_VIDEO_OUT_FIELD_2                            0x20CA
#define WGL_VIDEO_OUT_STACKED_FIELDS_1_2                 0x20CB
#define WGL_VIDEO_OUT_STACKED_FIELDS_2_1                 0x20CC
#define WGL_UNIQUE_ID_NV                                 0x20CE
#define WGL_NUM_VIDEO_CAPTURE_SLOTS_NV                   0x20CF
#define ERROR_INCOMPATIBLE_AFFINITY_MASKS_NV             0x20D0
#define ERROR_MISSING_AFFINITY_MASK_NV                   0x20D1
#define WGL_NUM_VIDEO_SLOTS_NV                           0x20F0
#define WGL_TYPE_RGBA_FLOAT_ARB                          0x21A0
#define WGL_TYPE_RGBA_FLOAT_ATI                          0x21A0
#define WGL_GPU_FASTEST_TARGET_GPUS_AMD                  0x21A2
#define WGL_GPU_RAM_AMD                                  0x21A3
#define WGL_GPU_CLOCK_AMD                                0x21A4
#define WGL_GPU_NUM_PIPES_AMD                            0x21A5
#define WGL_GPU_NUM_SIMD_AMD                             0x21A6
#define WGL_GPU_NUM_RB_AMD                               0x21A7
#define WGL_GPU_NUM_SPI_AMD                              0x21A8
#define WGL_LOSE_CONTEXT_ON_RESET_ARB                    0x8252
#define WGL_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB      0x8256
#define WGL_NO_RESET_NOTIFICATION_ARB                    0x8261
#define WGL_CONTEXT_PROFILE_MASK_ARB                     0x9126
#define WGL_FONT_POLYGONS                                1

typedef void * (GLAPIENTRY *PFNWGLALLOCATEMEMORYNVPROC)(GLsizei size, GLfloat readfreq, GLfloat writefreq, GLfloat priority);
typedef BOOL (GLAPIENTRY *PFNWGLASSOCIATEIMAGEBUFFEREVENTSI3DPROC)(HDC hDC, const HANDLE * pEvent, const LPVOID * pAddress, const DWORD * pSize, UINT count);
typedef BOOL (GLAPIENTRY *PFNWGLBEGINFRAMETRACKINGI3DPROC)(void);
typedef GLboolean (GLAPIENTRY *PFNWGLBINDDISPLAYCOLORTABLEEXTPROC)(GLushort id);
typedef BOOL (GLAPIENTRY *PFNWGLBINDSWAPBARRIERNVPROC)(GLuint group, GLuint barrier);
typedef BOOL (GLAPIENTRY *PFNWGLBINDTEXIMAGEARBPROC)(HPBUFFERARB hPbuffer, int iBuffer);
typedef BOOL (GLAPIENTRY *PFNWGLBINDVIDEOCAPTUREDEVICENVPROC)(UINT uVideoSlot, HVIDEOINPUTDEVICENV hDevice);
typedef BOOL (GLAPIENTRY *PFNWGLBINDVIDEODEVICENVPROC)(HDC hDC, unsigned int uVideoSlot, HVIDEOOUTPUTDEVICENV hVideoDevice, const int * piAttribList);
typedef BOOL (GLAPIENTRY *PFNWGLBINDVIDEOIMAGENVPROC)(HPVIDEODEV hVideoDevice, HPBUFFERARB hPbuffer, int iVideoBuffer);
typedef VOID (GLAPIENTRY *PFNWGLBLITCONTEXTFRAMEBUFFERAMDPROC)(HGLRC dstCtx, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
typedef int (GLAPIENTRY *PFNWGLCHOOSEPIXELFORMATPROC)(HDC hDc, const PIXELFORMATDESCRIPTOR * pPfd);
typedef BOOL (GLAPIENTRY *PFNWGLCHOOSEPIXELFORMATARBPROC)(HDC hdc, const int * piAttribIList, const FLOAT * pfAttribFList, UINT nMaxFormats, int * piFormats, UINT * nNumFormats);
typedef BOOL (GLAPIENTRY *PFNWGLCHOOSEPIXELFORMATEXTPROC)(HDC hdc, const int * piAttribIList, const FLOAT * pfAttribFList, UINT nMaxFormats, int * piFormats, UINT * nNumFormats);
typedef BOOL (GLAPIENTRY *PFNWGLCOPYCONTEXTPROC)(HGLRC hglrcSrc, HGLRC hglrcDst, UINT mask);
typedef BOOL (GLAPIENTRY *PFNWGLCOPYIMAGESUBDATANVPROC)(HGLRC hSrcRC, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, HGLRC hDstRC, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth);
typedef HDC (GLAPIENTRY *PFNWGLCREATEAFFINITYDCNVPROC)(const HGPUNV * phGpuList);
typedef HGLRC (GLAPIENTRY *PFNWGLCREATEASSOCIATEDCONTEXTAMDPROC)(UINT id);
typedef HGLRC (GLAPIENTRY *PFNWGLCREATEASSOCIATEDCONTEXTATTRIBSAMDPROC)(UINT id, HGLRC hShareContext, const int * attribList);
typedef HANDLE (GLAPIENTRY *PFNWGLCREATEBUFFERREGIONARBPROC)(HDC hDC, int iLayerPlane, UINT uType);
typedef HGLRC (GLAPIENTRY *PFNWGLCREATECONTEXTPROC)(HDC hDc);
typedef HGLRC (GLAPIENTRY *PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC, HGLRC hShareContext, const int * attribList);
typedef GLboolean (GLAPIENTRY *PFNWGLCREATEDISPLAYCOLORTABLEEXTPROC)(GLushort id);
typedef LPVOID (GLAPIENTRY *PFNWGLCREATEIMAGEBUFFERI3DPROC)(HDC hDC, DWORD dwSize, UINT uFlags);
typedef HGLRC (GLAPIENTRY *PFNWGLCREATELAYERCONTEXTPROC)(HDC hDc, int level);
typedef HPBUFFERARB (GLAPIENTRY *PFNWGLCREATEPBUFFERARBPROC)(HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int * piAttribList);
typedef HPBUFFEREXT (GLAPIENTRY *PFNWGLCREATEPBUFFEREXTPROC)(HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int * piAttribList);
typedef BOOL (GLAPIENTRY *PFNWGLDXCLOSEDEVICENVPROC)(HANDLE hDevice);
typedef BOOL (GLAPIENTRY *PFNWGLDXLOCKOBJECTSNVPROC)(HANDLE hDevice, GLint count, HANDLE * hObjects);
typedef BOOL (GLAPIENTRY *PFNWGLDXOBJECTACCESSNVPROC)(HANDLE hObject, GLenum access);
typedef HANDLE (GLAPIENTRY *PFNWGLDXOPENDEVICENVPROC)(void * dxDevice);
typedef HANDLE (GLAPIENTRY *PFNWGLDXREGISTEROBJECTNVPROC)(HANDLE hDevice, void * dxObject, GLuint name, GLenum type, GLenum access);
typedef BOOL (GLAPIENTRY *PFNWGLDXSETRESOURCESHAREHANDLENVPROC)(void * dxObject, HANDLE shareHandle);
typedef BOOL (GLAPIENTRY *PFNWGLDXUNLOCKOBJECTSNVPROC)(HANDLE hDevice, GLint count, HANDLE * hObjects);
typedef BOOL (GLAPIENTRY *PFNWGLDXUNREGISTEROBJECTNVPROC)(HANDLE hDevice, HANDLE hObject);
typedef BOOL (GLAPIENTRY *PFNWGLDELAYBEFORESWAPNVPROC)(HDC hDC, GLfloat seconds);
typedef BOOL (GLAPIENTRY *PFNWGLDELETEASSOCIATEDCONTEXTAMDPROC)(HGLRC hglrc);
typedef VOID (GLAPIENTRY *PFNWGLDELETEBUFFERREGIONARBPROC)(HANDLE hRegion);
typedef BOOL (GLAPIENTRY *PFNWGLDELETECONTEXTPROC)(HGLRC oldContext);
typedef BOOL (GLAPIENTRY *PFNWGLDELETEDCNVPROC)(HDC hdc);
typedef BOOL (GLAPIENTRY *PFNWGLDESCRIBELAYERPLANEPROC)(HDC hDc, int pixelFormat, int layerPlane, UINT nBytes, const LAYERPLANEDESCRIPTOR * plpd);
typedef int (GLAPIENTRY *PFNWGLDESCRIBEPIXELFORMATPROC)(HDC hdc, int ipfd, UINT cjpfd, const PIXELFORMATDESCRIPTOR * ppfd);
typedef VOID (GLAPIENTRY *PFNWGLDESTROYDISPLAYCOLORTABLEEXTPROC)(GLushort id);
typedef BOOL (GLAPIENTRY *PFNWGLDESTROYIMAGEBUFFERI3DPROC)(HDC hDC, LPVOID pAddress);
typedef BOOL (GLAPIENTRY *PFNWGLDESTROYPBUFFERARBPROC)(HPBUFFERARB hPbuffer);
typedef BOOL (GLAPIENTRY *PFNWGLDESTROYPBUFFEREXTPROC)(HPBUFFEREXT hPbuffer);
typedef BOOL (GLAPIENTRY *PFNWGLDISABLEFRAMELOCKI3DPROC)(void);
typedef BOOL (GLAPIENTRY *PFNWGLDISABLEGENLOCKI3DPROC)(HDC hDC);
typedef BOOL (GLAPIENTRY *PFNWGLENABLEFRAMELOCKI3DPROC)(void);
typedef BOOL (GLAPIENTRY *PFNWGLENABLEGENLOCKI3DPROC)(HDC hDC);
typedef BOOL (GLAPIENTRY *PFNWGLENDFRAMETRACKINGI3DPROC)(void);
typedef BOOL (GLAPIENTRY *PFNWGLENUMGPUDEVICESNVPROC)(HGPUNV hGpu, UINT iDeviceIndex, PGPU_DEVICE lpGpuDevice);
typedef BOOL (GLAPIENTRY *PFNWGLENUMGPUSFROMAFFINITYDCNVPROC)(HDC hAffinityDC, UINT iGpuIndex, HGPUNV * hGpu);
typedef BOOL (GLAPIENTRY *PFNWGLENUMGPUSNVPROC)(UINT iGpuIndex, HGPUNV * phGpu);
typedef UINT (GLAPIENTRY *PFNWGLENUMERATEVIDEOCAPTUREDEVICESNVPROC)(HDC hDc, HVIDEOINPUTDEVICENV * phDeviceList);
typedef int (GLAPIENTRY *PFNWGLENUMERATEVIDEODEVICESNVPROC)(HDC hDC, HVIDEOOUTPUTDEVICENV * phDeviceList);
typedef void (GLAPIENTRY *PFNWGLFREEMEMORYNVPROC)(void * pointer);
typedef BOOL (GLAPIENTRY *PFNWGLGENLOCKSAMPLERATEI3DPROC)(HDC hDC, UINT uRate);
typedef BOOL (GLAPIENTRY *PFNWGLGENLOCKSOURCEDELAYI3DPROC)(HDC hDC, UINT uDelay);
typedef BOOL (GLAPIENTRY *PFNWGLGENLOCKSOURCEEDGEI3DPROC)(HDC hDC, UINT uEdge);
typedef BOOL (GLAPIENTRY *PFNWGLGENLOCKSOURCEI3DPROC)(HDC hDC, UINT uSource);
typedef UINT (GLAPIENTRY *PFNWGLGETCONTEXTGPUIDAMDPROC)(HGLRC hglrc);
typedef HGLRC (GLAPIENTRY *PFNWGLGETCURRENTASSOCIATEDCONTEXTAMDPROC)(void);
typedef HGLRC (GLAPIENTRY *PFNWGLGETCURRENTCONTEXTPROC)(void);
typedef HDC (GLAPIENTRY *PFNWGLGETCURRENTDCPROC)(void);
typedef HDC (GLAPIENTRY *PFNWGLGETCURRENTREADDCARBPROC)(void);
typedef HDC (GLAPIENTRY *PFNWGLGETCURRENTREADDCEXTPROC)(void);
typedef PROC (GLAPIENTRY *PFNWGLGETDEFAULTPROCADDRESSPROC)(LPCSTR lpszProc);
typedef BOOL (GLAPIENTRY *PFNWGLGETDIGITALVIDEOPARAMETERSI3DPROC)(HDC hDC, int iAttribute, int * piValue);
typedef UINT (GLAPIENTRY *PFNWGLGETENHMETAFILEPIXELFORMATPROC)(HENHMETAFILE hemf, const PIXELFORMATDESCRIPTOR * ppfd);
typedef const char * (GLAPIENTRY *PFNWGLGETEXTENSIONSSTRINGARBPROC)(HDC hdc);
typedef const char * (GLAPIENTRY *PFNWGLGETEXTENSIONSSTRINGEXTPROC)(void);
typedef BOOL (GLAPIENTRY *PFNWGLGETFRAMEUSAGEI3DPROC)(float * pUsage);
typedef UINT (GLAPIENTRY *PFNWGLGETGPUIDSAMDPROC)(UINT maxCount, UINT * ids);
typedef INT (GLAPIENTRY *PFNWGLGETGPUINFOAMDPROC)(UINT id, int property, GLenum dataType, UINT size, void * data);
typedef BOOL (GLAPIENTRY *PFNWGLGETGAMMATABLEI3DPROC)(HDC hDC, int iEntries, USHORT * puRed, USHORT * puGreen, USHORT * puBlue);
typedef BOOL (GLAPIENTRY *PFNWGLGETGAMMATABLEPARAMETERSI3DPROC)(HDC hDC, int iAttribute, int * piValue);
typedef BOOL (GLAPIENTRY *PFNWGLGETGENLOCKSAMPLERATEI3DPROC)(HDC hDC, UINT * uRate);
typedef BOOL (GLAPIENTRY *PFNWGLGETGENLOCKSOURCEDELAYI3DPROC)(HDC hDC, UINT * uDelay);
typedef BOOL (GLAPIENTRY *PFNWGLGETGENLOCKSOURCEEDGEI3DPROC)(HDC hDC, UINT * uEdge);
typedef BOOL (GLAPIENTRY *PFNWGLGETGENLOCKSOURCEI3DPROC)(HDC hDC, UINT * uSource);
typedef int (GLAPIENTRY *PFNWGLGETLAYERPALETTEENTRIESPROC)(HDC hdc, int iLayerPlane, int iStart, int cEntries, const COLORREF * pcr);
typedef BOOL (GLAPIENTRY *PFNWGLGETMSCRATEOMLPROC)(HDC hdc, INT32 * numerator, INT32 * denominator);
typedef HDC (GLAPIENTRY *PFNWGLGETPBUFFERDCARBPROC)(HPBUFFERARB hPbuffer);
typedef HDC (GLAPIENTRY *PFNWGLGETPBUFFERDCEXTPROC)(HPBUFFEREXT hPbuffer);
typedef int (GLAPIENTRY *PFNWGLGETPIXELFORMATPROC)(HDC hdc);
typedef BOOL (GLAPIENTRY *PFNWGLGETPIXELFORMATATTRIBFVARBPROC)(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int * piAttributes, FLOAT * pfValues);
typedef BOOL (GLAPIENTRY *PFNWGLGETPIXELFORMATATTRIBFVEXTPROC)(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int * piAttributes, FLOAT * pfValues);
typedef BOOL (GLAPIENTRY *PFNWGLGETPIXELFORMATATTRIBIVARBPROC)(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int * piAttributes, int * piValues);
typedef BOOL (GLAPIENTRY *PFNWGLGETPIXELFORMATATTRIBIVEXTPROC)(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int * piAttributes, int * piValues);
typedef PROC (GLAPIENTRY *PFNWGLGETPROCADDRESSPROC)(LPCSTR lpszProc);
typedef int (GLAPIENTRY *PFNWGLGETSWAPINTERVALEXTPROC)(void);
typedef BOOL (GLAPIENTRY *PFNWGLGETSYNCVALUESOMLPROC)(HDC hdc, INT64 * ust, INT64 * msc, INT64 * sbc);
typedef BOOL (GLAPIENTRY *PFNWGLGETVIDEODEVICENVPROC)(HDC hDC, int numDevices, HPVIDEODEV * hVideoDevice);
typedef BOOL (GLAPIENTRY *PFNWGLGETVIDEOINFONVPROC)(HPVIDEODEV hpVideoDevice, unsigned long * pulCounterOutputPbuffer, unsigned long * pulCounterOutputVideo);
typedef BOOL (GLAPIENTRY *PFNWGLISENABLEDFRAMELOCKI3DPROC)(BOOL * pFlag);
typedef BOOL (GLAPIENTRY *PFNWGLISENABLEDGENLOCKI3DPROC)(HDC hDC, BOOL * pFlag);
typedef BOOL (GLAPIENTRY *PFNWGLJOINSWAPGROUPNVPROC)(HDC hDC, GLuint group);
typedef GLboolean (GLAPIENTRY *PFNWGLLOADDISPLAYCOLORTABLEEXTPROC)(const GLushort * table, GLuint length);
typedef BOOL (GLAPIENTRY *PFNWGLLOCKVIDEOCAPTUREDEVICENVPROC)(HDC hDc, HVIDEOINPUTDEVICENV hDevice);
typedef BOOL (GLAPIENTRY *PFNWGLMAKEASSOCIATEDCONTEXTCURRENTAMDPROC)(HGLRC hglrc);
typedef BOOL (GLAPIENTRY *PFNWGLMAKECONTEXTCURRENTARBPROC)(HDC hDrawDC, HDC hReadDC, HGLRC hglrc);
typedef BOOL (GLAPIENTRY *PFNWGLMAKECONTEXTCURRENTEXTPROC)(HDC hDrawDC, HDC hReadDC, HGLRC hglrc);
typedef BOOL (GLAPIENTRY *PFNWGLMAKECURRENTPROC)(HDC hDc, HGLRC newContext);
typedef BOOL (GLAPIENTRY *PFNWGLQUERYCURRENTCONTEXTNVPROC)(int iAttribute, int * piValue);
typedef BOOL (GLAPIENTRY *PFNWGLQUERYFRAMECOUNTNVPROC)(HDC hDC, GLuint * count);
typedef BOOL (GLAPIENTRY *PFNWGLQUERYFRAMELOCKMASTERI3DPROC)(BOOL * pFlag);
typedef BOOL (GLAPIENTRY *PFNWGLQUERYFRAMETRACKINGI3DPROC)(DWORD * pFrameCount, DWORD * pMissedFrames, float * pLastMissedUsage);
typedef BOOL (GLAPIENTRY *PFNWGLQUERYGENLOCKMAXSOURCEDELAYI3DPROC)(HDC hDC, UINT * uMaxLineDelay, UINT * uMaxPixelDelay);
typedef BOOL (GLAPIENTRY *PFNWGLQUERYMAXSWAPGROUPSNVPROC)(HDC hDC, GLuint * maxGroups, GLuint * maxBarriers);
typedef BOOL (GLAPIENTRY *PFNWGLQUERYPBUFFERARBPROC)(HPBUFFERARB hPbuffer, int iAttribute, int * piValue);
typedef BOOL (GLAPIENTRY *PFNWGLQUERYPBUFFEREXTPROC)(HPBUFFEREXT hPbuffer, int iAttribute, int * piValue);
typedef BOOL (GLAPIENTRY *PFNWGLQUERYSWAPGROUPNVPROC)(HDC hDC, GLuint * group, GLuint * barrier);
typedef BOOL (GLAPIENTRY *PFNWGLQUERYVIDEOCAPTUREDEVICENVPROC)(HDC hDc, HVIDEOINPUTDEVICENV hDevice, int iAttribute, int * piValue);
typedef BOOL (GLAPIENTRY *PFNWGLREALIZELAYERPALETTEPROC)(HDC hdc, int iLayerPlane, BOOL bRealize);
typedef BOOL (GLAPIENTRY *PFNWGLRELEASEIMAGEBUFFEREVENTSI3DPROC)(HDC hDC, const LPVOID * pAddress, UINT count);
typedef int (GLAPIENTRY *PFNWGLRELEASEPBUFFERDCARBPROC)(HPBUFFERARB hPbuffer, HDC hDC);
typedef int (GLAPIENTRY *PFNWGLRELEASEPBUFFERDCEXTPROC)(HPBUFFEREXT hPbuffer, HDC hDC);
typedef BOOL (GLAPIENTRY *PFNWGLRELEASETEXIMAGEARBPROC)(HPBUFFERARB hPbuffer, int iBuffer);
typedef BOOL (GLAPIENTRY *PFNWGLRELEASEVIDEOCAPTUREDEVICENVPROC)(HDC hDc, HVIDEOINPUTDEVICENV hDevice);
typedef BOOL (GLAPIENTRY *PFNWGLRELEASEVIDEODEVICENVPROC)(HPVIDEODEV hVideoDevice);
typedef BOOL (GLAPIENTRY *PFNWGLRELEASEVIDEOIMAGENVPROC)(HPBUFFERARB hPbuffer, int iVideoBuffer);
typedef BOOL (GLAPIENTRY *PFNWGLRESETFRAMECOUNTNVPROC)(HDC hDC);
typedef BOOL (GLAPIENTRY *PFNWGLRESTOREBUFFERREGIONARBPROC)(HANDLE hRegion, int x, int y, int width, int height, int xSrc, int ySrc);
typedef BOOL (GLAPIENTRY *PFNWGLSAVEBUFFERREGIONARBPROC)(HANDLE hRegion, int x, int y, int width, int height);
typedef BOOL (GLAPIENTRY *PFNWGLSENDPBUFFERTOVIDEONVPROC)(HPBUFFERARB hPbuffer, int iBufferType, unsigned long * pulCounterPbuffer, BOOL bBlock);
typedef BOOL (GLAPIENTRY *PFNWGLSETDIGITALVIDEOPARAMETERSI3DPROC)(HDC hDC, int iAttribute, const int * piValue);
typedef BOOL (GLAPIENTRY *PFNWGLSETGAMMATABLEI3DPROC)(HDC hDC, int iEntries, const USHORT * puRed, const USHORT * puGreen, const USHORT * puBlue);
typedef BOOL (GLAPIENTRY *PFNWGLSETGAMMATABLEPARAMETERSI3DPROC)(HDC hDC, int iAttribute, const int * piValue);
typedef int (GLAPIENTRY *PFNWGLSETLAYERPALETTEENTRIESPROC)(HDC hdc, int iLayerPlane, int iStart, int cEntries, const COLORREF * pcr);
typedef BOOL (GLAPIENTRY *PFNWGLSETPBUFFERATTRIBARBPROC)(HPBUFFERARB hPbuffer, const int * piAttribList);
typedef BOOL (GLAPIENTRY *PFNWGLSETPIXELFORMATPROC)(HDC hdc, int ipfd, const PIXELFORMATDESCRIPTOR * ppfd);
typedef BOOL (GLAPIENTRY *PFNWGLSETSTEREOEMITTERSTATE3DLPROC)(HDC hDC, UINT uState);
typedef BOOL (GLAPIENTRY *PFNWGLSHARELISTSPROC)(HGLRC hrcSrvShare, HGLRC hrcSrvSource);
typedef BOOL (GLAPIENTRY *PFNWGLSWAPBUFFERSPROC)(HDC hdc);
typedef INT64 (GLAPIENTRY *PFNWGLSWAPBUFFERSMSCOMLPROC)(HDC hdc, INT64 target_msc, INT64 divisor, INT64 remainder);
typedef BOOL (GLAPIENTRY *PFNWGLSWAPINTERVALEXTPROC)(int interval);
typedef BOOL (GLAPIENTRY *PFNWGLSWAPLAYERBUFFERSPROC)(HDC hdc, UINT fuFlags);
typedef INT64 (GLAPIENTRY *PFNWGLSWAPLAYERBUFFERSMSCOMLPROC)(HDC hdc, int fuPlanes, INT64 target_msc, INT64 divisor, INT64 remainder);
typedef BOOL (GLAPIENTRY *PFNWGLUSEFONTBITMAPSAPROC)(HDC hDC, DWORD first, DWORD count, DWORD listBase);
typedef BOOL (GLAPIENTRY *PFNWGLUSEFONTBITMAPSWPROC)(HDC hDC, DWORD first, DWORD count, DWORD listBase);
typedef BOOL (GLAPIENTRY *PFNWGLUSEFONTOUTLINESPROC)(HDC hDC, DWORD first, DWORD count, DWORD listBase, FLOAT deviation, FLOAT extrusion, int format, LPGLYPHMETRICSFLOAT lpgmf);
typedef BOOL (GLAPIENTRY *PFNWGLUSEFONTOUTLINESAPROC)(HDC hDC, DWORD first, DWORD count, DWORD listBase, FLOAT deviation, FLOAT extrusion, int format, LPGLYPHMETRICSFLOAT lpgmf);
typedef BOOL (GLAPIENTRY *PFNWGLUSEFONTOUTLINESWPROC)(HDC hDC, DWORD first, DWORD count, DWORD listBase, FLOAT deviation, FLOAT extrusion, int format, LPGLYPHMETRICSFLOAT lpgmf);
typedef BOOL (GLAPIENTRY *PFNWGLWAITFORMSCOMLPROC)(HDC hdc, INT64 target_msc, INT64 divisor, INT64 remainder, INT64 * ust, INT64 * msc, INT64 * sbc);
typedef BOOL (GLAPIENTRY *PFNWGLWAITFORSBCOMLPROC)(HDC hdc, INT64 target_sbc, INT64 * ust, INT64 * msc, INT64 * sbc);
GLPROXY_IMPORTEXPORT void * GLPROXY_CALLSPEC glproxy_wglAllocateMemoryNV(GLsizei size, GLfloat readfreq, GLfloat writefreq, GLfloat priority);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglAssociateImageBufferEventsI3D(HDC hDC, const HANDLE * pEvent, const LPVOID * pAddress, const DWORD * pSize, UINT count);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglBeginFrameTrackingI3D(void);

GLPROXY_IMPORTEXPORT GLboolean GLPROXY_CALLSPEC glproxy_wglBindDisplayColorTableEXT(GLushort id);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglBindSwapBarrierNV(GLuint group, GLuint barrier);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglBindTexImageARB(HPBUFFERARB hPbuffer, int iBuffer);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglBindVideoCaptureDeviceNV(UINT uVideoSlot, HVIDEOINPUTDEVICENV hDevice);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglBindVideoDeviceNV(HDC hDC, unsigned int uVideoSlot, HVIDEOOUTPUTDEVICENV hVideoDevice, const int * piAttribList);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglBindVideoImageNV(HPVIDEODEV hVideoDevice, HPBUFFERARB hPbuffer, int iVideoBuffer);

GLPROXY_IMPORTEXPORT VOID GLPROXY_CALLSPEC glproxy_wglBlitContextFramebufferAMD(HGLRC dstCtx, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);

GLPROXY_IMPORTEXPORT int GLPROXY_CALLSPEC glproxy_wglChoosePixelFormat(HDC hDc, const PIXELFORMATDESCRIPTOR * pPfd);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglChoosePixelFormatARB(HDC hdc, const int * piAttribIList, const FLOAT * pfAttribFList, UINT nMaxFormats, int * piFormats, UINT * nNumFormats);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglChoosePixelFormatEXT(HDC hdc, const int * piAttribIList, const FLOAT * pfAttribFList, UINT nMaxFormats, int * piFormats, UINT * nNumFormats);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglCopyContext(HGLRC hglrcSrc, HGLRC hglrcDst, UINT mask);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglCopyImageSubDataNV(HGLRC hSrcRC, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, HGLRC hDstRC, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth);

GLPROXY_IMPORTEXPORT HDC GLPROXY_CALLSPEC glproxy_wglCreateAffinityDCNV(const HGPUNV * phGpuList);

GLPROXY_IMPORTEXPORT HGLRC GLPROXY_CALLSPEC glproxy_wglCreateAssociatedContextAMD(UINT id);

GLPROXY_IMPORTEXPORT HGLRC GLPROXY_CALLSPEC glproxy_wglCreateAssociatedContextAttribsAMD(UINT id, HGLRC hShareContext, const int * attribList);

GLPROXY_IMPORTEXPORT HANDLE GLPROXY_CALLSPEC glproxy_wglCreateBufferRegionARB(HDC hDC, int iLayerPlane, UINT uType);

GLPROXY_IMPORTEXPORT HGLRC GLPROXY_CALLSPEC glproxy_wglCreateContext(HDC hDc);

GLPROXY_IMPORTEXPORT HGLRC GLPROXY_CALLSPEC glproxy_wglCreateContextAttribsARB(HDC hDC, HGLRC hShareContext, const int * attribList);

GLPROXY_IMPORTEXPORT GLboolean GLPROXY_CALLSPEC glproxy_wglCreateDisplayColorTableEXT(GLushort id);

GLPROXY_IMPORTEXPORT LPVOID GLPROXY_CALLSPEC glproxy_wglCreateImageBufferI3D(HDC hDC, DWORD dwSize, UINT uFlags);

GLPROXY_IMPORTEXPORT HGLRC GLPROXY_CALLSPEC glproxy_wglCreateLayerContext(HDC hDc, int level);

GLPROXY_IMPORTEXPORT HPBUFFERARB GLPROXY_CALLSPEC glproxy_wglCreatePbufferARB(HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int * piAttribList);

GLPROXY_IMPORTEXPORT HPBUFFEREXT GLPROXY_CALLSPEC glproxy_wglCreatePbufferEXT(HDC hDC, int iPixelFormat, int iWidth, int iHeight, const int * piAttribList);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglDXCloseDeviceNV(HANDLE hDevice);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglDXLockObjectsNV(HANDLE hDevice, GLint count, HANDLE * hObjects);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglDXObjectAccessNV(HANDLE hObject, GLenum access);

GLPROXY_IMPORTEXPORT HANDLE GLPROXY_CALLSPEC glproxy_wglDXOpenDeviceNV(void * dxDevice);

GLPROXY_IMPORTEXPORT HANDLE GLPROXY_CALLSPEC glproxy_wglDXRegisterObjectNV(HANDLE hDevice, void * dxObject, GLuint name, GLenum type, GLenum access);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglDXSetResourceShareHandleNV(void * dxObject, HANDLE shareHandle);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglDXUnlockObjectsNV(HANDLE hDevice, GLint count, HANDLE * hObjects);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglDXUnregisterObjectNV(HANDLE hDevice, HANDLE hObject);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglDelayBeforeSwapNV(HDC hDC, GLfloat seconds);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglDeleteAssociatedContextAMD(HGLRC hglrc);

GLPROXY_IMPORTEXPORT VOID GLPROXY_CALLSPEC glproxy_wglDeleteBufferRegionARB(HANDLE hRegion);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglDeleteContext(HGLRC oldContext);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglDeleteDCNV(HDC hdc);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglDescribeLayerPlane(HDC hDc, int pixelFormat, int layerPlane, UINT nBytes, const LAYERPLANEDESCRIPTOR * plpd);

GLPROXY_IMPORTEXPORT int GLPROXY_CALLSPEC glproxy_wglDescribePixelFormat(HDC hdc, int ipfd, UINT cjpfd, const PIXELFORMATDESCRIPTOR * ppfd);

GLPROXY_IMPORTEXPORT VOID GLPROXY_CALLSPEC glproxy_wglDestroyDisplayColorTableEXT(GLushort id);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglDestroyImageBufferI3D(HDC hDC, LPVOID pAddress);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglDestroyPbufferARB(HPBUFFERARB hPbuffer);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglDestroyPbufferEXT(HPBUFFEREXT hPbuffer);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglDisableFrameLockI3D(void);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglDisableGenlockI3D(HDC hDC);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglEnableFrameLockI3D(void);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglEnableGenlockI3D(HDC hDC);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglEndFrameTrackingI3D(void);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglEnumGpuDevicesNV(HGPUNV hGpu, UINT iDeviceIndex, PGPU_DEVICE lpGpuDevice);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglEnumGpusFromAffinityDCNV(HDC hAffinityDC, UINT iGpuIndex, HGPUNV * hGpu);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglEnumGpusNV(UINT iGpuIndex, HGPUNV * phGpu);

GLPROXY_IMPORTEXPORT UINT GLPROXY_CALLSPEC glproxy_wglEnumerateVideoCaptureDevicesNV(HDC hDc, HVIDEOINPUTDEVICENV * phDeviceList);

GLPROXY_IMPORTEXPORT int GLPROXY_CALLSPEC glproxy_wglEnumerateVideoDevicesNV(HDC hDC, HVIDEOOUTPUTDEVICENV * phDeviceList);

GLPROXY_IMPORTEXPORT void GLPROXY_CALLSPEC glproxy_wglFreeMemoryNV(void * pointer);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGenlockSampleRateI3D(HDC hDC, UINT uRate);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGenlockSourceDelayI3D(HDC hDC, UINT uDelay);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGenlockSourceEdgeI3D(HDC hDC, UINT uEdge);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGenlockSourceI3D(HDC hDC, UINT uSource);

GLPROXY_IMPORTEXPORT UINT GLPROXY_CALLSPEC glproxy_wglGetContextGPUIDAMD(HGLRC hglrc);

GLPROXY_IMPORTEXPORT HGLRC GLPROXY_CALLSPEC glproxy_wglGetCurrentAssociatedContextAMD(void);

GLPROXY_IMPORTEXPORT HGLRC GLPROXY_CALLSPEC glproxy_wglGetCurrentContext(void);

GLPROXY_IMPORTEXPORT HDC GLPROXY_CALLSPEC glproxy_wglGetCurrentDC(void);

GLPROXY_IMPORTEXPORT HDC GLPROXY_CALLSPEC glproxy_wglGetCurrentReadDCARB(void);

GLPROXY_IMPORTEXPORT HDC GLPROXY_CALLSPEC glproxy_wglGetCurrentReadDCEXT(void);

GLPROXY_IMPORTEXPORT PROC GLPROXY_CALLSPEC glproxy_wglGetDefaultProcAddress(LPCSTR lpszProc);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGetDigitalVideoParametersI3D(HDC hDC, int iAttribute, int * piValue);

GLPROXY_IMPORTEXPORT UINT GLPROXY_CALLSPEC glproxy_wglGetEnhMetaFilePixelFormat(HENHMETAFILE hemf, const PIXELFORMATDESCRIPTOR * ppfd);

GLPROXY_IMPORTEXPORT const char * GLPROXY_CALLSPEC glproxy_wglGetExtensionsStringARB(HDC hdc);

GLPROXY_IMPORTEXPORT const char * GLPROXY_CALLSPEC glproxy_wglGetExtensionsStringEXT(void);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGetFrameUsageI3D(float * pUsage);

GLPROXY_IMPORTEXPORT UINT GLPROXY_CALLSPEC glproxy_wglGetGPUIDsAMD(UINT maxCount, UINT * ids);

GLPROXY_IMPORTEXPORT INT GLPROXY_CALLSPEC glproxy_wglGetGPUInfoAMD(UINT id, int property, GLenum dataType, UINT size, void * data);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGetGammaTableI3D(HDC hDC, int iEntries, USHORT * puRed, USHORT * puGreen, USHORT * puBlue);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGetGammaTableParametersI3D(HDC hDC, int iAttribute, int * piValue);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGetGenlockSampleRateI3D(HDC hDC, UINT * uRate);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGetGenlockSourceDelayI3D(HDC hDC, UINT * uDelay);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGetGenlockSourceEdgeI3D(HDC hDC, UINT * uEdge);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGetGenlockSourceI3D(HDC hDC, UINT * uSource);

GLPROXY_IMPORTEXPORT int GLPROXY_CALLSPEC glproxy_wglGetLayerPaletteEntries(HDC hdc, int iLayerPlane, int iStart, int cEntries, const COLORREF * pcr);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGetMscRateOML(HDC hdc, INT32 * numerator, INT32 * denominator);

GLPROXY_IMPORTEXPORT HDC GLPROXY_CALLSPEC glproxy_wglGetPbufferDCARB(HPBUFFERARB hPbuffer);

GLPROXY_IMPORTEXPORT HDC GLPROXY_CALLSPEC glproxy_wglGetPbufferDCEXT(HPBUFFEREXT hPbuffer);

GLPROXY_IMPORTEXPORT int GLPROXY_CALLSPEC glproxy_wglGetPixelFormat(HDC hdc);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGetPixelFormatAttribfvARB(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int * piAttributes, FLOAT * pfValues);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGetPixelFormatAttribfvEXT(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int * piAttributes, FLOAT * pfValues);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGetPixelFormatAttribivARB(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, const int * piAttributes, int * piValues);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGetPixelFormatAttribivEXT(HDC hdc, int iPixelFormat, int iLayerPlane, UINT nAttributes, int * piAttributes, int * piValues);

GLPROXY_IMPORTEXPORT PROC GLPROXY_CALLSPEC glproxy_wglGetProcAddress(LPCSTR lpszProc);

GLPROXY_IMPORTEXPORT int GLPROXY_CALLSPEC glproxy_wglGetSwapIntervalEXT(void);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGetSyncValuesOML(HDC hdc, INT64 * ust, INT64 * msc, INT64 * sbc);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGetVideoDeviceNV(HDC hDC, int numDevices, HPVIDEODEV * hVideoDevice);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglGetVideoInfoNV(HPVIDEODEV hpVideoDevice, unsigned long * pulCounterOutputPbuffer, unsigned long * pulCounterOutputVideo);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglIsEnabledFrameLockI3D(BOOL * pFlag);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglIsEnabledGenlockI3D(HDC hDC, BOOL * pFlag);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglJoinSwapGroupNV(HDC hDC, GLuint group);

GLPROXY_IMPORTEXPORT GLboolean GLPROXY_CALLSPEC glproxy_wglLoadDisplayColorTableEXT(const GLushort * table, GLuint length);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglLockVideoCaptureDeviceNV(HDC hDc, HVIDEOINPUTDEVICENV hDevice);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglMakeAssociatedContextCurrentAMD(HGLRC hglrc);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglMakeContextCurrentARB(HDC hDrawDC, HDC hReadDC, HGLRC hglrc);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglMakeContextCurrentEXT(HDC hDrawDC, HDC hReadDC, HGLRC hglrc);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglMakeCurrent(HDC hDc, HGLRC newContext);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglQueryCurrentContextNV(int iAttribute, int * piValue);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglQueryFrameCountNV(HDC hDC, GLuint * count);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglQueryFrameLockMasterI3D(BOOL * pFlag);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglQueryFrameTrackingI3D(DWORD * pFrameCount, DWORD * pMissedFrames, float * pLastMissedUsage);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglQueryGenlockMaxSourceDelayI3D(HDC hDC, UINT * uMaxLineDelay, UINT * uMaxPixelDelay);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglQueryMaxSwapGroupsNV(HDC hDC, GLuint * maxGroups, GLuint * maxBarriers);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglQueryPbufferARB(HPBUFFERARB hPbuffer, int iAttribute, int * piValue);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglQueryPbufferEXT(HPBUFFEREXT hPbuffer, int iAttribute, int * piValue);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglQuerySwapGroupNV(HDC hDC, GLuint * group, GLuint * barrier);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglQueryVideoCaptureDeviceNV(HDC hDc, HVIDEOINPUTDEVICENV hDevice, int iAttribute, int * piValue);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglRealizeLayerPalette(HDC hdc, int iLayerPlane, BOOL bRealize);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglReleaseImageBufferEventsI3D(HDC hDC, const LPVOID * pAddress, UINT count);

GLPROXY_IMPORTEXPORT int GLPROXY_CALLSPEC glproxy_wglReleasePbufferDCARB(HPBUFFERARB hPbuffer, HDC hDC);

GLPROXY_IMPORTEXPORT int GLPROXY_CALLSPEC glproxy_wglReleasePbufferDCEXT(HPBUFFEREXT hPbuffer, HDC hDC);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglReleaseTexImageARB(HPBUFFERARB hPbuffer, int iBuffer);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglReleaseVideoCaptureDeviceNV(HDC hDc, HVIDEOINPUTDEVICENV hDevice);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglReleaseVideoDeviceNV(HPVIDEODEV hVideoDevice);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglReleaseVideoImageNV(HPBUFFERARB hPbuffer, int iVideoBuffer);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglResetFrameCountNV(HDC hDC);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglRestoreBufferRegionARB(HANDLE hRegion, int x, int y, int width, int height, int xSrc, int ySrc);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglSaveBufferRegionARB(HANDLE hRegion, int x, int y, int width, int height);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglSendPbufferToVideoNV(HPBUFFERARB hPbuffer, int iBufferType, unsigned long * pulCounterPbuffer, BOOL bBlock);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglSetDigitalVideoParametersI3D(HDC hDC, int iAttribute, const int * piValue);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglSetGammaTableI3D(HDC hDC, int iEntries, const USHORT * puRed, const USHORT * puGreen, const USHORT * puBlue);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglSetGammaTableParametersI3D(HDC hDC, int iAttribute, const int * piValue);

GLPROXY_IMPORTEXPORT int GLPROXY_CALLSPEC glproxy_wglSetLayerPaletteEntries(HDC hdc, int iLayerPlane, int iStart, int cEntries, const COLORREF * pcr);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglSetPbufferAttribARB(HPBUFFERARB hPbuffer, const int * piAttribList);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglSetPixelFormat(HDC hdc, int ipfd, const PIXELFORMATDESCRIPTOR * ppfd);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglSetStereoEmitterState3DL(HDC hDC, UINT uState);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglShareLists(HGLRC hrcSrvShare, HGLRC hrcSrvSource);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglSwapBuffers(HDC hdc);

GLPROXY_IMPORTEXPORT INT64 GLPROXY_CALLSPEC glproxy_wglSwapBuffersMscOML(HDC hdc, INT64 target_msc, INT64 divisor, INT64 remainder);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglSwapIntervalEXT(int interval);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglSwapLayerBuffers(HDC hdc, UINT fuFlags);

GLPROXY_IMPORTEXPORT INT64 GLPROXY_CALLSPEC glproxy_wglSwapLayerBuffersMscOML(HDC hdc, int fuPlanes, INT64 target_msc, INT64 divisor, INT64 remainder);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglUseFontBitmapsA(HDC hDC, DWORD first, DWORD count, DWORD listBase);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglUseFontBitmapsW(HDC hDC, DWORD first, DWORD count, DWORD listBase);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglUseFontOutlines(HDC hDC, DWORD first, DWORD count, DWORD listBase, FLOAT deviation, FLOAT extrusion, int format, LPGLYPHMETRICSFLOAT lpgmf);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglUseFontOutlinesA(HDC hDC, DWORD first, DWORD count, DWORD listBase, FLOAT deviation, FLOAT extrusion, int format, LPGLYPHMETRICSFLOAT lpgmf);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglUseFontOutlinesW(HDC hDC, DWORD first, DWORD count, DWORD listBase, FLOAT deviation, FLOAT extrusion, int format, LPGLYPHMETRICSFLOAT lpgmf);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglWaitForMscOML(HDC hdc, INT64 target_msc, INT64 divisor, INT64 remainder, INT64 * ust, INT64 * msc, INT64 * sbc);

GLPROXY_IMPORTEXPORT BOOL GLPROXY_CALLSPEC glproxy_wglWaitForSbcOML(HDC hdc, INT64 target_sbc, INT64 * ust, INT64 * msc, INT64 * sbc);

#define wglAllocateMemoryNV glproxy_wglAllocateMemoryNV
#define wglAssociateImageBufferEventsI3D glproxy_wglAssociateImageBufferEventsI3D
#define wglBeginFrameTrackingI3D glproxy_wglBeginFrameTrackingI3D
#define wglBindDisplayColorTableEXT glproxy_wglBindDisplayColorTableEXT
#define wglBindSwapBarrierNV glproxy_wglBindSwapBarrierNV
#define wglBindTexImageARB glproxy_wglBindTexImageARB
#define wglBindVideoCaptureDeviceNV glproxy_wglBindVideoCaptureDeviceNV
#define wglBindVideoDeviceNV glproxy_wglBindVideoDeviceNV
#define wglBindVideoImageNV glproxy_wglBindVideoImageNV
#define wglBlitContextFramebufferAMD glproxy_wglBlitContextFramebufferAMD
#define wglChoosePixelFormat glproxy_wglChoosePixelFormat
#define wglChoosePixelFormatARB glproxy_wglChoosePixelFormatARB
#define wglChoosePixelFormatEXT glproxy_wglChoosePixelFormatEXT
#define wglCopyContext glproxy_wglCopyContext
#define wglCopyImageSubDataNV glproxy_wglCopyImageSubDataNV
#define wglCreateAffinityDCNV glproxy_wglCreateAffinityDCNV
#define wglCreateAssociatedContextAMD glproxy_wglCreateAssociatedContextAMD
#define wglCreateAssociatedContextAttribsAMD glproxy_wglCreateAssociatedContextAttribsAMD
#define wglCreateBufferRegionARB glproxy_wglCreateBufferRegionARB
#define wglCreateContext glproxy_wglCreateContext
#define wglCreateContextAttribsARB glproxy_wglCreateContextAttribsARB
#define wglCreateDisplayColorTableEXT glproxy_wglCreateDisplayColorTableEXT
#define wglCreateImageBufferI3D glproxy_wglCreateImageBufferI3D
#define wglCreateLayerContext glproxy_wglCreateLayerContext
#define wglCreatePbufferARB glproxy_wglCreatePbufferARB
#define wglCreatePbufferEXT glproxy_wglCreatePbufferEXT
#define wglDXCloseDeviceNV glproxy_wglDXCloseDeviceNV
#define wglDXLockObjectsNV glproxy_wglDXLockObjectsNV
#define wglDXObjectAccessNV glproxy_wglDXObjectAccessNV
#define wglDXOpenDeviceNV glproxy_wglDXOpenDeviceNV
#define wglDXRegisterObjectNV glproxy_wglDXRegisterObjectNV
#define wglDXSetResourceShareHandleNV glproxy_wglDXSetResourceShareHandleNV
#define wglDXUnlockObjectsNV glproxy_wglDXUnlockObjectsNV
#define wglDXUnregisterObjectNV glproxy_wglDXUnregisterObjectNV
#define wglDelayBeforeSwapNV glproxy_wglDelayBeforeSwapNV
#define wglDeleteAssociatedContextAMD glproxy_wglDeleteAssociatedContextAMD
#define wglDeleteBufferRegionARB glproxy_wglDeleteBufferRegionARB
#define wglDeleteContext glproxy_wglDeleteContext
#define wglDeleteDCNV glproxy_wglDeleteDCNV
#define wglDescribeLayerPlane glproxy_wglDescribeLayerPlane
#define wglDescribePixelFormat glproxy_wglDescribePixelFormat
#define wglDestroyDisplayColorTableEXT glproxy_wglDestroyDisplayColorTableEXT
#define wglDestroyImageBufferI3D glproxy_wglDestroyImageBufferI3D
#define wglDestroyPbufferARB glproxy_wglDestroyPbufferARB
#define wglDestroyPbufferEXT glproxy_wglDestroyPbufferEXT
#define wglDisableFrameLockI3D glproxy_wglDisableFrameLockI3D
#define wglDisableGenlockI3D glproxy_wglDisableGenlockI3D
#define wglEnableFrameLockI3D glproxy_wglEnableFrameLockI3D
#define wglEnableGenlockI3D glproxy_wglEnableGenlockI3D
#define wglEndFrameTrackingI3D glproxy_wglEndFrameTrackingI3D
#define wglEnumGpuDevicesNV glproxy_wglEnumGpuDevicesNV
#define wglEnumGpusFromAffinityDCNV glproxy_wglEnumGpusFromAffinityDCNV
#define wglEnumGpusNV glproxy_wglEnumGpusNV
#define wglEnumerateVideoCaptureDevicesNV glproxy_wglEnumerateVideoCaptureDevicesNV
#define wglEnumerateVideoDevicesNV glproxy_wglEnumerateVideoDevicesNV
#define wglFreeMemoryNV glproxy_wglFreeMemoryNV
#define wglGenlockSampleRateI3D glproxy_wglGenlockSampleRateI3D
#define wglGenlockSourceDelayI3D glproxy_wglGenlockSourceDelayI3D
#define wglGenlockSourceEdgeI3D glproxy_wglGenlockSourceEdgeI3D
#define wglGenlockSourceI3D glproxy_wglGenlockSourceI3D
#define wglGetContextGPUIDAMD glproxy_wglGetContextGPUIDAMD
#define wglGetCurrentAssociatedContextAMD glproxy_wglGetCurrentAssociatedContextAMD
#define wglGetCurrentContext glproxy_wglGetCurrentContext
#define wglGetCurrentDC glproxy_wglGetCurrentDC
#define wglGetCurrentReadDCARB glproxy_wglGetCurrentReadDCARB
#define wglGetCurrentReadDCEXT glproxy_wglGetCurrentReadDCEXT
#define wglGetDefaultProcAddress glproxy_wglGetDefaultProcAddress
#define wglGetDigitalVideoParametersI3D glproxy_wglGetDigitalVideoParametersI3D
#define wglGetEnhMetaFilePixelFormat glproxy_wglGetEnhMetaFilePixelFormat
#define wglGetExtensionsStringARB glproxy_wglGetExtensionsStringARB
#define wglGetExtensionsStringEXT glproxy_wglGetExtensionsStringEXT
#define wglGetFrameUsageI3D glproxy_wglGetFrameUsageI3D
#define wglGetGPUIDsAMD glproxy_wglGetGPUIDsAMD
#define wglGetGPUInfoAMD glproxy_wglGetGPUInfoAMD
#define wglGetGammaTableI3D glproxy_wglGetGammaTableI3D
#define wglGetGammaTableParametersI3D glproxy_wglGetGammaTableParametersI3D
#define wglGetGenlockSampleRateI3D glproxy_wglGetGenlockSampleRateI3D
#define wglGetGenlockSourceDelayI3D glproxy_wglGetGenlockSourceDelayI3D
#define wglGetGenlockSourceEdgeI3D glproxy_wglGetGenlockSourceEdgeI3D
#define wglGetGenlockSourceI3D glproxy_wglGetGenlockSourceI3D
#define wglGetLayerPaletteEntries glproxy_wglGetLayerPaletteEntries
#define wglGetMscRateOML glproxy_wglGetMscRateOML
#define wglGetPbufferDCARB glproxy_wglGetPbufferDCARB
#define wglGetPbufferDCEXT glproxy_wglGetPbufferDCEXT
#define wglGetPixelFormat glproxy_wglGetPixelFormat
#define wglGetPixelFormatAttribfvARB glproxy_wglGetPixelFormatAttribfvARB
#define wglGetPixelFormatAttribfvEXT glproxy_wglGetPixelFormatAttribfvEXT
#define wglGetPixelFormatAttribivARB glproxy_wglGetPixelFormatAttribivARB
#define wglGetPixelFormatAttribivEXT glproxy_wglGetPixelFormatAttribivEXT
#define wglGetProcAddress glproxy_wglGetProcAddress
#define wglGetSwapIntervalEXT glproxy_wglGetSwapIntervalEXT
#define wglGetSyncValuesOML glproxy_wglGetSyncValuesOML
#define wglGetVideoDeviceNV glproxy_wglGetVideoDeviceNV
#define wglGetVideoInfoNV glproxy_wglGetVideoInfoNV
#define wglIsEnabledFrameLockI3D glproxy_wglIsEnabledFrameLockI3D
#define wglIsEnabledGenlockI3D glproxy_wglIsEnabledGenlockI3D
#define wglJoinSwapGroupNV glproxy_wglJoinSwapGroupNV
#define wglLoadDisplayColorTableEXT glproxy_wglLoadDisplayColorTableEXT
#define wglLockVideoCaptureDeviceNV glproxy_wglLockVideoCaptureDeviceNV
#define wglMakeAssociatedContextCurrentAMD glproxy_wglMakeAssociatedContextCurrentAMD
#define wglMakeContextCurrentARB glproxy_wglMakeContextCurrentARB
#define wglMakeContextCurrentEXT glproxy_wglMakeContextCurrentEXT
#define wglMakeCurrent glproxy_wglMakeCurrent
#define wglQueryCurrentContextNV glproxy_wglQueryCurrentContextNV
#define wglQueryFrameCountNV glproxy_wglQueryFrameCountNV
#define wglQueryFrameLockMasterI3D glproxy_wglQueryFrameLockMasterI3D
#define wglQueryFrameTrackingI3D glproxy_wglQueryFrameTrackingI3D
#define wglQueryGenlockMaxSourceDelayI3D glproxy_wglQueryGenlockMaxSourceDelayI3D
#define wglQueryMaxSwapGroupsNV glproxy_wglQueryMaxSwapGroupsNV
#define wglQueryPbufferARB glproxy_wglQueryPbufferARB
#define wglQueryPbufferEXT glproxy_wglQueryPbufferEXT
#define wglQuerySwapGroupNV glproxy_wglQuerySwapGroupNV
#define wglQueryVideoCaptureDeviceNV glproxy_wglQueryVideoCaptureDeviceNV
#define wglRealizeLayerPalette glproxy_wglRealizeLayerPalette
#define wglReleaseImageBufferEventsI3D glproxy_wglReleaseImageBufferEventsI3D
#define wglReleasePbufferDCARB glproxy_wglReleasePbufferDCARB
#define wglReleasePbufferDCEXT glproxy_wglReleasePbufferDCEXT
#define wglReleaseTexImageARB glproxy_wglReleaseTexImageARB
#define wglReleaseVideoCaptureDeviceNV glproxy_wglReleaseVideoCaptureDeviceNV
#define wglReleaseVideoDeviceNV glproxy_wglReleaseVideoDeviceNV
#define wglReleaseVideoImageNV glproxy_wglReleaseVideoImageNV
#define wglResetFrameCountNV glproxy_wglResetFrameCountNV
#define wglRestoreBufferRegionARB glproxy_wglRestoreBufferRegionARB
#define wglSaveBufferRegionARB glproxy_wglSaveBufferRegionARB
#define wglSendPbufferToVideoNV glproxy_wglSendPbufferToVideoNV
#define wglSetDigitalVideoParametersI3D glproxy_wglSetDigitalVideoParametersI3D
#define wglSetGammaTableI3D glproxy_wglSetGammaTableI3D
#define wglSetGammaTableParametersI3D glproxy_wglSetGammaTableParametersI3D
#define wglSetLayerPaletteEntries glproxy_wglSetLayerPaletteEntries
#define wglSetPbufferAttribARB glproxy_wglSetPbufferAttribARB
#define wglSetPixelFormat glproxy_wglSetPixelFormat
#define wglSetStereoEmitterState3DL glproxy_wglSetStereoEmitterState3DL
#define wglShareLists glproxy_wglShareLists
#define wglSwapBuffers glproxy_wglSwapBuffers
#define wglSwapBuffersMscOML glproxy_wglSwapBuffersMscOML
#define wglSwapIntervalEXT glproxy_wglSwapIntervalEXT
#define wglSwapLayerBuffers glproxy_wglSwapLayerBuffers
#define wglSwapLayerBuffersMscOML glproxy_wglSwapLayerBuffersMscOML
#define wglUseFontBitmapsA glproxy_wglUseFontBitmapsA
#define wglUseFontBitmapsW glproxy_wglUseFontBitmapsW
#define wglUseFontOutlines glproxy_wglUseFontOutlines
#define wglUseFontOutlinesA glproxy_wglUseFontOutlinesA
#define wglUseFontOutlinesW glproxy_wglUseFontOutlinesW
#define wglWaitForMscOML glproxy_wglWaitForMscOML
#define wglWaitForSbcOML glproxy_wglWaitForSbcOML

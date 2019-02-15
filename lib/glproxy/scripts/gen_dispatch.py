#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Copyright © 2013 Intel Corporation
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice (including the next
# paragraph) shall be included in all copies or substantial portions of the
# Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.

import sys
import argparse
import xml.etree.ElementTree as ET
import re
import os

class GLProvider(object):
    def __init__(self, condition, name):
        # A dict describing the condition.
        self.condition = condition

        # The name of the function to be loaded (possibly an
        # ARB/EXT/whatever-decorated variant).
        self.name = name
        if 'extension' in condition:
            self.sort_key = '2extension:' + condition['extension']
        elif 'version' in condition:
            self.sort_key = '1version:' + '{0:08d}'.format(condition['version'])
        else:
            self.sort_key = '0direct:'
        self.condition_name = self.sort_key

other_extensions = '''WGL_EXT_depth_float
WGL_ARB_buffer_region
WGL_ARB_extensions_string
WGL_ARB_make_current_read
WGL_ARB_pixel_format
WGL_ARB_pbuffer
WGL_EXT_extensions_string
WGL_EXT_swap_control
WGL_EXT_swap_control_tear
WGL_ARB_multisample
WGL_ARB_pixel_format_float
WGL_ARB_framebuffer_sRGB
WGL_ARB_create_context
WGL_ARB_create_context_profile
WGL_EXT_pixel_format_packed_float
WGL_EXT_create_context_es_profile
WGL_EXT_create_context_es2_profile
WGL_NV_DX_interop
WGL_INTEL_cl_sharing
WGL_NV_DX_interop2
WGL_ARB_create_context_robustness
GL_EXT_static_vertex_array
GL_EXT_vertex_array_set
GL_EXT_vertex_array_setXXX
GL_SGIX_fog_texture
GL_SGIX_fragment_specular_lighting
GL_EXT_static_vertex_array
GL_EXT_vertex_array_set
GL_EXT_vertex_array_setXXX
GL_SGIX_fog_texture
GL_SGIX_fragment_specular_lighting
GL_EXT_abgr
GL_EXT_blend_color
GL_EXT_polygon_offset
GL_EXT_texture
GL_EXT_texture3D
GL_SGIS_texture_filter4
GL_EXT_subtexture
GL_EXT_copy_texture
GL_EXT_histogram
GL_EXT_convolution
GL_SGI_color_matrix
GL_SGI_color_table
GL_SGIS_pixel_texture
GL_SGIX_pixel_texture
GL_SGIS_texture4D
GL_SGI_texture_color_table
GL_EXT_cmyka
GL_EXT_texture_object
GL_SGIS_detail_texture
GL_SGIS_sharpen_texture
GL_EXT_packed_pixels
GL_SGIS_texture_lod
GL_SGIS_multisample 
GLX_SGIS_multisample
GL_EXT_rescale_normal
GLX_EXT_visual_info
GL_EXT_vertex_array
GL_EXT_misc_attribute
GL_SGIS_generate_mipmap
GL_SGIX_clipmap
GL_SGIX_shadow
GL_SGIS_texture_edge_clamp
GL_SGIS_texture_border_clamp
GL_EXT_blend_minmax
GL_EXT_blend_subtract
GL_EXT_blend_logic_op
GLX_SGI_swap_control
GLX_SGI_video_sync
GLX_SGI_make_current_read
GLX_SGIX_video_source
GLX_EXT_visual_rating
GL_SGIX_interlace
GLX_EXT_import_context
GLX_SGIX_fbconfig
GLX_SGIX_pbuffer
GL_SGIS_texture_select
GL_SGIX_sprite
GL_SGIX_texture_multi_buffer
GL_EXT_point_parameters
GL_SGIX_instruments
GL_SGIX_texture_scale_bias
GL_SGIX_framezoom
GL_SGIX_tag_sample_buffer
GL_SGIX_reference_plane
GL_SGIX_flush_raster
GLX_SGI_cushion
GL_SGIX_depth_texture
GL_SGIS_fog_function
GL_SGIX_fog_offset
GL_HP_image_transform
GL_HP_convolution_border_modes
GL_SGIX_texture_add_env
GL_EXT_color_subtable
GLU_EXT_object_space_tess
GL_PGI_vertex_hints
GL_PGI_misc_hints
GL_EXT_paletted_texture
GL_EXT_clip_volume_hint
GL_SGIX_list_priority
GL_SGIX_ir_instrument1
GLX_SGIX_video_resize
GL_SGIX_texture_lod_bias
GLU_SGI_filter4_parameters
GLX_SGIX_dm_buffer
GL_SGIX_shadow_ambient
GLX_SGIX_swap_group
GLX_SGIX_swap_barrier
GL_EXT_index_texture
GL_EXT_index_material
GL_EXT_index_func
GL_EXT_index_array_formats
GL_EXT_compiled_vertex_array
GL_EXT_cull_vertex
GLU_EXT_nurbs_tessellator
GL_SGIX_ycrcb
GL_EXT_fragment_lighting
GL_IBM_rasterpos_clip
GL_HP_texture_lighting
GL_EXT_draw_range_elements
GL_WIN_phong_shading
GL_WIN_specular_fog
GLX_SGIS_color_range 
GL_SGIS_color_range
GL_EXT_light_texture
GL_SGIX_blend_alpha_minmax
GL_EXT_scene_marker 
GLX_EXT_scene_marker
GL_SGIX_pixel_texture_bits
GL_EXT_bgra
GL_SGIX_async
GL_SGIX_async_pixel
GL_SGIX_async_histogram
GL_INTEL_texture_scissor
GL_INTEL_parallel_arrays
GL_HP_occlusion_test
GL_EXT_pixel_transform
GL_EXT_pixel_transform_color_table
GL_EXT_shared_texture_palette
GLX_SGIS_blended_overlay
GL_EXT_separate_specular_color
GL_EXT_secondary_color
GL_EXT_texture_env
GL_EXT_texture_perturb_normal
GL_EXT_multi_draw_arrays 
GL_SUN_multi_draw_arrays
GL_EXT_fog_coord
GL_REND_screen_coordinates
GL_EXT_coordinate_frame
GL_EXT_texture_env_combine
GL_APPLE_specular_vector
GL_APPLE_transform_hint
GL_SUNX_constant_data
GL_SUN_global_alpha
GL_SUN_triangle_list
GL_SUN_vertex
WGL_EXT_display_color_table
WGL_EXT_extensions_string
WGL_EXT_make_current_read
WGL_EXT_pixel_format
WGL_EXT_pbuffer
WGL_EXT_swap_control
GL_EXT_blend_func_separate
GL_INGR_color_clamp
GL_INGR_interlace_read
GL_EXT_stencil_wrap
WGL_EXT_depth_float
GL_EXT_422_pixels
GL_NV_texgen_reflection
GL_SGIX_texture_range
GL_SUN_convolution_border_modes
GLX_SUN_get_transparent_index
GL_EXT_texture_env_add
GL_EXT_texture_lod_bias
GL_EXT_texture_filter_anisotropic
GL_EXT_vertex_weighting
GL_NV_light_max_exponent
GL_NV_vertex_array_range
GL_NV_register_combiners
GL_NV_fog_distance
GL_NV_texgen_emboss
GL_NV_blend_square
GL_NV_texture_env_combine4
GL_MESA_resize_buffers
GL_MESA_window_pos
GL_EXT_texture_compression_s3tc
GL_IBM_cull_vertex
GL_IBM_multimode_draw_arrays
GL_IBM_vertex_array_lists
GL_3DFX_texture_compression_FXT1
GL_3DFX_multisample
GL_3DFX_tbuffer
WGL_EXT_multisample 
GL_EXT_multisample
GL_SGIX_vertex_preclip 
GL_SGIX_vertex_preclip_hint
GL_SGIX_convolution_accuracy
GL_SGIX_resample
GL_SGIS_point_line_texgen
GL_SGIS_texture_color_mask
GLX_MESA_copy_sub_buffer
GLX_MESA_pixmap_colormap
GLX_MESA_release_buffers
GLX_MESA_set_3dfx_mode
GL_EXT_texture_env_dot3
GL_ATI_texture_mirror_once
GL_NV_fence
GL_IBM_static_data
GL_IBM_texture_mirrored_repeat
GL_NV_evaluators
GL_NV_packed_depth_stencil
GL_NV_register_combiners2
GL_NV_texture_compression_vtc
GL_NV_texture_rectangle
GL_NV_texture_shader
GL_NV_texture_shader2
GL_NV_vertex_array_range2
GL_NV_vertex_program
GLX_SGIX_visual_select_group
GL_SGIX_texture_coordinate_clamp
GLX_OML_swap_method
GLX_OML_sync_control
GL_OML_interlace
GL_OML_subsample
GL_OML_resample
WGL_OML_sync_control
GL_NV_copy_depth_to_color
GL_ATI_envmap_bumpmap
GL_ATI_fragment_shader
GL_ATI_pn_triangles
GL_ATI_vertex_array_object
GL_EXT_vertex_shader
GL_ATI_vertex_streams
WGL_I3D_digital_video_control
WGL_I3D_gamma
WGL_I3D_genlock
WGL_I3D_image_buffer
WGL_I3D_swap_frame_lock
WGL_I3D_swap_frame_usage
GL_ATI_element_array
GL_SUN_mesh_array
GL_SUN_slice_accum
GL_NV_multisample_filter_hint
GL_NV_depth_clamp
GL_NV_occlusion_query
GL_NV_point_sprite
WGL_NV_render_depth_texture
WGL_NV_render_texture_rectangle
GL_NV_texture_shader3
GL_NV_vertex_program1_1
GL_EXT_shadow_funcs
GL_EXT_stencil_two_side
GL_ATI_text_fragment_shader
GL_APPLE_client_storage
GL_APPLE_element_array
GL_APPLE_fence
GL_APPLE_vertex_array_object
GL_APPLE_vertex_array_range
GL_APPLE_ycbcr_422
GL_S3_s3tc
GL_ATI_draw_buffers
WGL_ATI_pixel_format_float
GL_ATI_texture_env_combine3
GL_ATI_texture_float
GL_NV_float_buffer 
WGL_NV_float_buffer
GL_NV_fragment_program
GL_NV_half_float
GL_NV_pixel_data_range
GL_NV_primitive_restart
GL_NV_texture_expand_normal
GL_NV_vertex_program2
GL_ATI_map_object_buffer
GL_ATI_separate_stencil
GL_ATI_vertex_attrib_array_object
GL_OES_byte_coordinates
GL_OES_fixed_point
GL_OES_single_precision
GL_OES_compressed_paletted_texture
GL_OES_read_format
GL_OES_query_matrix
GL_EXT_depth_bounds_test
GL_EXT_texture_mirror_clamp
GL_EXT_blend_equation_separate
GL_MESA_pack_invert
GL_MESA_ycbcr_texture
GL_EXT_pixel_buffer_object
GL_NV_fragment_program_option
GL_NV_fragment_program2
GL_NV_vertex_program2_option
GL_NV_vertex_program3
GLX_SGIX_hyperpipe
GLX_MESA_agp_offset
GL_EXT_texture_compression_dxt1
GL_EXT_framebuffer_object
GL_GREMEDY_string_marker
GL_EXT_packed_depth_stencil
WGL_3DL_stereo_control
GL_EXT_stencil_clear_tag
GL_EXT_texture_sRGB
GL_EXT_framebuffer_blit
GL_EXT_framebuffer_multisample
GL_MESAX_texture_stack
GL_EXT_timer_query
GL_EXT_gpu_program_parameters
GL_APPLE_flush_buffer_range
GL_NV_gpu_program4
GL_NV_geometry_program4
GL_EXT_geometry_shader4
GL_NV_vertex_program4
GL_EXT_gpu_shader4
GL_EXT_draw_instanced
GL_EXT_packed_float 
WGL_EXT_pixel_format_packed_float 
GLX_EXT_fbconfig_packed_float
GL_EXT_texture_array
GL_EXT_texture_buffer_object
GL_EXT_texture_compression_latc
GL_EXT_texture_compression_rgtc
GL_EXT_texture_shared_exponent
GL_NV_depth_buffer_float
GL_NV_fragment_program4
GL_NV_framebuffer_multisample_coverage
GL_EXT_framebuffer_sRGB 
GLX_EXT_framebuffer_sRGB 
WGL_EXT_framebuffer_sRGB
GL_NV_geometry_shader4
GL_NV_parameter_buffer_object
GL_EXT_draw_buffers2
GL_NV_transform_feedback
GL_EXT_bindable_uniform
GL_EXT_texture_integer
GLX_EXT_texture_from_pixmap
GL_GREMEDY_frame_terminator
GL_NV_conditional_render
GL_NV_present_video 
GLX_NV_present_video 
WGL_NV_present_video
GLX_NV_video_out
WGL_NV_video_output
GLX_NV_swap_group
WGL_NV_swap_group
GL_EXT_transform_feedback
GL_EXT_direct_state_access
GL_EXT_vertex_array_bgra
WGL_NV_gpu_affinity
GL_EXT_texture_swizzle
GL_NV_explicit_multisample
GL_NV_transform_feedback2
GL_ATI_meminfo
GL_AMD_performance_monitor
WGL_AMD_gpu_association
GL_AMD_texture_texture4
GL_AMD_vertex_shader_tessellator
GL_EXT_provoking_vertex
GL_EXT_texture_snorm
GL_AMD_draw_buffers_blend
GL_APPLE_texture_range
GL_APPLE_float_pixels
GL_APPLE_vertex_program_evaluators
GL_APPLE_aux_depth_stencil
GL_APPLE_object_purgeable
GL_APPLE_row_bytes
GL_APPLE_rgb_422
GL_NV_video_capture 
GLX_NV_video_capture 
WGL_NV_video_capture
GL_EXT_swap_control
GL_NV_copy_image 
WGL_NV_copy_image 
GLX_NV_copy_image
GL_EXT_separate_shader_objects
GL_NV_parameter_buffer_object2
GL_NV_shader_buffer_load
GL_NV_vertex_buffer_unified_memory
GL_NV_texture_barrier
GL_AMD_shader_stencil_export
GL_AMD_seamless_cubemap_per_texture
GLX_INTEL_swap_event
GL_AMD_conservative_depth
GL_EXT_shader_image_load_store
GL_EXT_vertex_attrib_64bit
GL_NV_gpu_program5
GL_NV_gpu_shader5
GL_NV_shader_buffer_store
GL_NV_tessellation_program5
GL_NV_vertex_attrib_integer_64bit
GL_NV_multisample_coverage
GL_AMD_name_gen_delete
GL_AMD_debug_output
GL_NV_vdpau_interop
GL_AMD_transform_feedback3_lines_triangles
GLX_AMD_gpu_association
GLX_EXT_create_context_es2_profile 
GLX_EXT_create_context_es_profile
WGL_EXT_create_context_es2_profile 
WGL_EXT_create_context_es_profile
GL_AMD_depth_clamp_separate
GL_EXT_texture_sRGB_decode
GL_NV_texture_multisample
GL_AMD_blend_minmax_factor
GL_AMD_sample_positions
GL_EXT_x11_sync_object
WGL_NV_DX_interop
GL_AMD_multi_draw_indirect
GL_EXT_framebuffer_multisample_blit_scaled
GL_NV_path_rendering
GL_AMD_pinned_memory
WGL_NV_DX_interop2
GL_AMD_stencil_operation_extended
GLX_EXT_swap_control_tear
WGL_EXT_swap_control_tear
GL_AMD_vertex_shader_viewport_index
GL_AMD_vertex_shader_layer
GL_NV_bindless_texture
GL_NV_shader_atomic_float
GL_AMD_query_buffer_object
GL_NV_compute_program5
GL_NV_shader_storage_buffer_object
GL_NV_shader_atomic_counters
GL_NV_deep_texture3D
GL_NVX_conditional_render
GL_AMD_sparse_texture
GLX_EXT_buffer_age
GL_AMD_shader_trinary_minmax
GL_INTEL_map_texture
GL_NV_draw_texture
GL_AMD_interleaved_elements
GL_NV_bindless_multi_draw_indirect
GL_NV_blend_equation_advanced 
GL_NV_blend_equation_advanced_coherent
GL_NV_gpu_program5_mem_extended
GL_AMD_shader_atomic_counter_ops
WGL_NV_delay_before_swap
GL_EXT_shader_integer_mix
GL_NVX_gpu_memory_info
GL_EXT_debug_label
GL_EXT_debug_marker
GL_INTEL_fragment_shader_ordering
GL_AMD_occlusion_query_event
GL_INTEL_performance_query
GL_AMD_shader_stencil_value_export
GLX_NV_delay_before_swap
GLX_MESA_query_renderer
GL_NV_shader_thread_group
GL_NV_shader_thread_shuffle
GL_EXT_shader_image_load_formatted
GL_AMD_transform_feedback4
GL_AMD_gpu_shader_int64
GL_EXT_glx_stereo_tree
GL_AMD_gcn_shader
GL_NV_shader_atomic_int64
GL_NV_bindless_multi_draw_indirect_count
GLX_NV_copy_buffer
GL_NV_uniform_buffer_unified_memory
GL_EXT_polygon_offset_clamp
GL_EXT_post_depth_coverage
GL_EXT_raster_multisample
GL_EXT_sparse_texture2
GL_EXT_texture_filter_minmax
GL_NV_conservative_raster
GL_NV_fill_rectangle
GL_NV_fragment_coverage_to_color
GL_NV_fragment_shader_interlock
GL_NV_framebuffer_mixed_samples
GL_NV_geometry_shader_passthrough
GL_NV_path_rendering_shared_edge
GL_NV_sample_locations
GL_NV_sample_mask_override_coverage
GL_NV_shader_atomic_fp16_vector
GL_NV_internalformat_sample_query
GL_NV_viewport_array2
GL_NV_command_list
GL_OVR_multiview
GL_OVR_multiview2
GL_NV_conservative_raster_dilate
GL_INTEL_framebuffer_CMAA
GLX_EXT_libglvnd
GL_NV_viewport_swizzle
GL_NV_robustness_video_memory_purge
GL_AMD_shader_explicit_vertex_parameter
GL_NV_clip_space_w_scaling
GL_NV_conservative_raster_pre_snap_triangles
GL_NV_shader_atomic_float64
GL_NV_stereo_view_rendering
GL_EXT_window_rectangles
GL_INTEL_conservative_rasterization
GL_NVX_blend_equation_advanced_multi_draw_buffers
GL_NVX_linked_gpu_multicast
GL_NV_gpu_multicast
GL_MESA_shader_integer_functions
GL_AMD_gpu_shader_half_float
GL_AMD_shader_ballot
GL_ARB_multitexture
GLX_ARB_get_proc_address
GL_ARB_transpose_matrix
WGL_ARB_buffer_region
GL_ARB_multisample 
GLX_ARB_multisample 
WGL_ARB_multisample
GL_ARB_texture_env_add
GL_ARB_texture_cube_map
WGL_ARB_extensions_string
WGL_ARB_pixel_format
WGL_ARB_make_current_read
WGL_ARB_pbuffer
GL_ARB_texture_compression
GL_ARB_texture_border_clamp
GL_ARB_point_parameters
GL_ARB_vertex_blend
GL_ARB_matrix_palette
GL_ARB_texture_env_combine
GL_ARB_texture_env_crossbar
GL_ARB_texture_env_dot3
WGL_ARB_render_texture
GL_ARB_texture_mirrored_repeat
GL_ARB_depth_texture
GL_ARB_shadow
GL_ARB_shadow_ambient
GL_ARB_window_pos
GL_ARB_vertex_program
GL_ARB_fragment_program
GL_ARB_vertex_buffer_object 
GLX_ARB_vertex_buffer_object
GL_ARB_occlusion_query
GL_ARB_shader_objects
GL_ARB_vertex_shader
GL_ARB_fragment_shader
GL_ARB_shading_language_100
GL_ARB_texture_non_power_of_two
GL_ARB_point_sprite
GL_ARB_fragment_program_shadow
GL_ARB_draw_buffers
GL_ARB_texture_rectangle
GL_ARB_color_buffer_float 
WGL_ARB_pixel_format_float 
GLX_ARB_fbconfig_float
GL_ARB_half_float_pixel
GL_ARB_texture_float
GL_ARB_pixel_buffer_object
GL_ARB_depth_buffer_float
GL_ARB_draw_instanced
GL_ARB_framebuffer_object
GL_ARB_framebuffer_sRGB 
GLX_ARB_framebuffer_sRGB 
WGL_ARB_framebuffer_sRGB
GL_ARB_geometry_shader4
GL_ARB_half_float_vertex
GL_ARB_instanced_arrays
GL_ARB_map_buffer_range
GL_ARB_texture_buffer_object
GL_ARB_texture_compression_rgtc
GL_ARB_texture_rg
GL_ARB_vertex_array_object
WGL_ARB_create_context
GLX_ARB_create_context
GL_ARB_uniform_buffer_object
GL_ARB_compatibility
GL_ARB_copy_buffer
GL_ARB_shader_texture_lod
GL_ARB_depth_clamp
GL_ARB_draw_elements_base_vertex
GL_ARB_fragment_coord_conventions
GL_ARB_provoking_vertex
GL_ARB_seamless_cube_map
GL_ARB_sync
GL_ARB_texture_multisample
GL_ARB_vertex_array_bgra
GL_ARB_draw_buffers_blend
GL_ARB_sample_shading
GL_ARB_texture_cube_map_array
GL_ARB_texture_gather
GL_ARB_texture_query_lod
WGL_ARB_create_context_profile
GLX_ARB_create_context_profile
GL_ARB_shading_language_include
GL_ARB_texture_compression_bptc
GL_ARB_blend_func_extended
GL_ARB_explicit_attrib_location
GL_ARB_occlusion_query2
GL_ARB_sampler_objects
GL_ARB_shader_bit_encoding
GL_ARB_texture_rgb10_a2ui
GL_ARB_texture_swizzle
GL_ARB_timer_query
GL_ARB_vertex_type_2_10_10_10_rev
GL_ARB_draw_indirect
GL_ARB_gpu_shader5
GL_ARB_gpu_shader_fp64
GL_ARB_shader_subroutine
GL_ARB_tessellation_shader
GL_ARB_texture_buffer_object_rgb32
GL_ARB_transform_feedback2
GL_ARB_transform_feedback3
GL_ARB_ES2_compatibility
GL_ARB_get_program_binary
GL_ARB_separate_shader_objects
GL_ARB_shader_precision
GL_ARB_vertex_attrib_64bit
GL_ARB_viewport_array
GLX_ARB_create_context_robustness
WGL_ARB_create_context_robustness
GL_ARB_cl_event
GL_ARB_debug_output
GL_ARB_robustness
GL_ARB_shader_stencil_export
GL_ARB_base_instance
GL_ARB_shading_language_420pack
GL_ARB_transform_feedback_instanced
GL_ARB_compressed_texture_pixel_storage
GL_ARB_conservative_depth
GL_ARB_internalformat_query
GL_ARB_map_buffer_alignment
GL_ARB_shader_atomic_counters
GL_ARB_shader_image_load_store
GL_ARB_shading_language_packing
GL_ARB_texture_storage
GL_KHR_texture_compression_astc_hdr 
GL_KHR_texture_compression_astc_ldr
GL_KHR_debug
GL_ARB_arrays_of_arrays
GL_ARB_clear_buffer_object
GL_ARB_compute_shader
GL_ARB_copy_image
GL_ARB_texture_view
GL_ARB_vertex_attrib_binding
GL_ARB_robustness_isolation
GL_ARB_ES3_compatibility
GL_ARB_explicit_uniform_location
GL_ARB_fragment_layer_viewport
GL_ARB_framebuffer_no_attachments
GL_ARB_internalformat_query2
GL_ARB_invalidate_subdata
GL_ARB_multi_draw_indirect
GL_ARB_program_interface_query
GL_ARB_robust_buffer_access_behavior
GL_ARB_shader_image_size
GL_ARB_shader_storage_buffer_object
GL_ARB_stencil_texturing
GL_ARB_texture_buffer_range
GL_ARB_texture_query_levels
GL_ARB_texture_storage_multisample
GLX_ARB_robustness_application_isolation 
GLX_ARB_robustness_share_group_isolation
WGL_ARB_robustness_application_isolation 
WGL_ARB_robustness_share_group_isolation
GL_ARB_buffer_storage
GL_ARB_clear_texture
GL_ARB_enhanced_layouts
GL_ARB_multi_bind
GL_ARB_query_buffer_object
GL_ARB_texture_mirror_clamp_to_edge
GL_ARB_texture_stencil8
GL_ARB_vertex_type_10f_11f_11f_rev
GL_ARB_bindless_texture
GL_ARB_compute_variable_group_size
GL_ARB_indirect_parameters
GL_ARB_seamless_cubemap_per_texture
GL_ARB_shader_draw_parameters
GL_ARB_shader_group_vote
GL_ARB_sparse_texture
GL_ARB_ES3_1_compatibility
GL_ARB_clip_control
GL_ARB_conditional_render_inverted
GL_ARB_cull_distance
GL_ARB_derivative_control
GL_ARB_direct_state_access
GL_ARB_get_texture_sub_image
GL_ARB_shader_texture_image_samples
GL_ARB_texture_barrier
GL_KHR_context_flush_control 
GLX_ARB_context_flush_control 
WGL_ARB_context_flush_control
GL_KHR_robust_buffer_access_behavior
GL_KHR_robustness
GL_ARB_pipeline_statistics_query
GL_ARB_sparse_buffer
GL_ARB_transform_feedback_overflow_query
GL_KHR_blend_equation_advanced 
GL_KHR_blend_equation_advanced_coherent
GL_KHR_no_error
GL_ARB_ES3_2_compatibility
GL_ARB_fragment_shader_interlock
GL_ARB_gpu_shader_int64
GL_ARB_parallel_shader_compile
GL_ARB_post_depth_coverage
GL_ARB_sample_locations
GL_ARB_shader_atomic_counter_ops
GL_ARB_shader_ballot
GL_ARB_shader_clock
GL_ARB_shader_viewport_layer_array
GL_ARB_sparse_texture2
GL_ARB_sparse_texture_clamp
GL_ARB_texture_filter_minmax
GL_KHR_texture_compression_astc_sliced_3d
GL_ARB_gl_spirv
'''
class GLFunction(object):
    def __init__(self, ret_type, name):
        self.name = name
        self.ptr_type = 'PFN' + name.upper() + 'PROC'
        self.ret_type = ret_type
        self.providers = {}
        self.args = []


        self.wrapped_name = name
        self.public = 'GLPROXY_IMPORTEXPORT '

        # This is the string of C code for passing through the
        # arguments to the function.
        self.args_list = ''

        # This is the string of C code for declaring the arguments
        # list.
        self.args_decl = 'void'

        # This is the string name of the function that this is an
        # alias of, or self.name.  This initially comes from the
        # registry, and may get updated if it turns out our alias is
        # itself an alias (for example glFramebufferTextureEXT ->
        # glFramebufferTextureARB -> glFramebufferTexture)
        self.alias_name = name

        # After alias resolution, this is the function that this is an
        # alias of.
        self.alias_func = None

        # For the root of an alias tree, this lists the functions that
        # are marked as aliases of it, so that it can write a resolver
        # for all of them.
        self.alias_exts = []

    def add_arg(self, type, name):
        # Reword glDepthRange() arguments to avoid clashing with the
        # "near" and "far" keywords on win32.
        if name == "near":
            name = "hither"
        elif name == "far":
            name = "yon"

        # Mac screwed up GLhandleARB and made it a void * instead of
        # uint32_t, despite it being specced as only necessarily 32
        # bits wide, causing portability problems all over.  There are
        # prototype conflicts between things like
        # glAttachShader(GLuint program, GLuint shader) and
        # glAttachObjectARB(GLhandleARB container, GLhandleARB obj),
        # even though they are marked as aliases in the XML (and being
        # aliases in Mesa).
        #
        # We retain those aliases.  In the x86_64 ABI, the first 6
        # args are stored in 64-bit registers, so the calls end up
        # being the same despite the different types.  We just need to
        # add a cast to khronos_uintptr_t to shut up the compiler.
        if type == 'GLhandleARB':
            assert(len(self.args) < 6)
            arg_list_name = '(khronos_uintptr_t)' + name
        else:
            arg_list_name = name

        self.args.append((type, name))
        if self.args_decl == 'void':
            self.args_list = arg_list_name
            self.args_decl = type + ' ' + name
        else:
            self.args_list += ', ' + arg_list_name
            self.args_decl += ', ' + type + ' ' + name

    def add_provider(self, condition):
        self.providers[str(condition)] = GLProvider(condition, self.name)

    def add_alias(self, ext):
        assert self.alias_func is None

        self.alias_exts.append(ext)
        ext.alias_func = self

class Generator(object):
    def __init__(self, target):
        self.target = target
        self.enums = {}
        self.functions = {}
        self.sorted_function = None
        self.max_enum_name_len = 1
        self.copyright_comment = None
        self.typedefs = ''
        self.out_file = None

        # GL versions named in the registry, which we should generate
        # #defines for.
        self.supported_versions = set()

        # Extensions named in the registry, which we should generate
        # #defines for.
        self.supported_extensions = set()


    def all_text_until_element_name(self, element, element_name):
        text = ''

        if element.text is not None:
            text += element.text

        for child in element:
            if child.tag == element_name:
                break
            if child.text:
                text += child.text
            if child.tail:
                text += child.tail
        return text

    def out(self, text):
        self.out_file.write(text)

    def outln(self, text):
        self.out_file.write(text + '\n')

    def parse_typedefs(self, reg):
        for t in reg.findall('types/type'):
            if 'name' in t.attrib and t.attrib['name'] not in {'GLhandleARB'}:
                continue

            # The gles1/gles2-specific types are redundant
            # declarations, and the different types used for them (int
            # vs int32_t) caused problems on win32 builds.
            api = t.get('api')
            if api:
                continue

            if t.text is not None:
                self.typedefs += t.text

            for child in t:
                if child.tag == 'apientry':
                    self.typedefs += 'APIENTRY'
                if child.text:
                    self.typedefs += child.text
                if child.tail:
                    self.typedefs += child.tail
            self.typedefs += '\n'

    def parse_enums(self, reg):
        for enum in reg.findall('enums/enum'):
            name = enum.get('name')

            # wgl.xml's 0xwhatever definitions end up colliding with
            # wingdi.h's decimal definitions of these.
            if ('WGL_SWAP_OVERLAY' in name or
                'WGL_SWAP_UNDERLAY' in name or
                'WGL_SWAP_MAIN_PLANE' in name):
                continue

            self.max_enum_name_len = max(self.max_enum_name_len, len(name))
            self.enums[name] = enum.get('value')

    def get_function_return_type(self, proto):
        # Everything up to the start of the name element is the return type.
        return self.all_text_until_element_name(proto, 'name').strip()

    def parse_function_definitions(self, reg):
        for command in reg.findall('commands/command'):
            proto = command.find('proto')
            name = proto.find('name').text
            ret_type = self.get_function_return_type(proto)

            func = GLFunction(ret_type, name)

            for arg in command.findall('param'):
                func.add_arg(self.all_text_until_element_name(arg, 'name').strip(),
                             arg.find('name').text)

            alias = command.find('alias')
            if alias is not None:
                # Note that some alias references appear before the
                # target command is defined (glAttachObjectARB() ->
                # glAttachShader(), for example).
                func.alias_name = alias.get('name')

            self.functions[name] = func

    def drop_weird_glx_functions(self):
        # Drop a few ancient SGIX GLX extensions that use types not defined
        # anywhere in Xlib.  In glxext.h, they're protected by #ifdefs for the
        # headers that defined them.
        weird_functions = [name for name, func in self.functions.items()
                           if 'VLServer' in func.args_decl
                           or 'DMparams' in func.args_decl]

        for name in weird_functions:
            del self.functions[name]

    def resolve_aliases(self):
        for func in self.functions.values():
            # Find the root of the alias tree, and add ourselves to it.
            if func.alias_name != func.name:
                alias_func = func
                while alias_func.alias_name != alias_func.name:
                    alias_func = self.functions[alias_func.alias_name]
                func.alias_name = alias_func.name
                func.alias_func = alias_func
                alias_func.alias_exts.append(func)

    def prepare_provider_enum(self):
        self.provider_enum = {}

        # We assume that for any given provider, all functions using
        # it will have the same loader.  This lets us generate a
        # general C function for detecting conditions and calling the
        # dlsym/getprocaddress, and have our many resolver stubs just
        # call it with a table of values.
        for func in self.functions.values():
            for provider in func.providers.values():
                if provider.condition_name in self.provider_enum:
                    assert(self.provider_enum[provider.condition_name] == provider.condition)
                    continue

                self.provider_enum[provider.condition_name] = provider.condition;

    def sort_functions(self):
        self.sorted_functions = sorted(self.functions.values(), key=lambda func:func.name)

    def process_require_statements(self, feature, condition):
        for command in feature.findall('require/command'):
            name = command.get('name')

            # wgl.xml describes 6 functions in WGL 1.0 that are in
            # gdi32.dll instead of opengl32.dll, and we would need to
            # change up our symbol loading to support that.  Just
            # don't wrap those functions.
            if self.target == 'wgl' and 'wgl' not in name:
                # According to http://stackoverflow.com/questions/199016/wglcreatecontext-in-c-sharp-failing-but-not-in-managed-c
                print("Remove function: " + name)
                del self.functions[name]
                continue;

            func = self.functions[name]
            func.add_provider(condition)

    def parse_function_providers(self, reg):
        self.es_version_start = 10000
        for feature in reg.findall('feature'):
            api = feature.get('api') # string gl, gles1, gles2, glx
            m = re.match('([0-9])\.([0-9])', feature.get('number'))
            version_major = int(m.group(1))
            version_minor = int(m.group(2))
            version = version_major * 10 + version_minor

            self.supported_versions.add(feature.get('name'))
            condition = {}
            if api == 'gl':
                condition = {
                  'api':'gl',
                  'enum_name': 'OpenGL_Desktop_{0}_{1}'.format(version_major, version_minor),
                  'version': version
                }
            elif api == 'gles2':
                condition = {
                  'api':'gl',
                  'enum_name': 'OpenGL_ES_{0}_{1}'.format(version_major, version_minor),
                  'version': self.es_version_start + version
                }
            elif api == 'gles1':
                condition = {
                  'api':'gl',
                  'enum_name': 'OpenGL_ES_1_0',
                  'version': self.es_version_start + 10
                }
            elif api == 'glx':
                condition = {
                  'api':'glx',
                  'enum_name': 'GLX_{0}_{1}'.format(version_major, version_minor),
                  "direct": True,
                  'version': version
                }
            elif api == 'egl':
                condition = {
                  'api':'egl',
                  'enum_name': 'EGL_{0}_{1}'.format(version_major, version_minor),
                  'version': version
                }
                if version == 10:
                  condition['direct'] = True
            elif api == 'wgl':
                condition = {
                  'api':'wgl',
                  "direct": True,
                  'enum_name': 'WGL_{0}_{1}'.format(version_major, version_minor),
                  'version': version
                }
            else:
                print('unknown API: "{0}"'.format(api))
                continue

            self.process_require_statements(feature, condition)

        for extension_feature in reg.findall('extensions/extension'):
            extname = extension_feature.get('name')

            self.supported_extensions.add(extname)

            # 'supported' is a set of strings like gl, gles1, gles2,
            # or glx, which are separated by '|'
            apis = extension_feature.get('supported').split('|')
            if 'glx' in apis:
                self.process_require_statements(extension_feature, {
                  'api':'glx',
                  'extension': extname
                })
            if 'egl' in apis:
                self.process_require_statements(extension_feature, {
                  'api':'egl',
                  'extension': extname
                })
            if 'wgl' in apis:
                self.process_require_statements(extension_feature, {
                  'api':'wgl',
                  'extension': extname
                })
            if {'gl', 'gles1', 'gles2'}.intersection(apis):
                self.process_require_statements(extension_feature, {
                  'api':'gl',
                  'extension': extname
                })

    def fixup_bootstrap_function(self, name):
        # We handle glGetString(), glGetIntegerv(), and
        # glXGetProcAddressARB() specially, because we need to use
        # them in the process of deciding on loaders for resolving,
        # and the naive code generation would result in their
        # resolvers calling their own resolvers.
        if name not in self.functions:
            return

        func = self.functions[name]
        for key in func.providers:
            func.providers[key].condition['direct'] = True

    def parse(self, file):
        reg = ET.parse(file)
        if reg.find('comment') != None:
            self.copyright_comment = reg.find('comment').text
        else:
            self.copyright_comment = ''
        self.parse_typedefs(reg)
        self.parse_enums(reg)
        self.parse_function_definitions(reg)
        self.parse_function_providers(reg)

    def write_copyright_comment_body(self):
        for line in self.copyright_comment.splitlines():
            if '-----' in line:
                break
            self.outln(' * ' + line)

    def write_enums(self):
        for name in sorted(self.supported_versions):
            self.outln('#define {0} 1'.format(name))
        self.outln('')
        if self.target == 'gl':
            for x in other_extensions.splitlines():
                self.supported_extensions.add(x.strip())
        self.extension_providers = sorted(self.supported_extensions)

        for name in self.extension_providers:
            self.outln('#define {0} 1'.format(name))
        self.outln('')

        if self.target == 'gl':
            offset = 0
            self.outln('enum glproxy_gl_extension_enum {')
            for name in self.extension_providers:
                self.outln('  GLPROXY_{0} = {1},'.format(name, offset))
                offset = offset + 1
            self.outln('};')
            self.outln('')
            self.outln('#define GLPROXY_GL_EXTENSION_enum_max {0}'.format(offset))
            self.outln('')

        # We want to sort by enum number (which puts a bunch of things
        # in a logical order), then by name after that, so we do those
        # sorts in reverse.  This is still way uglier than doing some
        # sort based on what version/extensions things are introduced
        # in, but we haven't paid any attention to those attributes
        # for enums yet.
        sorted_by_name = sorted(self.enums.keys())
        sorted_by_number = sorted(sorted_by_name, key=lambda name: self.enums[name])
        for name in sorted_by_number:
            self.outln('#define ' + name.ljust(self.max_enum_name_len + 3) + self.enums[name] + '')

    def write_function_ptr_typedefs(self):
        for func in self.sorted_functions:
            providers = self.get_function_ptr_providers(func)
            if len(providers) > 0:
              self.outln('typedef {0} (GLAPIENTRY *{1})({2});'.format(func.ret_type,
                                                                    func.ptr_type,
                                                                    func.args_decl))

    def write_header_header(self, file):
        self.out_file = open(file, 'w')

        self.outln('/* GL dispatch header.')
        self.outln(' * This is code-generated from the GL API XML files from Khronos.')
        self.write_copyright_comment_body()
        self.outln(' */')
        self.outln('')

        self.outln('#pragma once')

        self.outln('#include <stddef.h>')
        self.outln('')

    def write_header(self, file):
        self.write_header_header(file)

        self.out(self.typedefs)
        self.outln('')
        self.write_enums()
        self.outln('')
        self.write_function_ptr_typedefs()

        for func in self.sorted_functions:
            providers = self.get_function_ptr_providers(func)
            if len(providers) > 0:
              self.outln('GLPROXY_IMPORTEXPORT {0} GLPROXY_CALLSPEC glproxy_{1}({2});'.format(func.ret_type,
                                                                                     func.name,
                                                                                     func.args_decl))
            self.outln('')

        for func in self.sorted_functions:
            self.outln('#define {0} glproxy_{0}'.format(func.name))

    def get_function_ptr_providers(self, func):
        providers = []
        # Make a local list of all the providers for this alias group
        alias_root = func;
        if func.alias_func:
            alias_root = func.alias_func
        for provider in alias_root.providers.values():
            providers.append(provider)
        for alias_func in alias_root.alias_exts:
            for provider in alias_func.providers.values():
                providers.append(provider)

        # Add some partial aliases of a few functions.  These are ones
        # that aren't quite aliases, because of some trivial behavior
        # difference (like whether to produce an error for a
        # non-Genned name), but where we'd like to fall back to the
        # similar function if the proper one isn't present.
        half_aliases = {
            'glBindVertexArray' : 'glBindVertexArrayAPPLE',
            'glBindVertexArrayAPPLE' : 'glBindVertexArray',
            'glBindFramebuffer' : 'glBindFramebufferEXT',
            'glBindFramebufferEXT' : 'glBindFramebuffer',
            'glBindRenderbuffer' : 'glBindRenderbufferEXT',
            'glBindRenderbufferEXT' : 'glBindRenderbuffer',
        }
        if func.name in half_aliases:
            alias_func = self.functions[half_aliases[func.name]]
            for provider in alias_func.providers.values():
                providers.append(provider)

        def provider_sort(provider):
            return (provider.name != func.name, provider.name, provider.sort_key)
        providers.sort(key=provider_sort);
        return providers

    def write_thunks(self, func, offset):
        # Writes out the function that's initially plugged into the
        # global function pointer, which resolves, updates the global
        # function pointer, and calls down to it.
        #
        # It also writes out the actual initialized global function
        # pointer.
        uppder_name = 'PFN{0}PROC'.format(func.wrapped_name.upper())
        if func.ret_type == 'void' or func.ret_type == 'VOID':
            self.outln('GEN_THUNK({0}, {1}, ({2}), ({3}), {4}, {5})'.format(self.target,
                                                              func.wrapped_name,
                                                              func.args_decl,
                                                              func.args_list,
                                                              offset,
                                                              uppder_name))
        else:
            self.outln('GEN_THUNK_RET({0}, {1}, {2}, ({3}), ({4}), {5}, {6})'.format(self.target, func.ret_type,
                                                                       func.wrapped_name,
                                                                       func.args_decl,
                                                                       func.args_list,
                                                                       offset,
                                                              uppder_name))

    def write_providers_version(self):
        providers = [self.provider_enum[k] for k in self.provider_enum.keys()]
        version_providers = [x for x in providers if 'version' in x]
        if (self.target == 'gl'):
          version_providers.append({
            "api": "gl",
            "enum_name": "OpenGL_Desktop_MIN",
            "version": 0
          })
          version_providers.append({
            "api": "gl",
            "enum_name": "OpenGL_Desktop_MAX",
            "version": self.es_version_start - 1
          })
          version_providers.append({
            "api": "gl",
            "enum_name": "OpenGL_ES_MIN",
            "version": self.es_version_start
          })
          version_providers.append({
            "api": "gl",
            "enum_name": "OpenGL_ES_MAX",
            "version": self.es_version_start + self.es_version_start
          })

        version_providers = sorted(version_providers, key=lambda x: x['version'])
        self.outln('enum {0}_provider_versions {{'.format(self.target))
        for version_provider in version_providers:
            enum_name = version_provider["enum_name"]
            version = version_provider['version']
            self.outln('    {0} = {1},'.format(enum_name, version))
        self.outln('} PACKED;')
        self.outln('')

    def write_providers_extension(self):
        self.extension_offset_map = {}
        self.outln('#define {0}_extensions_count {1}'.format(self.target, self.extension_count))
        self.outln('')
        self.outln('static const char {0}_extension_enum_strings[] ='.format(self.target))
        offset = 0
        for extension_provider in self.extension_providers:
            self.extension_offset_map[extension_provider] = offset
            self.outln('    "{0}\\0"'.format(extension_provider))
            offset = offset + 1
        self.outln(';')
        self.outln('static const khronos_uint16_t {0}_extension_offsets[] = {{'.format(self.target))
        offset = 0
        for extension_provider in self.extension_providers:
            self.outln('    {0},'.format(offset))
            offset += len(extension_provider) + 1
        self.outln('    {0}'.format(offset))
        self.outln('};')
        self.outln('')


    def write_entrypoint_strings(self):
        self.entrypoint_string_offset = {}

        self.outln('static const khronos_uint8_t {0}_entrypoint_strings[] = {{'.format(self.target))
        offset = 0
        for func in self.sorted_functions:
            if func.name not in self.entrypoint_string_offset:
                self.entrypoint_string_offset[func.name] = offset
                offset += len(func.name) + 1
                self.out('    ')
                for x in list(func.name):
                    self.out('{0}, '.format(ord(x)))
                self.outln('0, /*{0}*/'.format(func.name))
        self.outln('};')
        self.outln('')

    def write_inc_header(self, file, is_table = False):
        self.out_file = open(file, 'w')

        self.outln('/* GL dispatch code.')
        self.outln(' * This is code-generated from the GL API XML files from Khronos.')
        self.write_copyright_comment_body()
        self.outln(' */')
        if is_table:
            self.outln('#if PLATFORM_HAS_{0}'.format(self.target.upper()))
            self.outln('#include "glproxy/{0}.h"'.format(self.target))
        else:
            self.outln('#include "dispatch_common.h"')
            self.outln('#if PLATFORM_HAS_{0}'.format(self.target.upper()))
        self.outln('')

    def write_table_type_inc(self, file):
        self.write_inc_header(file, True)
        self.outln('struct {0}_dispatch_table {{'.format(self.target))
        for func in self.sorted_functions:
            providers = self.get_function_ptr_providers(func)
            if len(providers) > 0:
              self.outln('    {0} glproxy_{1};'.format(func.ptr_type, func.wrapped_name))
        self.outln('};')
        self.outln('')

        self.extension_count = len(self.extension_providers)
        extension_bitmap_count = ((self.extension_count - 1) >> 5) + 1

        self.outln('#define {0}_EXTENSIONS_BITMAP_COUNT {1}'.format(self.target.upper(), extension_bitmap_count))
        self.outln('')
        self.write_providers_version()
        self.outln('')
        self.outln('#endif /* PLATFORM_HAS_{0} */'.format(self.target.upper()))

    def write_thunks_inc(self, file):
        self.write_inc_header(file)

        self.write_providers_extension()
        self.write_entrypoint_strings()
        self.outln('static const struct dispatch_resolve_info {0}_resolve_info_table[] = {{'.format(self.target))
        function_number = 0
        self.has_dispatch_direct = 0
        self.has_dispatch_version = 0
        self.function_offsets = {}
        for func in self.sorted_functions:
            providers = self.get_function_ptr_providers(func)
            for provider in providers:
                condition = provider.condition
                name = provider.name
                name_offset = self.entrypoint_string_offset[name]
                identity = function_number % 256
                self.out('    {')
                if ('direct' in condition):
                    self.out('DISPATCH_RESOLVE_DIRECT, {0}, {1}, {2}'.format(identity, condition['enum_name'], name_offset))
                    self.has_dispatch_direct = 1
                elif ('version' in condition):
                    self.out('DISPATCH_RESOLVE_VERSION, {0}, {1}, {2}'.format(identity, condition['enum_name'], name_offset))
                    self.has_dispatch_version = 1
                elif ('extension' in condition):
                    extension_offset = self.extension_offset_map[condition['extension']]
                    self.out('DISPATCH_RESOLVE_EXTENSION, {0}, {1} /* {2} */, {3}'.format(identity, extension_offset, condition['extension'], name_offset))
                else:
                    raise Exception("not valid")
                self.outln('}}, /* {0} */'.format(provider.name))
            if len(providers) > 0:
                self.function_offsets[func.name] = function_number
                function_number = function_number + 1
        identity = function_number % 256
        self.outln('    {{DISPATCH_RESOLVE_TERMINATOR, {0}, 0, 0}}'.format(identity))
        self.outln('};')
        self.outln('')
        self.outln('static khronos_uint16_t {0}_resolve_offsets[{1}] = {{0}};'.format(self.target, function_number));
        self.outln('static khronos_uint32_t {0}_method_name_offsets[{1}] = {{0}};'.format(self.target, function_number));
        self.outln('')
        self.dispatch_generated_inc_list = [
            'resolve',
            'glproxy_resolve_init',
            'glproxy_resolve_direct',
            'glproxy_resolve_version',
            'glproxy_resolve_extension',
            'dispatch_table',
            'metadata',
            'glproxy_resolve_local',
            'glproxy_dispatch_metadata_init',
            'extension_offsets',
            'extensions_count',
            'extension_enum_strings',
            'entrypoint_strings',
            'resolve_info_table',
            'resolve_offsets',
            'method_name_offsets',
        ]
        self.outln('#define HAS_DISPATCH_RESOLVE_DIRECT {0}'.format(self.has_dispatch_direct));
        self.outln('#define HAS_DISPATCH_RESOLVE_VERSION {0}'.format(self.has_dispatch_version));
        for suffix in self.dispatch_generated_inc_list:
            self.outln('#define current_{1} {0}_{1}'.format(self.target, suffix))
        self.outln('#include "dispatch_generated.inc"')
        for suffix in self.dispatch_generated_inc_list:
            self.outln('#undef current_{0}'.format(suffix))
        self.outln('#undef HAS_DISPATCH_RESOLVE_DIRECT');
        self.outln('#undef HAS_DISPATCH_RESOLVE_VERSION');

        self.outln('')

        for func in self.sorted_functions:
            if not func.name in self.function_offsets:
                print('Can not resolve `{0}`'.format(func.name))
            else:
                self.write_thunks(func, self.function_offsets[func.name])
        self.outln('')


        self.outln('#endif /* PLATFORM_HAS_{0} */'.format(self.target.upper()))

argparser = argparse.ArgumentParser(description='Generate GL dispatch wrappers.')
argparser.add_argument('files', metavar='file.xml', nargs='+', help='GL API XML files to be parsed')
argparser.add_argument('--dir', metavar='dir', required=True, help='Destination directory')
args = argparser.parse_args()

srcdir = args.dir + '/src/'
incdir = args.dir + '/include/glproxy/'

for file in args.files:
    name = os.path.basename(file).split('.xml')[0]
    generator = Generator(name)
    generator.parse(file)

    generator.drop_weird_glx_functions()

    # This is an ANSI vs Unicode function, handled specially by
    # include/glproxy/wgl.h
    if 'wglUseFontBitmaps' in generator.functions:
        del generator.functions['wglUseFontBitmaps']

    generator.sort_functions()
    generator.resolve_aliases()
    generator.fixup_bootstrap_function('glGetString')
    generator.fixup_bootstrap_function('glGetIntegerv')

    # While this is technically exposed as a GLX extension, it's
    # required to be present as a public symbol by the Linux OpenGL
    # ABI.
    generator.fixup_bootstrap_function('glXGetProcAddress')

    generator.prepare_provider_enum()

    generator.write_header(incdir + name + '_generated.h')
    generator.write_table_type_inc(srcdir + name + '_generated_dispatch_table_type.inc')
    generator.write_thunks_inc(srcdir + name + '_generated_dispatch_thunks.inc')

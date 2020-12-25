#include <array>
#include <vector>

#include <emscripten.h>
#include <emscripten/bind.h>

#include <h264_stream.h>

#include "reader.h"
#include "types.h"
#include "value-array.h"

EMSCRIPTEN_BINDINGS(H264Bitstream) {

  emscripten::class_<Reader>("Reader")
    .constructor<>()
    .function("readNaked", &Reader::readNaked)
    .function("readPPS", &Reader::readPPS)
    .function("readSPS", &Reader::readSPS)
    .function("readSEI", &Reader::readSEI)
    .function("readSliceHeader", &Reader::readSliceHeader)
    .function("readSPSSubset", &Reader::readSPSSubset)
    .function("readPrefixNAL", &Reader::readPrefixNAL)
    .function("readNALHeaderSVCEXT", &Reader::readNALHeaderSVCEXT)
  ;

  initValueArray<int, 2>("array_int_2");
  initValueArray<int, 6>("array_int_6");
  initValueArray<int, 8>("array_int_8");
  initValueArray<int, 12>("array_int_12");
  initValueArray<int, 64>("array_int_64");
  initValueArray<int, 96>("array_int_96");
  initValueArray<int, 128>("array_int_128");
  initValueArray<int, 256>("array_int_256");
  initValueArray<int, 384>("array_int_384");

  emscripten::register_vector<bind_sei_t>("vector_bind_sei");
  emscripten::register_vector<uint8_t>("vector_uint8");

  emscripten::value_object<pps_t>("pps_t")
    .field("pic_parameter_set_id", &pps_t::pic_parameter_set_id)
    .field("seq_parameter_set_id", &pps_t::seq_parameter_set_id)
    .field("entropy_coding_mode_flag", &pps_t::entropy_coding_mode_flag)
    .field("pic_order_present_flag", &pps_t::pic_order_present_flag)
    .field("num_slice_groups_minus1", &pps_t::num_slice_groups_minus1)
    .field("slice_group_map_type", &pps_t::slice_group_map_type)
    .field("run_length_minus1", &pps_t::run_length_minus1)
    .field("top_left", &pps_t::top_left)
    .field("bottom_right", &pps_t::bottom_right)
    .field(
      "slice_group_change_direction_flag",
      &pps_t::slice_group_change_direction_flag
    )
    .field(
      "slice_group_change_rate_minus1",
      &pps_t::slice_group_change_rate_minus1
    )
    .field("pic_size_in_map_units_minus1", &pps_t::pic_size_in_map_units_minus1)
    .field("slice_group_id", &pps_t::slice_group_id)
    .field("num_ref_idx_l0_active_minus1", &pps_t::num_ref_idx_l0_active_minus1)
    .field("num_ref_idx_l1_active_minus1", &pps_t::num_ref_idx_l1_active_minus1)
    .field("weighted_pred_flag", &pps_t::weighted_pred_flag)
    .field("weighted_bipred_idc", &pps_t::weighted_bipred_idc)
    .field("pic_init_qp_minus26", &pps_t::pic_init_qp_minus26)
    .field("pic_init_qs_minus26", &pps_t::pic_init_qs_minus26)
    .field("chroma_qp_index_offset", &pps_t::chroma_qp_index_offset)
    .field(
      "deblocking_filter_control_present_flag",
      &pps_t::deblocking_filter_control_present_flag
    )
    .field("constrained_intra_pred_flag", &pps_t::constrained_intra_pred_flag)
    .field(
      "redundant_pic_cnt_present_flag",
      &pps_t::redundant_pic_cnt_present_flag
    )
    .field("transform_8x8_mode_flag", &pps_t::transform_8x8_mode_flag)
    .field(
      "pic_scaling_matrix_present_flag",
      &pps_t::pic_scaling_matrix_present_flag
    )
    .field(
      "pic_scaling_list_present_flag",
      &pps_t::pic_scaling_list_present_flag
    )
    .field(
      "ScalingList4x4",
      &readArray2d<int, 6, 16, int[6][16], pps_t, &pps_t::ScalingList4x4>,
      &writeArray2d<int, 6, 16, pps_t>
    )
    .field(
      "UseDefaultScalingMatrix4x4Flag",
      &pps_t::UseDefaultScalingMatrix4x4Flag
    )
    .field(
      "ScalingList8x8",
      &readArray2d<int, 2, 64, int[2][64], pps_t, &pps_t::ScalingList8x8>,
      &writeArray2d<int, 2, 64, pps_t>
    )
    .field(
      "UseDefaultScalingMatrix8x8Flag",
      &pps_t::UseDefaultScalingMatrix8x8Flag
    )
    .field(
      "second_chroma_qp_index_offset",
      &pps_t::second_chroma_qp_index_offset
    )
  ;

  emscripten::value_object<sps_t>("sps_t")
    .field("profile_idc", &sps_t::profile_idc)
    .field("constraint_set0_flag", &sps_t::constraint_set0_flag)
    .field("constraint_set1_flag", &sps_t::constraint_set1_flag)
    .field("constraint_set2_flag", &sps_t::constraint_set2_flag)
    .field("constraint_set3_flag", &sps_t::constraint_set3_flag)
    .field("constraint_set4_flag", &sps_t::constraint_set4_flag)
    .field("constraint_set5_flag", &sps_t::constraint_set5_flag)
    .field("reserved_zero_2bits", &sps_t::reserved_zero_2bits)
    .field("level_idc", &sps_t::level_idc)
    .field("seq_parameter_set_id", &sps_t::seq_parameter_set_id)
    .field("chroma_format_idc", &sps_t::chroma_format_idc)
    .field("residual_colour_transform_flag", &sps_t::residual_colour_transform_flag)
    .field("bit_depth_luma_minus8", &sps_t::bit_depth_luma_minus8)
    .field("bit_depth_chroma_minus8", &sps_t::bit_depth_chroma_minus8)
    .field("qpprime_y_zero_transform_bypass_flag", &sps_t::qpprime_y_zero_transform_bypass_flag)
    .field("seq_scaling_matrix_present_flag", &sps_t::seq_scaling_matrix_present_flag)
    .field("seq_scaling_list_present_flag", &sps_t::seq_scaling_list_present_flag)
    .field(
      "ScalingList4x4",
      &readArray2d<int, 6, 16, int[6][16], sps_t, &sps_t::ScalingList4x4>,
      &writeArray2d<int, 6, 16, sps_t>
    )
    .field("UseDefaultScalingMatrix4x4Flag", &sps_t::UseDefaultScalingMatrix4x4Flag)
    .field(
      "ScalingList8x8",
      &readArray2d<int, 6, 64, int[6][64], sps_t, &sps_t::ScalingList8x8>,
      &writeArray2d<int, 6, 64, sps_t>
    )
    .field("UseDefaultScalingMatrix8x8Flag", &sps_t::UseDefaultScalingMatrix8x8Flag)
    .field("log2_max_frame_num_minus4", &sps_t::log2_max_frame_num_minus4)
    .field("pic_order_cnt_type", &sps_t::pic_order_cnt_type)
    .field("log2_max_pic_order_cnt_lsb_minus4", &sps_t::log2_max_pic_order_cnt_lsb_minus4)
    /*
    int delta_pic_order_always_zero_flag;
    int offset_for_non_ref_pic;
    int offset_for_top_to_bottom_field;
    int num_ref_frames_in_pic_order_cnt_cycle;
    int offset_for_ref_frame[256];
     */
    .field("num_ref_frames", &sps_t::num_ref_frames)
    .field("gaps_in_frame_num_value_allowed_flag", &sps_t::gaps_in_frame_num_value_allowed_flag)
    .field("pic_width_in_mbs_minus1", &sps_t::pic_width_in_mbs_minus1)
    .field("pic_height_in_map_units_minus1", &sps_t::pic_height_in_map_units_minus1)
    .field("frame_mbs_only_flag", &sps_t::frame_mbs_only_flag)
    .field("mb_adaptive_frame_field_flag", &sps_t::mb_adaptive_frame_field_flag)
    .field("direct_8x8_inference_flag", &sps_t::direct_8x8_inference_flag)
    .field("frame_cropping_flag", &sps_t::frame_cropping_flag)
    .field("frame_crop_left_offset", &sps_t::frame_crop_left_offset)
    .field("frame_crop_right_offset", &sps_t::frame_crop_right_offset)
    .field("frame_crop_top_offset", &sps_t::frame_crop_top_offset)
    .field("frame_crop_bottom_offset", &sps_t::frame_crop_bottom_offset)
    .field("vui_parameters_present_flag", &sps_t::vui_parameters_present_flag)
    .field("vui", &sps_t::vui)
    .field("hrd_nal", &sps_t::hrd_nal)
    .field("hrd_vcl", &sps_t::hrd_vcl)
  ;

  using sps_vui_t = decltype(sps_t::vui);

  emscripten::value_object<sps_vui_t>("sps_vui_t")
    .field("aspect_ratio_info_present_flag", &sps_vui_t::aspect_ratio_info_present_flag)
    .field("aspect_ratio_idc", &sps_vui_t::aspect_ratio_idc)
    .field("sar_width", &sps_vui_t::sar_width)
    .field("sar_height", &sps_vui_t::sar_height)
    .field("overscan_info_present_flag", &sps_vui_t::overscan_info_present_flag)
    .field("overscan_appropriate_flag", &sps_vui_t::overscan_appropriate_flag)
    .field("video_signal_type_present_flag", &sps_vui_t::video_signal_type_present_flag)
    .field("video_format", &sps_vui_t::video_format)
    .field("video_full_range_flag", &sps_vui_t::video_full_range_flag)
    .field("colour_description_present_flag", &sps_vui_t::colour_description_present_flag)
    .field("colour_primaries", &sps_vui_t::colour_primaries)
    .field("transfer_characteristics", &sps_vui_t::transfer_characteristics)
    .field("matrix_coefficients", &sps_vui_t::matrix_coefficients)
    .field("chroma_loc_info_present_flag", &sps_vui_t::chroma_loc_info_present_flag)
    .field("chroma_sample_loc_type_top_field", &sps_vui_t::chroma_sample_loc_type_top_field)
    .field("chroma_sample_loc_type_bottom_field", &sps_vui_t::chroma_sample_loc_type_bottom_field)
    .field("timing_info_present_flag", &sps_vui_t::timing_info_present_flag)
    .field("num_units_in_tick", &sps_vui_t::num_units_in_tick)
    .field("time_scale", &sps_vui_t::time_scale)
    .field("fixed_frame_rate_flag", &sps_vui_t::fixed_frame_rate_flag)
    .field("nal_hrd_parameters_present_flag", &sps_vui_t::nal_hrd_parameters_present_flag)
    .field("vcl_hrd_parameters_present_flag", &sps_vui_t::vcl_hrd_parameters_present_flag)
    .field("low_delay_hrd_flag", &sps_vui_t::low_delay_hrd_flag)
    .field("pic_struct_present_flag", &sps_vui_t::pic_struct_present_flag)
    .field("bitstream_restriction_flag", &sps_vui_t::bitstream_restriction_flag)
    .field("motion_vectors_over_pic_boundaries_flag", &sps_vui_t::motion_vectors_over_pic_boundaries_flag)
    .field("max_bytes_per_pic_denom", &sps_vui_t::max_bytes_per_pic_denom)
    .field("max_bits_per_mb_denom", &sps_vui_t::max_bits_per_mb_denom)
    .field("log2_max_mv_length_horizontal", &sps_vui_t::log2_max_mv_length_horizontal)
    .field("log2_max_mv_length_vertical", &sps_vui_t::log2_max_mv_length_vertical)
    .field("num_reorder_frames", &sps_vui_t::num_reorder_frames)
    .field("max_dec_frame_buffering", &sps_vui_t::max_dec_frame_buffering)
  ;

  emscripten::value_object<hrd_t>("hrd_t");

  emscripten::value_object<slice_header_t>("slice_header_t")
    .field("first_mb_in_slice", &slice_header_t::first_mb_in_slice)
    .field("slice_type", &slice_header_t::slice_type)
    .field("pic_parameter_set_id", &slice_header_t::pic_parameter_set_id)
    .field("colour_plane_id", &slice_header_t::colour_plane_id)
    .field("frame_num", &slice_header_t::frame_num)
    .field("field_pic_flag", &slice_header_t::field_pic_flag)
    .field("bottom_field_flag", &slice_header_t::bottom_field_flag)
    .field("idr_pic_id", &slice_header_t::idr_pic_id)
    .field("pic_order_cnt_lsb", &slice_header_t::pic_order_cnt_lsb)
    .field("delta_pic_order_cnt_bottom", &slice_header_t::delta_pic_order_cnt_bottom)
    .field("delta_pic_order_cnt", &slice_header_t::delta_pic_order_cnt)
    .field("redundant_pic_cnt", &slice_header_t::redundant_pic_cnt)
    .field("direct_spatial_mv_pred_flag", &slice_header_t::direct_spatial_mv_pred_flag)
    .field("num_ref_idx_active_override_flag", &slice_header_t::num_ref_idx_active_override_flag)
    .field("num_ref_idx_l0_active_minus1", &slice_header_t::num_ref_idx_l0_active_minus1)
    .field("num_ref_idx_l1_active_minus1", &slice_header_t::num_ref_idx_l1_active_minus1)
    .field("cabac_init_idc", &slice_header_t::cabac_init_idc)
    .field("slice_qp_delta", &slice_header_t::slice_qp_delta)
    .field("sp_for_switch_flag", &slice_header_t::sp_for_switch_flag)
    .field("slice_qs_delta", &slice_header_t::slice_qs_delta)
    .field("disable_deblocking_filter_idc", &slice_header_t::disable_deblocking_filter_idc)
    .field("slice_alpha_c0_offset_div2", &slice_header_t::slice_alpha_c0_offset_div2)
    .field("slice_beta_offset_div2", &slice_header_t::slice_beta_offset_div2)
    .field("slice_group_change_cycle", &slice_header_t::slice_group_change_cycle)
    .field("rplr", &slice_header_t::rplr)
    .field("drpm", &slice_header_t::drpm)
    .field("pwt", &slice_header_t::pwt)
  ;

  using rplr_t = decltype(slice_header_t::rplr);

  emscripten::value_object<rplr_t>("rplr_t")
    .field("ref_pic_list_reordering_flag_l0", &rplr_t::ref_pic_list_reordering_flag_l0)
    .field("reorder_l0", &rplr_t::reorder_l0)
    .field("ref_pic_list_reordering_flag_l1", &rplr_t::ref_pic_list_reordering_flag_l1)
    .field("reorder_l1", &rplr_t::reorder_l1)
  ;

  using rplr_reorder_l0_t = decltype(rplr_t::reorder_l0);

  emscripten::value_object<rplr_reorder_l0_t>("rplr_reorder_l0_t")
    .field("reordering_of_pic_nums_idc", &rplr_reorder_l0_t::reordering_of_pic_nums_idc)
    .field("abs_diff_pic_num_minus1", &rplr_reorder_l0_t::abs_diff_pic_num_minus1)
    .field("long_term_pic_num", &rplr_reorder_l0_t::long_term_pic_num)
  ;

  using rplr_reorder_l1_t = decltype(rplr_t::reorder_l1);

  emscripten::value_object<rplr_reorder_l1_t>("rplr_reorder_l1_t")
    .field("reordering_of_pic_nums_idc", &rplr_reorder_l1_t::reordering_of_pic_nums_idc)
    .field("abs_diff_pic_num_minus1", &rplr_reorder_l1_t::abs_diff_pic_num_minus1)
    .field("long_term_pic_num", &rplr_reorder_l1_t::long_term_pic_num)
  ;

  using drpm_t = decltype(slice_header_t::drpm);

  emscripten::value_object<drpm_t>("drpm_t")
    .field("no_output_of_prior_pics_flag", &drpm_t::no_output_of_prior_pics_flag)
    .field("long_term_reference_flag", &drpm_t::long_term_reference_flag)
    .field("adaptive_ref_pic_marking_mode_flag", &drpm_t::adaptive_ref_pic_marking_mode_flag)
    .field("memory_management_control_operation", &drpm_t::memory_management_control_operation)
    .field("difference_of_pic_nums_minus1", &drpm_t::difference_of_pic_nums_minus1)
    .field("long_term_pic_num", &drpm_t::long_term_pic_num)
    .field("long_term_frame_idx", &drpm_t::long_term_frame_idx)
    .field("max_long_term_frame_idx_plus1", &drpm_t::max_long_term_frame_idx_plus1)
  ;

  using pwt_t = decltype(slice_header_t::pwt);

  emscripten::value_object<pwt_t>("pwt_t")
    .field("luma_log2_weight_denom", &pwt_t::luma_log2_weight_denom)
    .field("chroma_log2_weight_denom", &pwt_t::chroma_log2_weight_denom)
    .field("luma_weight_l0_flag", &pwt_t::luma_weight_l0_flag)
    .field("luma_weight_l0", &pwt_t::luma_weight_l0)
    .field("luma_offset_l0", &pwt_t::luma_offset_l0)
    .field("chroma_weight_l0_flag", &pwt_t::chroma_weight_l0_flag)
    .field(
      "chroma_weight_l0",
      &readArray2d<int, 64, 2, int[64][2], pwt_t, &pwt_t::chroma_weight_l0>,
      &writeArray2d<int, 64, 2, pwt_t>
    )
    .field(
      "chroma_offset_l0",
      &readArray2d<int, 64, 2, int[64][2], pwt_t, &pwt_t::chroma_offset_l0>,
      &writeArray2d<int, 64, 2, pwt_t>
    )
    .field("luma_weight_l1_flag", &pwt_t::luma_weight_l1_flag)
    .field("luma_weight_l1", &pwt_t::luma_weight_l1)
    .field("luma_offset_l1", &pwt_t::luma_offset_l1)
    .field("chroma_weight_l1_flag", &pwt_t::chroma_weight_l1_flag)
    .field(
      "chroma_weight_l1",
      &readArray2d<int, 64, 2, int[64][2], pwt_t, &pwt_t::chroma_weight_l1>,
      &writeArray2d<int, 64, 2, pwt_t>
    )
    .field(
      "chroma_offset_l1",
      &readArray2d<int, 64, 2, int[64][2], pwt_t, &pwt_t::chroma_offset_l1>,
      &writeArray2d<int, 64, 2, pwt_t>
    )
  ;

  emscripten::value_object<bind_sei_t>("bind_sei_t")
    .field("payloadType", &bind_sei_t::payloadType)
    .field("payloadSize", &bind_sei_t::payloadSize)
    .field("data", &bind_sei_t::data)
  ;

  emscripten::value_object<bind_sps_subset_t>("bind_sps_subset_t")
    .field("additional_extension2_flag", &bind_sps_subset_t::additional_extension2_flag)
    .field("sps", &bind_sps_subset_t::sps)
    .field("sps_svc_ext", &bind_sps_subset_t::sps_svc_ext)
  ;

  emscripten::value_object<sps_svc_ext_t>("sps_svc_ext_t")
    .field("inter_layer_deblocking_filter_control_present_flag", &sps_svc_ext_t::inter_layer_deblocking_filter_control_present_flag)
    .field("extended_spatial_scalability_idc", &sps_svc_ext_t::extended_spatial_scalability_idc)
    .field("chroma_phase_x_plus1_flag", &sps_svc_ext_t::chroma_phase_x_plus1_flag)
    .field("chroma_phase_y_plus1", &sps_svc_ext_t::chroma_phase_y_plus1)
    .field("seq_ref_layer_chroma_phase_x_plus1_flag", &sps_svc_ext_t::seq_ref_layer_chroma_phase_x_plus1_flag)
    .field("seq_ref_layer_chroma_phase_y_plus1", &sps_svc_ext_t::seq_ref_layer_chroma_phase_y_plus1)
    .field("seq_scaled_ref_layer_left_offset", &sps_svc_ext_t::seq_scaled_ref_layer_left_offset)
    .field("seq_scaled_ref_layer_top_offset", &sps_svc_ext_t::seq_scaled_ref_layer_top_offset)
    .field("seq_scaled_ref_layer_right_offset", &sps_svc_ext_t::seq_scaled_ref_layer_right_offset)
    .field("seq_scaled_ref_layer_bottom_offset", &sps_svc_ext_t::seq_scaled_ref_layer_bottom_offset)
    .field("seq_tcoeff_level_prediction_flag", &sps_svc_ext_t::seq_tcoeff_level_prediction_flag)
    .field("adaptive_tcoeff_level_prediction_flag", &sps_svc_ext_t::adaptive_tcoeff_level_prediction_flag)
    .field("slice_header_restriction_flag", &sps_svc_ext_t::slice_header_restriction_flag)
    .field("svc_vui_parameters_present_flag", &sps_svc_ext_t::svc_vui_parameters_present_flag)
  ;

  emscripten::value_object<prefix_nal_svc_t>("prefix_nal_svc_t")
    .field("store_ref_base_pic_flag", &prefix_nal_svc_t::store_ref_base_pic_flag)
    .field("additional_prefix_nal_unit_extension_flag", &prefix_nal_svc_t::additional_prefix_nal_unit_extension_flag)
    .field("additional_prefix_nal_unit_extension_data_flag", &prefix_nal_svc_t::additional_prefix_nal_unit_extension_data_flag)
    .field("adaptive_ref_base_pic_marking_mode_flag", &prefix_nal_svc_t::adaptive_ref_base_pic_marking_mode_flag)
    .field("memory_management_base_control_operation", &prefix_nal_svc_t::memory_management_base_control_operation)
    .field("difference_of_base_pic_nums_minus1", &prefix_nal_svc_t::difference_of_base_pic_nums_minus1)
    .field("long_term_base_pic_num", &prefix_nal_svc_t::long_term_base_pic_num)
  ;

  emscripten::value_object<nal_svc_ext_t>("nal_svc_ext_t")
    .field("idr_flag", &nal_svc_ext_t::idr_flag)
    .field("priority_id", &nal_svc_ext_t::priority_id)
    .field("no_inter_layer_pred_flag", &nal_svc_ext_t::no_inter_layer_pred_flag)
    .field("dependency_id", &nal_svc_ext_t::dependency_id)
    .field("quality_id", &nal_svc_ext_t::quality_id)
    .field("temporal_id", &nal_svc_ext_t::temporal_id)
    .field("use_ref_base_pic_flag", &nal_svc_ext_t::use_ref_base_pic_flag)
    .field("discardable_flag", &nal_svc_ext_t::discardable_flag)
    .field("output_flag", &nal_svc_ext_t::output_flag)
    .field("reserved_three_2bits", &nal_svc_ext_t::reserved_three_2bits)
  ;
};

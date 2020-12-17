#include <array>
#include <vector>

#include <emscripten.h>
#include <emscripten/bind.h>

#include <h264_stream.h>

#include "reader.h"
#include "value-array.h"

EMSCRIPTEN_BINDINGS(H264Bitstream) {

  emscripten::class_<Reader>("Reader")
    .constructor<>()
    .function("readNaked", &Reader::readNaked)
    .function("readPPS", &Reader::readPPS)
    .function("readSPS", &Reader::readSPS)
  ;

  initValueArray<int, 2>("array_int_2");
  initValueArray<int, 6>("array_int_6");
  initValueArray<int, 8>("array_int_8");
  initValueArray<int, 96>("array_int_96");
  initValueArray<int, 128>("array_int_128");
  initValueArray<int, 256>("array_int_256");

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
    /*
    int seq_scaling_list_present_flag[12];
    int ScalingList4x4[6][16];
    int UseDefaultScalingMatrix4x4Flag[6];
    int ScalingList8x8[6][64];
    int UseDefaultScalingMatrix8x8Flag[6];
    */
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

  emscripten::value_object<sps_vui_t>("sps_t::vui")
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
};

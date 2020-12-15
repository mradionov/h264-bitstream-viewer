#include <emscripten.h>
#include <emscripten/bind.h>

#include "reader.h"
#include "payloads/payload-pps.h"

extern "C" {

EMSCRIPTEN_BINDINGS(H264Bitstream) {

  emscripten::class_<Reader>("Reader")
    .constructor<>()
    .function("readNaked", &Reader::readNaked)
    .function("readPPS", &Reader::readPPS)
    ;

  emscripten::register_vector<int>("vector<int>");

  emscripten::value_object<PayloadPPS>("PayloadPPS")
    .field("pic_parameter_set_id", &PayloadPPS::pic_parameter_set_id)
    .field("seq_parameter_set_id", &PayloadPPS::seq_parameter_set_id)
    .field("entropy_coding_mode_flag", &PayloadPPS::entropy_coding_mode_flag)
    .field("pic_order_present_flag", &PayloadPPS::pic_order_present_flag)
    .field("num_slice_groups_minus1", &PayloadPPS::num_slice_groups_minus1)
    .field("slice_group_map_type", &PayloadPPS::slice_group_map_type)
    .field("run_length_minus1", &PayloadPPS::run_length_minus1)
    .field("top_left", &PayloadPPS::top_left)
    .field("bottom_right", &PayloadPPS::bottom_right)
    .field("slice_group_change_direction_flag", &PayloadPPS::slice_group_change_direction_flag)
    .field("slice_group_change_rate_minus1", &PayloadPPS::slice_group_change_rate_minus1)
    .field("pic_size_in_map_units_minus1", &PayloadPPS::pic_size_in_map_units_minus1)
    .field("slice_group_id", &PayloadPPS::slice_group_id)
    .field("num_ref_idx_l0_active_minus1", &PayloadPPS::num_ref_idx_l0_active_minus1)
    .field("num_ref_idx_l1_active_minus1", &PayloadPPS::num_ref_idx_l1_active_minus1)
    .field("weighted_pred_flag", &PayloadPPS::weighted_pred_flag)
    .field("weighted_bipred_idc", &PayloadPPS::weighted_bipred_idc)
    .field("pic_init_qp_minus26", &PayloadPPS::pic_init_qp_minus26)
    .field("pic_init_qs_minus26", &PayloadPPS::pic_init_qs_minus26)
    .field("chroma_qp_index_offset", &PayloadPPS::chroma_qp_index_offset)
    .field("deblocking_filter_control_present_flag", &PayloadPPS::deblocking_filter_control_present_flag)
    .field("constrained_intra_pred_flag", &PayloadPPS::constrained_intra_pred_flag)
    .field("redundant_pic_cnt_present_flag", &PayloadPPS::redundant_pic_cnt_present_flag)
    .field("transform_8x8_mode_flag", &PayloadPPS::transform_8x8_mode_flag)
    .field("pic_scaling_matrix_present_flag", &PayloadPPS::pic_scaling_matrix_present_flag)
    .field("second_chroma_qp_index_offset", &PayloadPPS::second_chroma_qp_index_offset)
  ;

};

}

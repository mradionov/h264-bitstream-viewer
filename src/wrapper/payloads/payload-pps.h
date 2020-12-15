#ifndef PAYLOAD_PPS_H
#define PAYLOAD_PPS_H

#include <vector>

#include <h264_stream.h>

// Reference type: pps_t

struct PayloadPPS {
  int pic_parameter_set_id;
  int seq_parameter_set_id;
  int entropy_coding_mode_flag;
  int pic_order_present_flag;
  int num_slice_groups_minus1;
  int slice_group_map_type;
  std::vector<int> run_length_minus1;
  std::vector<int> top_left;
  std::vector<int> bottom_right;
  int slice_group_change_direction_flag;
  int slice_group_change_rate_minus1;
  int pic_size_in_map_units_minus1;
  std::vector<int> slice_group_id;
  int num_ref_idx_l0_active_minus1;
  int num_ref_idx_l1_active_minus1;
  int weighted_pred_flag;
  int weighted_bipred_idc;
  int pic_init_qp_minus26;
  int pic_init_qs_minus26;
  int chroma_qp_index_offset;
  int deblocking_filter_control_present_flag;
  int constrained_intra_pred_flag;
  int redundant_pic_cnt_present_flag;
  int transform_8x8_mode_flag;
  int pic_scaling_matrix_present_flag;
  // int pic_scaling_list_present_flag[8];
  // int ScalingList4x4[6][16];
  // int UseDefaultScalingMatrix4x4Flag[6];
  // int ScalingList8x8[2][64];
  // int UseDefaultScalingMatrix8x8Flag[2];
  int second_chroma_qp_index_offset;
};

#endif

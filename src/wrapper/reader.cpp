#include <iostream>
#include <sstream>

#include <h264_stream.h>

#include "h264naked-print.h"
#include "reader.h"
#include "payloads/payload-pps.h"

std::string Reader::readNaked(uintptr_t input, int size) {
  const int32_t* data = reinterpret_cast<int32_t*>(input);

  uint8_t* buf = new uint8_t[size];

  for (int i = 0; i < size; i += 1) {
    buf[i] = (uint8_t) (data[i] & 0xff);
  }

  h264_stream_t* h = h264_new();

  int ret = read_nal_unit(h, buf, size);

  std::stringstream ss;

  print_nal(ss, h, h->nal);

  h264_free(h);

  delete [] buf;

  return ss.str();
}

PayloadPPS Reader::readPPS(uintptr_t input, int size) {
  const int32_t* data = reinterpret_cast<int32_t*>(input);

  uint8_t* buf = new uint8_t[size];

  for (int i = 0; i < size; i += 1) {
    buf[i] = (uint8_t) (data[i] & 0xff);
  }

  h264_stream_t* h = h264_new();

  int ret = read_nal_unit(h, buf, size);

  PayloadPPS payload;

  pps_t* pps = h->pps;

  payload.pic_parameter_set_id = pps->pic_parameter_set_id;
  payload.seq_parameter_set_id = pps->seq_parameter_set_id;
  payload.entropy_coding_mode_flag = pps->entropy_coding_mode_flag;
  payload.pic_order_present_flag = pps->pic_order_present_flag;
  payload.num_slice_groups_minus1 = pps->num_slice_groups_minus1;
  payload.slice_group_map_type = pps->slice_group_map_type;
  payload.run_length_minus1.assign(*pps->run_length_minus1, 8);
  payload.top_left.assign(*pps->top_left, 8);
  payload.bottom_right.assign(*pps->bottom_right, 8);
  payload.slice_group_change_direction_flag = pps->slice_group_change_direction_flag;
  payload.slice_group_change_rate_minus1 = pps->slice_group_change_rate_minus1;
  payload.pic_size_in_map_units_minus1 = pps->pic_size_in_map_units_minus1;
  payload.slice_group_id.assign(*pps->slice_group_id, 8);
  payload.num_ref_idx_l0_active_minus1 = pps->num_ref_idx_l0_active_minus1;
  payload.num_ref_idx_l1_active_minus1 = pps->num_ref_idx_l1_active_minus1;
  payload.weighted_pred_flag = pps->weighted_pred_flag;
  payload.weighted_bipred_idc = pps->weighted_bipred_idc;
  payload.pic_init_qp_minus26 = pps->pic_init_qp_minus26;
  payload.pic_init_qs_minus26 = pps->pic_init_qs_minus26;
  payload.chroma_qp_index_offset = pps->chroma_qp_index_offset;
  payload.deblocking_filter_control_present_flag = pps->deblocking_filter_control_present_flag;
  payload.constrained_intra_pred_flag = pps->constrained_intra_pred_flag;
  payload.redundant_pic_cnt_present_flag = pps->redundant_pic_cnt_present_flag;
  payload.transform_8x8_mode_flag = pps->transform_8x8_mode_flag;
  payload.pic_scaling_matrix_present_flag = pps->pic_scaling_matrix_present_flag;
  payload.second_chroma_qp_index_offset = pps->second_chroma_qp_index_offset;

  h264_free(h);

  delete [] buf;

  return payload;
}

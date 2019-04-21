#include <iostream>
#include <sstream>

#include <emscripten.h>
#include <emscripten/bind.h>

#include <h264_stream.h>

// using namespace emscripten;
using namespace std;

extern "C" {

// The following functions:
// - print_sps
// - print_pps
// - print_slice_header
// - print_aud
// - print_seis
// - print_nal
// - print_bytes
//
// Were copied and modified from the file:
//
// https://github.com/shi-yan/H264Naked/blob/master/H264NALListModel.cpp
//
// which is a part of open-source project
//
// https://github.com/shi-yan/H264Naked
//
// licensed under MIT License
//
// https://github.com/shi-yan/H264Naked/blob/master/LICENSE
//
// Which is preserved right below:
//
// The MIT License (MIT)
//
// Copyright (c) 2015 Shi Yan
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

void print_bytes(stringstream &ts, uint8_t* buf, int len) {
  for (int i = 0; i < len; i++) {
    // ts << string("%1 ").arg(buf[i] , 0, 16, QLatin1Char('0'));
    ts << hex << buf[i] << " ";

    if ((i+1) % 16 == 0) {
      ts<< "\n";
    }
  }
  ts << "\n";
}

void print_sps(stringstream &ts, sps_t* sps)
{
    ts << "======= SPS =======\n";
    ts << " profile_idc :" << sps->profile_idc <<"\n";
    ts << " constraint_set0_flag :"<< sps->constraint_set0_flag <<"\n";
    ts << " constraint_set1_flag :" << sps->constraint_set1_flag <<"\n";
    ts << " constraint_set2_flag :" << sps->constraint_set2_flag <<"\n";
    ts << " constraint_set3_flag :" << sps->constraint_set3_flag <<"\n";
    ts << " constraint_set4_flag :" << sps->constraint_set4_flag <<"\n";
    ts << " constraint_set5_flag :" << sps->constraint_set5_flag <<"\n";
    ts << " reserved_zero_2bits :" << sps->reserved_zero_2bits <<"\n";
    ts << " level_idc :" << sps->level_idc <<"\n";
    ts << " seq_parameter_set_id :" << sps->seq_parameter_set_id <<"\n";
    ts << " chroma_format_idc :" << sps->chroma_format_idc <<"\n";
    ts << " residual_colour_transform_flag :" << sps->residual_colour_transform_flag <<"\n";
    ts << " bit_depth_luma_minus8 :" << sps->bit_depth_luma_minus8 <<"\n";
    ts << " bit_depth_chroma_minus8 :" << sps->bit_depth_chroma_minus8 <<"\n";
    ts << " qpprime_y_zero_transform_bypass_flag :" << sps->qpprime_y_zero_transform_bypass_flag <<"\n";
    ts << " seq_scaling_matrix_present_flag :" << sps->seq_scaling_matrix_present_flag <<"\n";
    //  int seq_scaling_list_present_flag[8];
    //  void* ScalingList4x4[6];
    //  int UseDefaultScalingMatrix4x4Flag[6];
    //  void* ScalingList8x8[2];
    //  int UseDefaultScalingMatrix8x8Flag[2];
    ts << " log2_max_frame_num_minus4 :" << sps->log2_max_frame_num_minus4 <<"\n";
    ts << " pic_order_cnt_type :" << sps->pic_order_cnt_type <<"\n";
      ts << "   log2_max_pic_order_cnt_lsb_minus4 :" << sps->log2_max_pic_order_cnt_lsb_minus4 <<"\n";
      ts << "   delta_pic_order_always_zero_flag :" << sps->delta_pic_order_always_zero_flag <<"\n";
      ts << "   offset_for_non_ref_pic :" << sps->offset_for_non_ref_pic <<"\n";
      ts << "   offset_for_top_to_bottom_field :" << sps->offset_for_top_to_bottom_field <<"\n";
      ts << "   num_ref_frames_in_pic_order_cnt_cycle :" << sps->num_ref_frames_in_pic_order_cnt_cycle <<"\n";
    //  int offset_for_ref_frame[256];
    ts << " num_ref_frames :" << sps->num_ref_frames <<"\n";
    ts << " gaps_in_frame_num_value_allowed_flag :" << sps->gaps_in_frame_num_value_allowed_flag <<"\n";
    ts << " pic_width_in_mbs_minus1 :" << sps->pic_width_in_mbs_minus1 <<"\n";
    ts << " pic_height_in_map_units_minus1 :" << sps->pic_height_in_map_units_minus1 <<"\n";
    ts << " frame_mbs_only_flag :" << sps->frame_mbs_only_flag <<"\n";
    ts << " mb_adaptive_frame_field_flag :" << sps->mb_adaptive_frame_field_flag <<"\n";
    ts << " direct_8x8_inference_flag :" << sps->direct_8x8_inference_flag <<"\n";
    ts << " frame_cropping_flag :" << sps->frame_cropping_flag <<"\n";
    ts << "   frame_crop_left_offset :" << sps->frame_crop_left_offset <<"\n";
    ts << "   frame_crop_right_offset :" << sps->frame_crop_right_offset <<"\n";
    ts << "   frame_crop_top_offset :" << sps->frame_crop_top_offset <<"\n";
    ts << "   frame_crop_bottom_offset :" << sps->frame_crop_bottom_offset <<"\n";
    ts << " vui_parameters_present_flag :" << sps->vui_parameters_present_flag <<"\n";

    ts << "=== VUI ===\n";
    ts << " aspect_ratio_info_present_flag :" << sps->vui.aspect_ratio_info_present_flag <<"\n";
    ts << "   aspect_ratio_idc :" << sps->vui.aspect_ratio_idc <<"\n";
    ts << "     sar_width :" << sps->vui.sar_width <<"\n";
    ts << "     sar_height :" << sps->vui.sar_height <<"\n";
    ts << " overscan_info_present_flag :" << sps->vui.overscan_info_present_flag <<"\n";
    ts << "   overscan_appropriate_flag :" << sps->vui.overscan_appropriate_flag <<"\n";
    ts << " video_signal_type_present_flag :" << sps->vui.video_signal_type_present_flag <<"\n";
    ts << "   video_format :" << sps->vui.video_format <<"\n";
    ts << "   video_full_range_flag :" << sps->vui.video_full_range_flag <<"\n";
    ts << "   colour_description_present_flag :" << sps->vui.colour_description_present_flag <<"\n";
    ts << "     colour_primaries :" << sps->vui.colour_primaries <<"\n";
    ts << "   transfer_characteristics :" << sps->vui.transfer_characteristics <<"\n";
    ts << "   matrix_coefficients :" << sps->vui.matrix_coefficients <<"\n";
    ts << " chroma_loc_info_present_flag :" << sps->vui.chroma_loc_info_present_flag <<"\n";
    ts << "   chroma_sample_loc_type_top_field :" << sps->vui.chroma_sample_loc_type_top_field <<"\n";
    ts << "   chroma_sample_loc_type_bottom_field :" << sps->vui.chroma_sample_loc_type_bottom_field <<"\n";
    ts << " timing_info_present_flag :" << sps->vui.timing_info_present_flag <<"\n";
    ts << "   num_units_in_tick :" << sps->vui.num_units_in_tick <<"\n";
    ts << "   time_scale :" << sps->vui.time_scale <<"\n";
    ts << "   fixed_frame_rate_flag :" << sps->vui.fixed_frame_rate_flag <<"\n";
    ts << " nal_hrd_parameters_present_flag :" << sps->vui.nal_hrd_parameters_present_flag <<"\n";
    ts << " vcl_hrd_parameters_present_flag :" << sps->vui.vcl_hrd_parameters_present_flag <<"\n";
    ts << "   low_delay_hrd_flag :" << sps->vui.low_delay_hrd_flag <<"\n";
    ts << " pic_struct_present_flag :" << sps->vui.pic_struct_present_flag <<"\n";
    ts << " bitstream_restriction_flag :" << sps->vui.bitstream_restriction_flag <<"\n";
    ts << "   motion_vectors_over_pic_boundaries_flag :" << sps->vui.motion_vectors_over_pic_boundaries_flag <<"\n";
    ts << "   max_bytes_per_pic_denom :" << sps->vui.max_bytes_per_pic_denom <<"\n";
    ts << "   max_bits_per_mb_denom :" << sps->vui.max_bits_per_mb_denom <<"\n";
    ts << "   log2_max_mv_length_horizontal :" << sps->vui.log2_max_mv_length_horizontal <<"\n";
    ts << "   log2_max_mv_length_vertical :" << sps->vui.log2_max_mv_length_vertical <<"\n";
    ts << "   num_reorder_frames :" << sps->vui.num_reorder_frames <<"\n";
    ts << "   max_dec_frame_buffering :" << sps->vui.max_dec_frame_buffering <<"\n";

    ts << "=== HRD ===\n";
    ts << " cpb_cnt_minus1 :" << sps->hrd_nal.cpb_cnt_minus1 <<"\n";
    ts << " bit_rate_scale :" << sps->hrd_nal.bit_rate_scale <<"\n";
    ts << " cpb_size_scale :" << sps->hrd_nal.cpb_size_scale <<"\n";
    int SchedSelIdx;
    for( SchedSelIdx = 0; SchedSelIdx <= sps->hrd_nal.cpb_cnt_minus1; SchedSelIdx++ )
    {
        ts << "   bit_rate_value_minus1[" << SchedSelIdx <<"] :"<< sps->hrd_nal.bit_rate_value_minus1[SchedSelIdx] <<"\n"; // up to cpb_cnt_minus1, which is <= 31
        ts << "   cpb_size_value_minus1[" << SchedSelIdx << "] :"<< sps->hrd_nal.cpb_size_value_minus1[SchedSelIdx] <<"\n";
        ts << "   cbr_flag[" << SchedSelIdx <<"] :" << sps->hrd_nal.cbr_flag[SchedSelIdx] <<"\n";
    }
    ts << " initial_cpb_removal_delay_length_minus1 :" << sps->hrd_nal.initial_cpb_removal_delay_length_minus1 <<"\n";
    ts << " cpb_removal_delay_length_minus1 :" << sps->hrd_nal.cpb_removal_delay_length_minus1 <<"\n";
    ts << " dpb_output_delay_length_minus1 :" << sps->hrd_nal.dpb_output_delay_length_minus1 <<"\n";
    ts << " time_offset_length :" << sps->hrd_nal.time_offset_length <<"\n";
}

void print_pps(stringstream &ts, pps_t* pps)
{
    ts << "======= PPS =======\n";
    ts << " pic_parameter_set_id :" << pps->pic_parameter_set_id <<"\n";
    ts << " seq_parameter_set_id :" << pps->seq_parameter_set_id <<"\n";
    ts << " entropy_coding_mode_flag :" << pps->entropy_coding_mode_flag <<"\n";
    ts << " pic_order_present_flag :" << pps->pic_order_present_flag <<"\n";
    ts << " num_slice_groups_minus1 :" << pps->num_slice_groups_minus1 <<"\n";
    ts << " slice_group_map_type :" << pps->slice_group_map_type <<"\n";
    //  int run_length_minus1[8]; // up to num_slice_groups_minus1, which is <= 7 in Baseline and Extended, 0 otheriwse
    //  int top_left[8];
    //  int bottom_right[8];
    //  int slice_group_change_direction_flag;
    //  int slice_group_change_rate_minus1;
    //  int pic_size_in_map_units_minus1;
    //  int slice_group_id[256]; // FIXME what size?
    ts << " num_ref_idx_l0_active_minus1 :" << pps->num_ref_idx_l0_active_minus1 <<"\n";
    ts << " num_ref_idx_l1_active_minus1 :" << pps->num_ref_idx_l1_active_minus1 <<"\n";
    ts << " weighted_pred_flag :" << pps->weighted_pred_flag <<"\n";
    ts << " weighted_bipred_idc :" << pps->weighted_bipred_idc <<"\n";
    ts << " pic_init_qp_minus26 :" << pps->pic_init_qp_minus26 <<"\n";
    ts << " pic_init_qs_minus26 :" << pps->pic_init_qs_minus26 <<"\n";
    ts << " chroma_qp_index_offset :" << pps->chroma_qp_index_offset <<"\n";
    ts << " deblocking_filter_control_present_flag :" << pps->deblocking_filter_control_present_flag <<"\n";
    ts << " constrained_intra_pred_flag :" << pps->constrained_intra_pred_flag <<"\n";
    ts << " redundant_pic_cnt_present_flag :" << pps->redundant_pic_cnt_present_flag <<"\n";
    ts << " transform_8x8_mode_flag :" << pps->transform_8x8_mode_flag <<"\n";
    ts << " pic_scaling_matrix_present_flag :" << pps->pic_scaling_matrix_present_flag <<"\n";
    //  int pic_scaling_list_present_flag[8];
    //  void* ScalingList4x4[6];
    //  int UseDefaultScalingMatrix4x4Flag[6];
    //  void* ScalingList8x8[2];
    //  int UseDefaultScalingMatrix8x8Flag[2];
    ts << " second_chroma_qp_index_offset :" << pps->second_chroma_qp_index_offset <<"\n";
}

void print_slice_header(stringstream &ts, slice_header_t* sh)
{
    ts << "======= Slice Header =======\n";
    ts << " first_mb_in_slice :" << sh->first_mb_in_slice <<"\n";
    const char* slice_type_name;
    switch(sh->slice_type)
    {
    case SH_SLICE_TYPE_P :       slice_type_name = "P slice"; break;
    case SH_SLICE_TYPE_B :       slice_type_name = "B slice"; break;
    case SH_SLICE_TYPE_I :       slice_type_name = "I slice"; break;
    case SH_SLICE_TYPE_SP :      slice_type_name = "SP slice"; break;
    case SH_SLICE_TYPE_SI :      slice_type_name = "SI slice"; break;
    case SH_SLICE_TYPE_P_ONLY :  slice_type_name = "P slice only"; break;
    case SH_SLICE_TYPE_B_ONLY :  slice_type_name = "B slice only"; break;
    case SH_SLICE_TYPE_I_ONLY :  slice_type_name = "I slice only"; break;
    case SH_SLICE_TYPE_SP_ONLY : slice_type_name = "SP slice only"; break;
    case SH_SLICE_TYPE_SI_ONLY : slice_type_name = "SI slice only"; break;
    default :                    slice_type_name = "Unknown"; break;
    }
    ts << " slice_type :" << sh->slice_type << " " << slice_type_name << "\n";

    ts << " pic_parameter_set_id :" << sh->pic_parameter_set_id <<"\n";
    ts <<" frame_num :" << sh->frame_num << "\n";
    ts << " field_pic_flag :" << sh->field_pic_flag <<"\n";
    ts << " bottom_field_flag :" << sh->bottom_field_flag <<"\n";
    ts << " idr_pic_id :" << sh->idr_pic_id <<"\n";
    ts << " pic_order_cnt_lsb :" << sh->pic_order_cnt_lsb <<"\n";
    ts << " delta_pic_order_cnt_bottom :" << sh->delta_pic_order_cnt_bottom <<"\n";
    // int delta_pic_order_cnt[ 2 ];
    ts << " redundant_pic_cnt :" << sh->redundant_pic_cnt <<"\n";
    ts << " direct_spatial_mv_pred_flag :" << sh->direct_spatial_mv_pred_flag <<"\n";
    ts << " num_ref_idx_active_override_flag :" << sh->num_ref_idx_active_override_flag <<"\n";
    ts << " num_ref_idx_l0_active_minus1 :" << sh->num_ref_idx_l0_active_minus1 <<"\n";
    ts << " num_ref_idx_l1_active_minus1 :" << sh->num_ref_idx_l1_active_minus1 <<"\n";
    ts << " cabac_init_idc :" << sh->cabac_init_idc <<"\n";
    ts << " slice_qp_delta :" << sh->slice_qp_delta <<"\n";
    ts << " sp_for_switch_flag :" << sh->sp_for_switch_flag <<"\n";
    ts << " slice_qs_delta :" << sh->slice_qs_delta <<"\n";
    ts << " disable_deblocking_filter_idc :" << sh->disable_deblocking_filter_idc <<"\n";
    ts << " slice_alpha_c0_offset_div2 :" << sh->slice_alpha_c0_offset_div2 <<"\n";
    ts << " slice_beta_offset_div2 :" << sh->slice_beta_offset_div2 <<"\n";
    ts << " slice_group_change_cycle :" << sh->slice_group_change_cycle <<"\n";

    ts << "=== Prediction Weight Table ===\n";
    ts << " luma_log2_weight_denom :" << sh->pwt.luma_log2_weight_denom <<"\n";
    ts << " chroma_log2_weight_denom :"<< sh->pwt.chroma_log2_weight_denom <<"\n";
    ts << " luma_weight_l0_flag :"<< sh->pwt.luma_weight_l0_flag <<"\n";
    // int luma_weight_l0[64];
    // int luma_offset_l0[64];
    ts << " chroma_weight_l0_flag :"<< sh->pwt.chroma_weight_l0_flag <<"\n";
    // int chroma_weight_l0[64][2];
    // int chroma_offset_l0[64][2];
    ts << " luma_weight_l1_flag :"<< sh->pwt.luma_weight_l1_flag <<"\n";
    // int luma_weight_l1[64];
    // int luma_offset_l1[64];
    ts << " chroma_weight_l1_flag :"<< sh->pwt.chroma_weight_l1_flag <<"\n";
    // int chroma_weight_l1[64][2];
    // int chroma_offset_l1[64][2];

    ts << "=== Ref Pic List Reordering ===\n";
    ts << " ref_pic_list_reordering_flag_l0 :" << sh->rplr.ref_pic_list_reordering_flag_l0 <<"\n";
    ts << " ref_pic_list_reordering_flag_l1 :" << sh->rplr.ref_pic_list_reordering_flag_l1 <<"\n";
        // int reordering_of_pic_nums_idc;
        // int abs_diff_pic_num_minus1;
        // int long_term_pic_num;

    ts << "=== Decoded Ref Pic Marking ===\n";
    ts << " no_output_of_prior_pics_flag :" << sh->drpm.no_output_of_prior_pics_flag <<"\n";
    ts << " long_term_reference_flag :" << sh->drpm.long_term_reference_flag <<"\n";
    ts << " adaptive_ref_pic_marking_mode_flag :" << sh->drpm.adaptive_ref_pic_marking_mode_flag <<"\n";
        // int memory_management_control_operation;
        // int difference_of_pic_nums_minus1;
        // int long_term_pic_num;
        // int long_term_frame_idx;
        // int max_long_term_frame_idx_plus1;

}

void print_aud(stringstream &ts, aud_t* aud)
{
    ts << "======= Access Unit Delimiter =======\n";
    const char* primary_pic_type_name;
    switch (aud->primary_pic_type)
    {
    case AUD_PRIMARY_PIC_TYPE_I :       primary_pic_type_name = "I"; break;
    case AUD_PRIMARY_PIC_TYPE_IP :      primary_pic_type_name = "I, P"; break;
    case AUD_PRIMARY_PIC_TYPE_IPB :     primary_pic_type_name = "I, P, B"; break;
    case AUD_PRIMARY_PIC_TYPE_SI :      primary_pic_type_name = "SI"; break;
    case AUD_PRIMARY_PIC_TYPE_SISP :    primary_pic_type_name = "SI, SP"; break;
    case AUD_PRIMARY_PIC_TYPE_ISI :     primary_pic_type_name = "I, SI"; break;
    case AUD_PRIMARY_PIC_TYPE_ISIPSP :  primary_pic_type_name = "I, SI, P, SP"; break;
    case AUD_PRIMARY_PIC_TYPE_ISIPSPB : primary_pic_type_name = "I, SI, P, SP, B"; break;
    default : primary_pic_type_name = "Unknown"; break;
    }
    ts << " primary_pic_type :" << aud->primary_pic_type << primary_pic_type_name <<"\n";
}

void print_seis(stringstream &ts, h264_stream_t* h) {
  sei_t** seis = h->seis;
  int num_seis = h->num_seis;

  cout << "num_seis = " << num_seis << endl;

  ts << "======= SEI =======\n";
  const char* sei_type_name;
  int i;
  for (i = 0; i < num_seis; i++) {
    sei_t* s = seis[i];
    switch(s->payloadType) {
      case SEI_TYPE_BUFFERING_PERIOD :          sei_type_name = "Buffering period"; break;
      case SEI_TYPE_PIC_TIMING :                sei_type_name = "Pic timing"; break;
      case SEI_TYPE_PAN_SCAN_RECT :             sei_type_name = "Pan scan rect"; break;
      case SEI_TYPE_FILLER_PAYLOAD :            sei_type_name = "Filler payload"; break;
      case SEI_TYPE_USER_DATA_REGISTERED_ITU_T_T35 : sei_type_name = "User data registered ITU-T T35"; break;
      case SEI_TYPE_USER_DATA_UNREGISTERED :    sei_type_name = "User data unregistered"; break;
      case SEI_TYPE_RECOVERY_POINT :            sei_type_name = "Recovery point"; break;
      case SEI_TYPE_DEC_REF_PIC_MARKING_REPETITION : sei_type_name = "Dec ref pic marking repetition"; break;
      case SEI_TYPE_SPARE_PIC :                 sei_type_name = "Spare pic"; break;
      case SEI_TYPE_SCENE_INFO :                sei_type_name = "Scene info"; break;
      case SEI_TYPE_SUB_SEQ_INFO :              sei_type_name = "Sub seq info"; break;
      case SEI_TYPE_SUB_SEQ_LAYER_CHARACTERISTICS : sei_type_name = "Sub seq layer characteristics"; break;
      case SEI_TYPE_SUB_SEQ_CHARACTERISTICS :   sei_type_name = "Sub seq characteristics"; break;
      case SEI_TYPE_FULL_FRAME_FREEZE :         sei_type_name = "Full frame freeze"; break;
      case SEI_TYPE_FULL_FRAME_FREEZE_RELEASE : sei_type_name = "Full frame freeze release"; break;
      case SEI_TYPE_FULL_FRAME_SNAPSHOT :       sei_type_name = "Full frame snapshot"; break;
      case SEI_TYPE_PROGRESSIVE_REFINEMENT_SEGMENT_START : sei_type_name = "Progressive refinement segment start"; break;
      case SEI_TYPE_PROGRESSIVE_REFINEMENT_SEGMENT_END : sei_type_name = "Progressive refinement segment end"; break;
      case SEI_TYPE_MOTION_CONSTRAINED_SLICE_GROUP_SET : sei_type_name = "Motion constrained slice group set"; break;
      case SEI_TYPE_FILM_GRAIN_CHARACTERISTICS : sei_type_name = "Film grain characteristics"; break;
      case SEI_TYPE_DEBLOCKING_FILTER_DISPLAY_PREFERENCE : sei_type_name = "Deblocking filter display preference"; break;
      case SEI_TYPE_STEREO_VIDEO_INFO :         sei_type_name = "Stereo video info"; break;
      default: sei_type_name = "Unknown"; break;
    }
    ts << "=== " << sei_type_name<<"===\n";
    ts << " payloadType :" << s->payloadType <<"\n";
    ts << " payloadSize :" << s->payloadSize <<"\n";

    ts << " payload : \n";
    print_bytes(ts, s->data, s->payloadSize);
  }
}

void print_nal(stringstream &ts, h264_stream_t* h, nal_t* nal)
{
    ts << "==================== NAL ====================\n";
    ts << " forbidden_zero_bit :" << nal->forbidden_zero_bit << "\n";
    ts << " nal_ref_idc :" << nal->nal_ref_idc << "\n";
    // TODO make into subroutine
    const char* nal_unit_type_name;
    switch (nal->nal_unit_type)
    {
    case  NAL_UNIT_TYPE_UNSPECIFIED :                   nal_unit_type_name = "Unspecified"; break;
    case  NAL_UNIT_TYPE_CODED_SLICE_NON_IDR :           nal_unit_type_name = "Coded slice of a non-IDR picture"; break;
    case  NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_A :  nal_unit_type_name = "Coded slice data partition A"; break;
    case  NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_B :  nal_unit_type_name = "Coded slice data partition B"; break;
    case  NAL_UNIT_TYPE_CODED_SLICE_DATA_PARTITION_C :  nal_unit_type_name = "Coded slice data partition C"; break;
    case  NAL_UNIT_TYPE_CODED_SLICE_IDR :               nal_unit_type_name = "Coded slice of an IDR picture"; break;
    case  NAL_UNIT_TYPE_SEI :                           nal_unit_type_name = "Supplemental enhancement information (SEI)"; break;
    case  NAL_UNIT_TYPE_SPS :                           nal_unit_type_name = "Sequence parameter set"; break;
    case  NAL_UNIT_TYPE_PPS :                           nal_unit_type_name = "Picture parameter set"; break;
    case  NAL_UNIT_TYPE_AUD :                           nal_unit_type_name = "Access unit delimiter"; break;
    case  NAL_UNIT_TYPE_END_OF_SEQUENCE :               nal_unit_type_name = "End of sequence"; break;
    case  NAL_UNIT_TYPE_END_OF_STREAM :                 nal_unit_type_name = "End of stream"; break;
    case  NAL_UNIT_TYPE_FILLER :                        nal_unit_type_name = "Filler data"; break;
    case  NAL_UNIT_TYPE_SPS_EXT :                       nal_unit_type_name = "Sequence parameter set extension"; break;
        // 14..18    // Reserved
    case  NAL_UNIT_TYPE_CODED_SLICE_AUX :               nal_unit_type_name = "Coded slice of an auxiliary coded picture without partitioning"; break;
        // 20..23    // Reserved
        // 24..31    // Unspecified
    default :                                           nal_unit_type_name = "Unknown"; break;
    }
    ts << " nal_unit_type : " << nal->nal_unit_type << " " << nal_unit_type_name <<"\n";

    if( nal->nal_unit_type == NAL_UNIT_TYPE_CODED_SLICE_NON_IDR) { print_slice_header(ts, h->sh); }
    else if( nal->nal_unit_type == NAL_UNIT_TYPE_CODED_SLICE_IDR) { print_slice_header(ts, h->sh); }
    else if( nal->nal_unit_type == NAL_UNIT_TYPE_SPS) { print_sps(ts, h->sps); }
    else if( nal->nal_unit_type == NAL_UNIT_TYPE_PPS) { print_pps(ts, h->pps); }
    else if( nal->nal_unit_type == NAL_UNIT_TYPE_AUD) { print_aud(ts, h->aud); }
    else if( nal->nal_unit_type == NAL_UNIT_TYPE_SEI) { print_seis(ts, h ); }
}

struct Reader {
  Reader() {}

  string read(uintptr_t input, int size) {
    const int32_t* data = reinterpret_cast<int32_t*>(input);

    uint8_t* buf = new uint8_t[size];

    for (int i = 0; i < size; i += 1) {
      buf[i] = (uint8_t) (data[i] & 0xff);
    }

    h264_stream_t* h = h264_new();

    int ret = read_nal_unit(h, buf, size);

    // cout << "ret = " << ret << endl;

    stringstream ss;

    print_nal(ss, h, h->nal);

    // cout << ss.str() << endl;

    h264_free(h);

    delete [] buf;

    return ss.str();
  }
};


EMSCRIPTEN_BINDINGS(H264Bitstream) {

  emscripten::class_<Reader>("Reader")
    .constructor<>()
    .function("read", &Reader::read)
    ;

}

}

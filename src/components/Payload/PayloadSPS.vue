<template>
  <div>
    <Table>
      <HeaderRow>
        <HeaderCell>SPS</HeaderCell>
      </HeaderRow>
      <Row>
        <Cell>profile_idc</Cell>
        <Cell>{{ sps.profile_idc }}</Cell>
      </Row>
      <Row>
        <Cell>constraint_set0_flag</Cell>
        <Cell>{{ sps.constraint_set0_flag }}</Cell>
      </Row>
      <Row>
        <Cell>constraint_set1_flag</Cell>
        <Cell>{{ sps.constraint_set1_flag }}</Cell>
      </Row>
      <Row>
        <Cell>constraint_set2_flag</Cell>
        <Cell>{{ sps.constraint_set2_flag }}</Cell>
      </Row>
      <Row>
        <Cell>constraint_set3_flag</Cell>
        <Cell>{{ sps.constraint_set3_flag }}</Cell>
      </Row>
      <Row>
        <Cell>constraint_set4_flag</Cell>
        <Cell>{{ sps.constraint_set4_flag }}</Cell>
      </Row>
      <Row>
        <Cell>constraint_set5_flag</Cell>
        <Cell>{{ sps.constraint_set5_flag }}</Cell>
      </Row>
      <Row>
        <Cell>reserved_zero_2bits</Cell>
        <Cell>{{ sps.reserved_zero_2bits }}</Cell>
      </Row>
      <Row>
        <Cell>level_idc</Cell>
        <Cell>{{ sps.level_idc }}</Cell>
      </Row>
      <Row>
        <Cell>seq_parameter_set_id</Cell>
        <Cell>{{ sps.seq_parameter_set_id }}</Cell>
      </Row>
      <template v-if="isRequiredProfile">
        <Row>
          <Cell>chroma_format_idc</Cell>
          <Cell>{{ sps.chroma_format_idc }}</Cell>
        </Row>
        <Row v-if="sps.chroma_format_idc === 3">
          <Cell>residual_colour_transform_flag</Cell>
          <Cell>{{ sps.residual_colour_transform_flag }}</Cell>
        </Row>
        <Row>
          <Cell>bit_depth_luma_minus8</Cell>
          <Cell>{{ sps.bit_depth_luma_minus8 }}</Cell>
        </Row>
        <Row>
          <Cell>bit_depth_chroma_minus8</Cell>
          <Cell>{{ sps.bit_depth_chroma_minus8 }}</Cell>
        </Row>
        <Row>
          <Cell>qpprime_y_zero_transform_bypass_flag</Cell>
          <Cell>{{ sps.qpprime_y_zero_transform_bypass_flag }}</Cell>
        </Row>
        <Row>
          <Cell>seq_scaling_matrix_present_flag</Cell>
          <Cell>{{ sps.seq_scaling_matrix_present_flag }}</Cell>
        </Row>
        <template v-if="sps.seq_scaling_matrix_present_flag">
          <template v-for="(n, i) in 8">
            <Row>
              <Cell>seq_scaling_list_present_flag[{{ i }}]</Cell>
              <Cell>{{ sps.seq_scaling_list_present_flag[i] }}</Cell>
            </Row>
            <template v-if="sps.seq_scaling_list_present_flag[i]">
              <template v-if="i < 6">
                <ScalingList :list="sps.ScalingList4x4" :size="16" :index="i" />
              </template>
              <template v-else>
                <ScalingList
                  :list="sps.ScalingList8x8"
                  :size="64"
                  :index="i - 6"
                />
              </template>
            </template>
          </template>
        </template>
      </template>
      <Row>
        <Cell>log2_max_frame_num_minus4</Cell>
        <Cell>{{ sps.log2_max_frame_num_minus4 }}</Cell>
      </Row>
      <Row>
        <Cell>pic_order_cnt_type</Cell>
        <Cell>{{ sps.pic_order_cnt_type }}</Cell>
      </Row>
      <template v-if="sps.pic_order_cnt_type === 0">
        <Row>
          <Cell>log2_max_pic_order_cnt_lsb_minus4</Cell>
          <Cell>{{ sps.log2_max_pic_order_cnt_lsb_minus4 }}</Cell>
        </Row>
      </template>
      <template v-if="sps.pic_order_cnt_type === 1">
        <TodoRow tag="sps.pic_order_cnt_type === 1" />
        <!--
        TODO
        int delta_pic_order_always_zero_flag;
        int offset_for_non_ref_pic;
        int offset_for_top_to_bottom_field;
        int num_ref_frames_in_pic_order_cnt_cycle;
        int offset_for_ref_frame[256];
        -->
      </template>
      <Row>
        <Cell>num_ref_frames</Cell>
        <Cell>{{ sps.num_ref_frames }}</Cell>
      </Row>
      <Row>
        <Cell>gaps_in_frame_num_value_allowed_flag</Cell>
        <Cell>{{ sps.gaps_in_frame_num_value_allowed_flag }}</Cell>
      </Row>
      <Row>
        <Cell>pic_width_in_mbs_minus1</Cell>
        <Cell>{{ sps.pic_width_in_mbs_minus1 }}</Cell>
      </Row>
      <Row>
        <Cell>pic_height_in_map_units_minus1</Cell>
        <Cell>{{ sps.pic_height_in_map_units_minus1 }}</Cell>
      </Row>
      <Row>
        <Cell>frame_mbs_only_flag</Cell>
        <Cell>{{ sps.frame_mbs_only_flag }}</Cell>
      </Row>
      <Row v-if="!sps.frame_mbs_only_flag">
        <Cell>mb_adaptive_frame_field_flag</Cell>
        <Cell>{{ sps.mb_adaptive_frame_field_flag }}</Cell>
      </Row>
      <Row>
        <Cell>direct_8x8_inference_flag</Cell>
        <Cell>{{ sps.direct_8x8_inference_flag }}</Cell>
      </Row>
      <Row>
        <Cell>frame_cropping_flag</Cell>
        <Cell>{{ sps.frame_cropping_flag }}</Cell>
      </Row>
      <template v-if="sps.frame_cropping_flag">
        <Row>
          <Cell>frame_crop_left_offset</Cell>
          <Cell>{{ sps.frame_crop_left_offset }}</Cell>
        </Row>
        <Row>
          <Cell>frame_crop_right_offset</Cell>
          <Cell>{{ sps.frame_crop_right_offset }}</Cell>
        </Row>
        <Row>
          <Cell>frame_crop_top_offset</Cell>
          <Cell>{{ sps.frame_crop_top_offset }}</Cell>
        </Row>
        <Row>
          <Cell>frame_crop_bottom_offset</Cell>
          <Cell>{{ sps.frame_crop_bottom_offset }}</Cell>
        </Row>
      </template>
      <Row>
        <Cell>vui_parameters_present_flag</Cell>
        <Cell>{{ sps.vui_parameters_present_flag }}</Cell>
      </Row>
    </Table>
    <Table v-if="sps.vui_parameters_present_flag">
      <HeaderRow>
        <HeaderCell>VUI</HeaderCell>
        <HeaderCell></HeaderCell>
      </HeaderRow>
      <Row>
        <Cell>aspect_ratio_info_present_flag</Cell>
        <Cell>{{ vui.aspect_ratio_info_present_flag }}</Cell>
      </Row>
      <template v-if="vui.aspect_ratio_info_present_flag">
        <Row>
          <Cell>aspect_ratio_idc</Cell>
          <Cell>{{ vui.aspect_ratio_idc }}</Cell>
        </Row>
        <template v-if="isExtendedSAR(vui.aspect_ratio_idc)">
          <Row>
            <Cell>sar_width</Cell>
            <Cell>{{ vui.sar_width }}</Cell>
          </Row>
          <Row>
            <Cell>sar_height</Cell>
            <Cell>{{ vui.sar_height }}</Cell>
          </Row>
        </template>
      </template>
      <Row>
        <Cell>overscan_info_present_flag</Cell>
        <Cell>{{ vui.overscan_info_present_flag }}</Cell>
      </Row>
      <template v-if="vui.overscan_info_present_flag">
        <Row>
          <Cell>overscan_appropriate_flag</Cell>
          <Cell>{{ vui.overscan_appropriate_flag }}</Cell>
        </Row>
      </template>
      <Row>
        <Cell>video_signal_type_present_flag</Cell>
        <Cell>{{ vui.video_signal_type_present_flag }}</Cell>
      </Row>
      <template v-if="vui.video_signal_type_present_flag">
        <Row>
          <Cell>video_format</Cell>
          <Cell>{{ vui.video_format }}</Cell>
        </Row>
        <Row>
          <Cell>video_full_range_flag</Cell>
          <Cell>{{ vui.video_full_range_flag }}</Cell>
        </Row>
        <Row>
          <Cell>colour_description_present_flag</Cell>
          <Cell>{{ vui.colour_description_present_flag }}</Cell>
        </Row>
        <template v-if="vui.colour_description_present_flag">
          <Row>
            <Cell>colour_primaries</Cell>
            <Cell>{{ vui.colour_primaries }}</Cell>
          </Row>
          <Row>
            <Cell>transfer_characteristics</Cell>
            <Cell>{{ vui.transfer_characteristics }}</Cell>
          </Row>
          <Row>
            <Cell>matrix_coefficients</Cell>
            <Cell>{{ vui.matrix_coefficients }}</Cell>
          </Row>
        </template>
      </template>
      <Row>
        <Cell>chroma_loc_info_present_flag</Cell>
        <Cell>{{ vui.chroma_loc_info_present_flag }}</Cell>
      </Row>
      <template v-if="vui.chroma_loc_info_present_flag">
        <Row>
          <Cell>chroma_sample_loc_type_top_field</Cell>
          <Cell>{{ vui.chroma_sample_loc_type_top_field }}</Cell>
        </Row>
        <Row>
          <Cell>chroma_sample_loc_type_bottom_field</Cell>
          <Cell>{{ vui.chroma_sample_loc_type_bottom_field }}</Cell>
        </Row>
      </template>
      <Row>
        <Cell>timing_info_present_flag</Cell>
        <Cell>{{ vui.timing_info_present_flag }}</Cell>
      </Row>
      <template v-if="vui.timing_info_present_flag">
        <Row>
          <Cell>num_units_in_tick</Cell>
          <Cell>{{ vui.num_units_in_tick }}</Cell>
        </Row>
        <Row>
          <Cell>time_scale</Cell>
          <Cell>{{ vui.time_scale }}</Cell>
        </Row>
        <Row>
          <Cell>fixed_frame_rate_flag</Cell>
          <Cell>{{ vui.fixed_frame_rate_flag }}</Cell>
        </Row>
      </template>
      <Row>
        <Cell>nal_hrd_parameters_present_flag</Cell>
        <Cell>{{ vui.nal_hrd_parameters_present_flag }}</Cell>
      </Row>
      <template v-if="vui.nal_hrd_parameters_present_flag">
        <HrdParameters :hrd="sps.hrd_nal" />
      </template>
      <Row>
        <Cell>vcl_hrd_parameters_present_flag</Cell>
        <Cell>{{ vui.vcl_hrd_parameters_present_flag }}</Cell>
      </Row>
      <template v-if="vui.vcl_hrd_parameters_present_flag">
        <HrdParameters :hrd="sps.hrd_vcl" />
      </template>
      <template
        v-if="
          vui.nal_hrd_parameters_present_flag ||
            vui.vcl_hrd_parameters_present_flag
        "
      >
        <Row>
          <Cell>low_delay_hrd_flag</Cell>
          <Cell>{{ vui.low_delay_hrd_flag }}</Cell>
        </Row>
      </template>
      <Row>
        <Cell>pic_struct_present_flag</Cell>
        <Cell>{{ vui.pic_struct_present_flag }}</Cell>
      </Row>
      <Row>
        <Cell>bitstream_restriction_flag</Cell>
        <Cell>{{ vui.bitstream_restriction_flag }}</Cell>
      </Row>
      <template v-if="vui.bitstream_restriction_flag">
        <Row>
          <Cell>motion_vectors_over_pic_boundaries_flag</Cell>
          <Cell>{{ vui.motion_vectors_over_pic_boundaries_flag }}</Cell>
        </Row>
        <Row>
          <Cell>max_bytes_per_pic_denom</Cell>
          <Cell>{{ vui.max_bytes_per_pic_denom }}</Cell>
        </Row>
        <Row>
          <Cell>max_bits_per_mb_denom</Cell>
          <Cell>{{ vui.max_bits_per_mb_denom }}</Cell>
        </Row>
        <Row>
          <Cell>log2_max_mv_length_horizontal</Cell>
          <Cell>{{ vui.log2_max_mv_length_horizontal }}</Cell>
        </Row>
        <Row>
          <Cell>log2_max_mv_length_vertical</Cell>
          <Cell>{{ vui.log2_max_mv_length_vertical }}</Cell>
        </Row>
        <Row>
          <Cell>num_reorder_frames</Cell>
          <Cell>{{ vui.num_reorder_frames }}</Cell>
        </Row>
        <Row>
          <Cell>max_dec_frame_buffering</Cell>
          <Cell>{{ vui.max_dec_frame_buffering }}</Cell>
        </Row>
      </template>
    </Table>
  </div>
</template>

<script>
import { PROFILE_IDC, SAR } from '../../lib';

import { Table, Row, Cell, HeaderRow, HeaderCell, TodoRow } from '../Table';

import HrdParameters from './HrdParameters';
import ScalingList from './ScalingList';

export default {
  components: {
    Table,
    Row,
    Cell,
    HeaderRow,
    HeaderCell,
    TodoRow,
    HrdParameters,
    ScalingList,
  },

  computed: {
    vui() {
      return this.sps.vui;
    },
    isRequiredProfile() {
      const profiles = [
        PROFILE_IDC.HiP,
        PROFILE_IDC.Hi10P,
        PROFILE_IDC.Hi422P,
        PROFILE_IDC.Hi444PP,
        PROFILE_IDC.CAVLC,
        PROFILE_IDC.ScalableBP,
        PROFILE_IDC.ScalableHP,
        PROFILE_IDC.MultiviewHP,
        PROFILE_IDC.StereoHP,
        PROFILE_IDC.MultiviewDepthHP,
        PROFILE_IDC.EnchancedMultiviewDepthHP,
        PROFILE_IDC.MFCHP,
      ];

      return profiles.includes(this.sps.profile_idc);
    },
  },

  methods: {
    isExtendedSAR(sar) {
      return sar === SAR.Extended;
    },
  },

  props: {
    sps: Object,
  },
};
</script>

<template>
  <div>
    <Table>
      <Row>
        <Cell>pic_parameter_set_id</Cell>
        <Cell>{{ payload.pic_parameter_set_id }}</Cell>
      </Row>
      <Row>
        <Cell>seq_parameter_set_id</Cell>
        <Cell>{{ payload.seq_parameter_set_id }}</Cell>
      </Row>
      <Row>
        <Cell>entropy_coding_mode_flag</Cell>
        <Cell>{{ payload.entropy_coding_mode_flag }}</Cell>
      </Row>
      <Row>
        <Cell>pic_order_present_flag</Cell>
        <Cell>{{ payload.pic_order_present_flag }}</Cell>
      </Row>
      <Row>
        <Cell>num_slice_groups_minus1</Cell>
        <Cell>{{ payload.num_slice_groups_minus1 }}</Cell>
      </Row>
      <template v-if="payload.num_slice_groups_minus1 > 0">
        <Row warn>
          <Cell>TODO</Cell>
          <Cell>TODO</Cell>
        </Row>
        <!-- TODO if( pps->num_slice_groups_minus1 > 0 ) -->
      </template>
      <Row>
        <Cell>num_ref_idx_l0_active_minus1</Cell>
        <Cell>{{ payload.num_ref_idx_l0_active_minus1 }}</Cell>
      </Row>
      <Row>
        <Cell>num_ref_idx_l1_active_minus1</Cell>
        <Cell>{{ payload.num_ref_idx_l1_active_minus1 }}</Cell>
      </Row>
      <Row>
        <Cell>weighted_pred_flag</Cell>
        <Cell>{{ payload.weighted_pred_flag }}</Cell>
      </Row>
      <Row>
        <Cell>weighted_bipred_idc</Cell>
        <Cell>{{ payload.weighted_bipred_idc }}</Cell>
      </Row>
      <Row>
        <Cell>pic_init_qp_minus26</Cell>
        <Cell>{{ payload.pic_init_qp_minus26 }}</Cell>
      </Row>
      <Row>
        <Cell>pic_init_qs_minus26</Cell>
        <Cell>{{ payload.pic_init_qs_minus26 }}</Cell>
      </Row>
      <Row>
        <Cell>chroma_qp_index_offset</Cell>
        <Cell>{{ payload.chroma_qp_index_offset }}</Cell>
      </Row>
      <Row>
        <Cell>deblocking_filter_control_present_flag</Cell>
        <Cell>{{ payload.deblocking_filter_control_present_flag }}</Cell>
      </Row>
      <Row>
        <Cell>constrained_intra_pred_flag</Cell>
        <Cell>{{ payload.constrained_intra_pred_flag }}</Cell>
      </Row>
      <Row>
        <Cell>redundant_pic_cnt_present_flag</Cell>
        <Cell>{{ payload.redundant_pic_cnt_present_flag }}</Cell>
      </Row>
      <Row>
        <Cell>transform_8x8_mode_flag</Cell>
        <Cell>{{ payload.transform_8x8_mode_flag }}</Cell>
      </Row>
      <Row>
        <Cell>pic_scaling_matrix_present_flag</Cell>
        <Cell>{{ payload.pic_scaling_matrix_present_flag }}</Cell>
      </Row>
      <template v-if="payload.pic_scaling_matrix_present_flag">
        <Row warn>
          <Cell>TODO</Cell>
          <Cell>TODO</Cell>
        </Row>
        <!--
        TODO:
        int pic_scaling_list_present_flag[8];
        int ScalingList4x4[6][16];
        int UseDefaultScalingMatrix4x4Flag[6];
        int ScalingList8x8[2][64];
        int UseDefaultScalingMatrix8x8Flag[2];
        -->
      </template>
      <Row>
        <Cell>second_chroma_qp_index_offset</Cell>
        <Cell>{{ payload.second_chroma_qp_index_offset }}</Cell>
      </Row>
    </Table>
  </div>
</template>

<script>
import { Table, Row, Cell } from './Table';

export default {
  components: {
    Table,
    Row,
    Cell,
  },

  props: {
    payload: {
      type: Object,
      default: () => {},
    },
  },
};
</script>

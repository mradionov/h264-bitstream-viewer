<template>
  <Table>
    <HeaderRow>
      <HeaderCell>PPS</HeaderCell>
    </HeaderRow>
    <Row>
      <Cell>pic_parameter_set_id</Cell>
      <Cell>{{ pps.pic_parameter_set_id }}</Cell>
    </Row>
    <Row>
      <Cell>seq_parameter_set_id</Cell>
      <Cell>{{ pps.seq_parameter_set_id }}</Cell>
    </Row>
    <Row>
      <Cell>entropy_coding_mode_flag</Cell>
      <Cell>{{ pps.entropy_coding_mode_flag }}</Cell>
    </Row>
    <Row>
      <Cell>pic_order_present_flag</Cell>
      <Cell>{{ pps.pic_order_present_flag }}</Cell>
    </Row>
    <Row>
      <Cell>num_slice_groups_minus1</Cell>
      <Cell>{{ pps.num_slice_groups_minus1 }}</Cell>
    </Row>
    <template v-if="pps.num_slice_groups_minus1 > 0">
      <TodoRow tag="if pps->num_slice_groups_minus1 > 0" />
      <!-- TODO if( pps->num_slice_groups_minus1 > 0 ) -->
    </template>
    <Row>
      <Cell>num_ref_idx_l0_active_minus1</Cell>
      <Cell>{{ pps.num_ref_idx_l0_active_minus1 }}</Cell>
    </Row>
    <Row>
      <Cell>num_ref_idx_l1_active_minus1</Cell>
      <Cell>{{ pps.num_ref_idx_l1_active_minus1 }}</Cell>
    </Row>
    <Row>
      <Cell>weighted_pred_flag</Cell>
      <Cell>{{ pps.weighted_pred_flag }}</Cell>
    </Row>
    <Row>
      <Cell>weighted_bipred_idc</Cell>
      <Cell>{{ pps.weighted_bipred_idc }}</Cell>
    </Row>
    <Row>
      <Cell>pic_init_qp_minus26</Cell>
      <Cell>{{ pps.pic_init_qp_minus26 }}</Cell>
    </Row>
    <Row>
      <Cell>pic_init_qs_minus26</Cell>
      <Cell>{{ pps.pic_init_qs_minus26 }}</Cell>
    </Row>
    <Row>
      <Cell>chroma_qp_index_offset</Cell>
      <Cell>{{ pps.chroma_qp_index_offset }}</Cell>
    </Row>
    <Row>
      <Cell>deblocking_filter_control_present_flag</Cell>
      <Cell>{{ pps.deblocking_filter_control_present_flag }}</Cell>
    </Row>
    <Row>
      <Cell>constrained_intra_pred_flag</Cell>
      <Cell>{{ pps.constrained_intra_pred_flag }}</Cell>
    </Row>
    <Row>
      <Cell>redundant_pic_cnt_present_flag</Cell>
      <Cell>{{ pps.redundant_pic_cnt_present_flag }}</Cell>
    </Row>
    <Row>
      <Cell>transform_8x8_mode_flag</Cell>
      <Cell>{{ pps.transform_8x8_mode_flag }}</Cell>
    </Row>
    <Row>
      <Cell>pic_scaling_matrix_present_flag</Cell>
      <Cell>{{ pps.pic_scaling_matrix_present_flag }}</Cell>
    </Row>
    <template v-if="pps.pic_scaling_matrix_present_flag">
      <TodoRow tag="pps.pic_scaling_matrix_present_flag" />
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
      <Cell>{{ pps.second_chroma_qp_index_offset }}</Cell>
    </Row>
  </Table>
</template>

<script>
import { Table, Row, Cell, HeaderRow, HeaderCell, TodoRow } from '../Table';

export default {
  components: {
    Table,
    Row,
    Cell,
    TodoRow,
    HeaderRow,
    HeaderCell,
  },

  props: {
    payload: {
      type: Object,
      default: () => {},
    },
  },

  computed: {
    pps() {
      return this.payload.pps;
    },
  },
};
</script>

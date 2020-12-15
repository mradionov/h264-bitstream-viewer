<template>
  <!-- TODO: different ways to read and display binary: bs_read_u1, bs_read_ue, bs_read_se, etc -->
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
      <!-- TODO: must be tested on real-->
      <template v-if="payload.num_slice_groups_minus1 > 0">
        <Row>
          <Cell>slice_group_map_type</Cell>
          <Cell>{{ payload.slice_group_map_type }}</Cell>
        </Row>
        <template v-if="payload.slice_group_map_type === 0">
          <Row v-for="(_, i) in payload.num_slice_groups_minus1" :key="i">
            <Cell>run_length_minus1[{{ i }}]</Cell>
            <Cell>
              {{ payload.run_length_minus1.get(i) }}
            </Cell>
          </Row>
        </template>
        <template v-if="payload.slice_group_map_type === 2">
          <template v-for="(_, i) in payload.num_slice_groups_minus1">
            <Row :key="`top_left_${i}`">
              <Cell>top_left[{{ i }}]</Cell>
              <Cell>{{ payload.top_left.get(i) }}</Cell>
            </Row>
            <Row :key="`bottom_right_${i}`">
              <Cell>bottom_right[{{ i }}]</Cell>
              <Cell>{{ payload.bottom_right.get(i) }}</Cell>
            </Row>
          </template>
        </template>
        <template
          v-if="
            payload.slice_group_map_type === 3 ||
              payload.slice_group_map_type === 4 ||
              payload.slice_group_map_type === 5
          "
        >
          <Row>
            <Cell>slice_group_change_direction_flag</Cell>
            <Cell>{{ payload.slice_group_change_direction_flag }}</Cell>
          </Row>
          <Row>
            <Cell>slice_group_change_rate_minus1</Cell>
            <Cell>{{ payload.slice_group_change_rate_minus1 }}</Cell>
          </Row>
        </template>
        <template v-if="payload.slice_group_map_type === 6">
          <Row>
            <Cell>pic_size_in_map_units_minus1</Cell>
            <Cell>{{ payload.pic_size_in_map_units_minus1 }}</Cell>
          </Row>
          <Row v-for="(_, i) in payload.pic_size_in_map_units_minus1" :key="i">
            <!-- TODO: v = intlog2 -->
            <Cell>slice_group_id[{{ i }}]</Cell>
            <Cell>{{ payload.slice_group_id.get(i) }}</Cell>
          </Row>
        </template>
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

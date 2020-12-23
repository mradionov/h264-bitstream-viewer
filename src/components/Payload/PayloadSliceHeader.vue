<template>
  <Table>
    <Row>
      <Cell>first_mb_in_slice</Cell>
      <Cell>{{ sh.first_mb_in_slice }}</Cell>
    </Row>
    <Row>
      <Cell>slice_type</Cell>
      <Cell>{{ sh.slice_type }}</Cell>
    </Row>
    <Row>
      <Cell>pic_parameter_set_id</Cell>
      <Cell>{{ sh.pic_parameter_set_id }}</Cell>
    </Row>
    <template v-if="sps.residual_colour_transform_flag">
      <Row>
        <Cell>colour_plane_id</Cell>
        <Cell>{{ sh.colour_plane_id }}</Cell>
      </Row>
    </template>
    <Row>
      <Cell>frame_num</Cell>
      <Cell>{{ sh.frame_num }}</Cell>
    </Row>
    <template v-if="!sps.frame_mbs_only_flag">
      <Row>
        <Cell>field_pic_flag</Cell>
        <Cell>{{ sh.field_pic_flag }}</Cell>
      </Row>
      <template v-if="sh.field_pic_flag">
        <Row>
          <Cell>bottom_field_flag</Cell>
          <Cell>{{ sh.bottom_field_flag }}</Cell>
        </Row>
      </template>
    </template>
    <template v-if="header.type === NALU_TYPES.CODED_SLICE_IDR">
      <Row>
        <Cell>idr_pic_id</Cell>
        <Cell>{{ sh.idr_pic_id }}</Cell>
      </Row>
    </template>
    <template v-if="sps.pic_order_cnt_type === 0">
      <Row>
        <Cell>pic_order_cnt_lsb</Cell>
        <Cell>{{ sh.pic_order_cnt_lsb }}</Cell>
      </Row>
      <template v-if="pps.pic_order_present_flag && !sh.field_pic_flag">
        <Row>
          <Cell>delta_pic_order_cnt_bottom</Cell>
          <Cell>{{ sh.delta_pic_order_cnt_bottom }}</Cell>
        </Row>
      </template>
    </template>
    <template
      v-if="
        sps.pic_order_cnt_type == 1 && !sps.delta_pic_order_always_zero_flag
      "
    >
      <Row>
        <Cell>delta_pic_order_cnt[0]</Cell>
        <Cell>{{ sh.delta_pic_order_cnt[0] }}</Cell>
      </Row>
      <template v-if="pps.pic_order_present_flag && !sh.field_pic_flag">
        <Row>
          <Cell>delta_pic_order_cnt[1]</Cell>
          <Cell>{{ sh.delta_pic_order_cnt[1] }}</Cell>
        </Row>
      </template>
    </template>
    <template v-if="pps.redundant_pic_cnt_present_flag">
      <Row>
        <Cell>redundant_pic_cnt</Cell>
        <Cell>{{ sh.redundant_pic_cnt }}</Cell>
      </Row>
    </template>
    <template v-if="isSliceType(sh.slice_type, SLICE_TYPES.B)">
      <Row>
        <Cell>direct_spatial_mv_pred_flag</Cell>
        <Cell>{{ sh.direct_spatial_mv_pred_flag }}</Cell>
      </Row>
    </template>
    <template
      v-if="
        isSliceType(sh.slice_type, SLICE_TYPES.P) ||
          isSliceType(sh.slice_type, SLICE_TYPES.SP) ||
          isSliceType(sh.slice_type, SLICE_TYPES.B)
      "
    >
      <Row>
        <Cell>num_ref_idx_active_override_flag</Cell>
        <Cell>{{ sh.num_ref_idx_active_override_flag }}</Cell>
      </Row>
      <template v-if="sh.num_ref_idx_active_override_flag">
        <Row>
          <Cell>num_ref_idx_l0_active_minus1</Cell>
          <Cell>{{ sh.num_ref_idx_l0_active_minus1 }}</Cell>
        </Row>
        <template v-if="isSliceType(sh.slice_type, SLICE_TYPES.B)">
          <Row>
            <Cell>num_ref_idx_l1_active_minus1</Cell>
            <Cell>{{ sh.num_ref_idx_l1_active_minus1 }}</Cell>
          </Row>
        </template>
      </template>
    </template>
    <!-- TODO read_debug_ref_pic_list_reordering -->
    <TodoRow />
    <template
      v-if="
        (pps.weighted_pred_flag &&
          (isSliceType(sh.slice_type, SLICE_TYPES.P) ||
            isSliceType(sh.slice_type, SLICE_TYPES.SP))) ||
          (pps.weighted_bipred_idc === 1 &&
            isSliceType(sh.slice_type, SLICE_TYPES.B))
      "
    >
      <!-- TODO read_debug_pred_weight_table(h, b); -->
      <TodoRow />
    </template>
    <template v-if="header.refIdc !== 0">
      <!-- TODO read_debug_dec_ref_pic_marking -->
      <TodoRow />
    </template>
    <template
      v-if="
        pps.entropy_coding_mode_flag &&
          !isSliceType(sh.slice_type, SLICE_TYPES.I) &&
          !isSliceType(sh.slice_type, SLICE_TYPES.SI)
      "
    >
      <Row>
        <Cell>cabac_init_idc</Cell>
        <Cell>{{ sh.cabac_init_idc }}</Cell>
      </Row>
    </template>
    <Row>
      <Cell>slice_qp_delta</Cell>
      <Cell>{{ sh.slice_qp_delta }}</Cell>
    </Row>
    <template
      v-if="
        isSliceType(sh.slice_type, SLICE_TYPES.SP) ||
          isSliceType(sh.slice_type, SLICE_TYPES.SI)
      "
    >
      <template v-if="isSliceType(sh.slice_type, SLICE_TYPES.SP)">
        <Row>
          <Cell>sp_for_switch_flag</Cell>
          <Cell>{{ sh.sp_for_switch_flag }}</Cell>
        </Row>
      </template>
      <Row>
        <Cell>slice_qs_delta</Cell>
        <Cell>{{ sh.slice_qs_delta }}</Cell>
      </Row>
    </template>
    <template v-if="pps.deblocking_filter_control_present_flag">
      <Row>
        <Cell>disable_deblocking_filter_idc</Cell>
        <Cell>{{ sh.disable_deblocking_filter_idc }}</Cell>
      </Row>
      <template v-if="sh.disable_deblocking_filter_idc !== 1">
        <Row>
          <Cell>slice_alpha_c0_offset_div2</Cell>
          <Cell>{{ sh.slice_alpha_c0_offset_div2 }}</Cell>
        </Row>
        <Row>
          <Cell>slice_beta_offset_div2</Cell>
          <Cell>{{ sh.slice_beta_offset_div2 }}</Cell>
        </Row>
      </template>
    </template>
    <template
      v-if="
        pps.num_slice_groups_minus1 > 0 &&
          pps.slice_group_map_type >= 3 &&
          pps.slice_group_map_type <= 5
      "
    >
      <Row>
        <Cell>slice_group_change_cycle</Cell>
        <Cell>{{ sh.slice_group_change_cycle }}</Cell>
      </Row>
    </template>
  </Table>
</template>

<script>
import { Table, Row, Cell, TodoRow } from '../Table';

import { NALU_TYPES, SLICE_TYPES } from '../../lib';

export default {
  components: {
    Table,
    Row,
    Cell,
    TodoRow,
  },

  props: {
    payload: {
      type: Object,
      default: () => {},
    },
  },

  data() {
    return { NALU_TYPES, SLICE_TYPES };
  },

  computed: {
    header() {
      return this.payload.header;
    },
    sh() {
      return this.payload.sh;
    },
    sps() {
      return this.payload.sps;
    },
    pps() {
      return this.payload.pps;
    },
  },

  methods: {
    isSliceType(sliceType, cmpType) {
      if (sliceType >= 5) {
        sliceType -= 5;
      }
      if (cmpType >= 5) {
        cmpType -= 5;
      }
      return sliceType === cmpType;
    },
  },
};
</script>

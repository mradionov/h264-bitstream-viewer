<template>
  <tbody>
    <Row>
      <Cell>pwt.luma_log2_weight_denom</Cell>
      <Cell>{{ pwt.luma_log2_weight_denom }}</Cell>
    </Row>
    <template v-if="sps.chroma_format_idc !== 0">
      <Row>
        <Cell>pwt.chroma_log2_weight_denom</Cell>
        <Cell>{{ pwt.chroma_log2_weight_denom }}</Cell>
      </Row>
    </template>
    <template
      v-if="pps.num_ref_idx_l0_active_minus1 > 0"
      v-for="(v, i) in pps.num_ref_idx_l0_active_minus1 + 1"
    >
      <Row>
        <Cell>pwt.luma_weight_l0_flag[{{ i }}]</Cell>
        <Cell>{{ pwt.luma_weight_l0_flag[i] }}</Cell>
      </Row>
      <template v-if="pwt.luma_weight_l0_flag[i]">
        <Row>
          <Cell>pwt.luma_weight_l0[{{ i }}]</Cell>
          <Cell>{{ pwt.luma_weight_l0[i] }}</Cell>
        </Row>
        <Row>
          <Cell>pwt.luma_offset_l0[{{ i }}]</Cell>
          <Cell>{{ pwt.luma_offset_l0[i] }}</Cell>
        </Row>
      </template>
      <template v-if="sps.chroma_format_idc !== 0">
        <Row>
          <Cell>pwt.chroma_weight_l0_flag[{{ i }}]</Cell>
          <Cell>{{ pwt.chroma_weight_l0_flag[i] }}</Cell>
        </Row>
        <template v-if="pwt.chroma_weight_l0_flag[i]">
          <template v-for="(v2, j) in 2">
            <Row>
              <Cell>pwt.chroma_weight_l0[{{ i }}][{{ j }}]</Cell>
              <Cell>{{
                pwt.chroma_weight_l0[i * pps.num_ref_idx_l0_active_minus1 + j]
              }}</Cell>
            </Row>
            <Row>
              <Cell>pwt.chroma_offset_l0[{{ i }}][{{ j }}]</Cell>
              <Cell>{{
                pwt.chroma_offset_l0[i * pps.num_ref_idx_l0_active_minus1 + j]
              }}</Cell>
            </Row>
          </template>
        </template>
      </template>
    </template>
    <template v-if="isSliceType(header.type, SLICE_TYPES.B)">
      <template
        v-if="pps.num_ref_idx_l1_active_minus1 > 0"
        v-for="(v, i) in pps.num_ref_idx_l1_active_minus1 + 1"
      >
        <Row>
          <Cell>pwt.luma_weight_l1_flag[{{ i }}]</Cell>
          <Cell>{{ pwt.luma_weight_l1_flag[i] }}</Cell>
        </Row>
        <template v-if="pwt.luma_weight_l1_flag[i]">
          <Row>
            <Cell>pwt.luma_weight_l1[{{ i }}]</Cell>
            <Cell>{{ pwt.luma_weight_l1[i] }}</Cell>
          </Row>
          <Row>
            <Cell>pwt.luma_offset_l1[{{ i }}]</Cell>
            <Cell>{{ pwt.luma_offset_l1[i] }}</Cell>
          </Row>
        </template>
        <template v-if="sps.chroma_format_idc !== 0">
          <Row>
            <Cell>pwt.chroma_weight_l1_flag[{{ i }}]</Cell>
            <Cell>{{ pwt.chroma_weight_l1_flag[i] }}</Cell>
          </Row>
          <template v-if="pwt.chroma_weight_l1_flag[i]">
            <template v-for="(v2, j) in 2">
              <Row>
                <Cell>pwt.chroma_weight_l1[{{ i }}][{{ j }}]</Cell>
                <Cell>{{
                  pwt.chroma_weight_l1[i * pps.num_ref_idx_l1_active_minus1 + j]
                }}</Cell>
              </Row>
              <Row>
                <Cell>pwt.chroma_offset_l1[{{ i }}][{{ j }}]</Cell>
                <Cell>{{
                  pwt.chroma_offset_l1[i * pps.num_ref_idx_l1_active_minus1 + j]
                }}</Cell>
              </Row>
            </template>
          </template>
        </template>
      </template>
    </template>
  </tbody>
</template>

<script>
import { NALU_TYPES, SLICE_TYPES } from '../../lib';

import { Table, Row, Cell, TodoRow } from '../Table';

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
    sps() {
      return this.payload.sps;
    },
    pps() {
      return this.payload.pps;
    },
    sh() {
      return this.payload.sh;
    },
    pwt() {
      return this.sh.pwt;
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

<style module></style>

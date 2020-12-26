<template>
  <tbody>
    <template v-if="header.type === NALU_TYPES.CODED_SLICE_IDR">
      <Row>
        <Cell>drpm.no_output_of_prior_pics_flag</Cell>
        <Cell>{{ drpm.no_output_of_prior_pics_flag }}</Cell>
      </Row>
      <Row>
        <Cell>drpm.long_term_reference_flag</Cell>
        <Cell>{{ drpm.long_term_reference_flag }}</Cell>
      </Row>
    </template>
    <template v-else>
      <Row>
        <Cell>drpm.adaptive_ref_pic_marking_mode_flag</Cell>
        <Cell>{{ drpm.adaptive_ref_pic_marking_mode_flag }}</Cell>
      </Row>
      <template v-if="drpm.adaptive_ref_pic_marking_mode_flag">
        <template v-for="(n, i) in mmco_size">
          <Row>
            <Cell>drpm.memory_management_control_operation[{{ i }}]</Cell>
            <Cell>{{ drpm.memory_management_control_operation[i] }}</Cell>
          </Row>
          <template
            v-if="
              drpm.memory_management_control_operation[i] === 1 ||
                drpm.memory_management_control_operation[i] === 3
            "
          >
            <Row>
              <Cell>drpm.difference_of_pic_nums_minus1[{{ i }}]</Cell>
              <Cell>{{ drpm.difference_of_pic_nums_minus1[i] }}</Cell>
            </Row>
          </template>
          <template v-if="drpm.memory_management_control_operation[i] === 2">
            <Row>
              <Cell>drpm.long_term_pic_num[{{ i }}]</Cell>
              <Cell>{{ drpm.long_term_pic_num[i] }}</Cell>
            </Row>
          </template>
          <template
            v-if="
              drpm.memory_management_control_operation[i] === 3 ||
                drpm.memory_management_control_operation[i] === 6
            "
          >
            <Row>
              <Cell>drpm.long_term_frame_idx[{{ i }}]</Cell>
              <Cell>{{ drpm.long_term_frame_idx[i] }}</Cell>
            </Row>
          </template>
          <template v-if="drpm.memory_management_control_operation[i] === 4">
            <Row>
              <Cell>drpm.max_long_term_frame_idx_plus1[{{ i }}]</Cell>
              <Cell>{{ drpm.max_long_term_frame_idx_plus1[i] }}</Cell>
            </Row>
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
    sh() {
      return this.payload.sh;
    },
    drpm() {
      return this.sh.drpm;
    },
    mmco_size() {
      const size = this.getSize(this.drpm.memory_management_control_operation);
      if (size > 0) {
        return size + 1;
      }
      return 0;
    },
  },

  methods: {
    getSize(field) {
      let n = -1;

      do {
        n++;
      } while (field[n] !== 0);

      return n;
    },
  },
};
</script>

<style module></style>

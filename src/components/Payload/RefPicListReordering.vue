<template>
  <tbody>
    <template
      v-if="
        !isSliceType(sh.slice_type, SLICE_TYPES.I) &&
          !isSliceType(sh.slice_type, SLICE_TYPES.SI)
      "
    >
      <Row>
        <Cell>rplr.ref_pic_list_reordering_flag_l0</Cell>
        <Cell>{{ rplr.ref_pic_list_reordering_flag_l0 }}</Cell>
      </Row>
      <template v-if="rplr.ref_pic_list_reordering_flag_l0">
        <Row>
          <Cell>rplr.ref_pic_list_reordering_flag_l0</Cell>
          <Cell>{{ rplr.ref_pic_list_reordering_flag_l0 }}</Cell>
        </Row>
        <template v-if="rplr.ref_pic_list_reordering_flag_l0">
          <template v-for="(v, i) in reorder_l0_size">
            <Row>
              <Cell>rplr.reorder_l0.reordering_of_pic_nums_idc[{{ i }}]</Cell>
              <Cell>{{ rplr.reorder_l0.reordering_of_pic_nums_idc[i] }}</Cell>
            </Row>
            <template
              v-if="
                rplr.reorder_l0.reordering_of_pic_nums_idc[i] === 0 ||
                  sh.rplr.reorder_l0.reordering_of_pic_nums_idc[i] === 1
              "
            >
              <Row>
                <Cell>rplr.reorder_l0.abs_diff_pic_num_minus1[{{ i }}]</Cell>
                <Cell>{{ rplr.reorder_l0.abs_diff_pic_num_minus1[i] }}</Cell>
              </Row>
            </template>
            <template
              v-else-if="rplr.reorder_l0.reordering_of_pic_nums_idc[i] === 2"
            >
              <Row>
                <Cell>rplr.reorder_l0.long_term_pic_num[{{ i }}]</Cell>
                <Cell>{{ rplr.reorder_l0.long_term_pic_num[i] }}</Cell>
              </Row>
            </template>
          </template>
        </template>
      </template>
    </template>
    <template v-if="isSliceType(sh.slice_type, SLICE_TYPES.B)">
      <Row>
        <Cell>rplr.ref_pic_list_reordering_flag_l1</Cell>
        <Cell>{{ rplr.ref_pic_list_reordering_flag_l1 }}</Cell>
      </Row>
      <template v-if="rplr.ref_pic_list_reordering_flag_l1">
        <TodoRow tag="rplr.ref_pic_list_reordering_flag_l1" />
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
    return { SLICE_TYPES };
  },

  computed: {
    sh() {
      return this.payload.sh;
    },
    rplr() {
      return this.sh.rplr;
    },
    reorder_l0_size() {
      const size = this.getSize(
        this.rplr.reorder_l0.reordering_of_pic_nums_idc,
      );
      if (size > 0) {
        return size + 1;
      }
      return 0;
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

    getSize(field) {
      let n = -1;

      do {
        n++;
      } while (field[n] !== 3);

      return n;
    },
  },
};
</script>

<style module></style>

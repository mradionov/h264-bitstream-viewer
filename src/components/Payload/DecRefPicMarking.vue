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
        <TodoRow tag="drpm.adaptive_ref_pic_marking_mode_flag" />
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
  },
};
</script>

<style module></style>

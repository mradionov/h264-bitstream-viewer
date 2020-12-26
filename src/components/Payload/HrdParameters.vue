<template>
  <tbody>
    <Row>
      <Cell>hrd.cpb_cnt_minus1</Cell>
      <Cell>{{ hrd.cpb_cnt_minus1 }}</Cell>
    </Row>
    <Row>
      <Cell>hrd.bit_rate_scale</Cell>
      <Cell>{{ hrd.bit_rate_scale }}</Cell>
    </Row>
    <Row>
      <Cell>hrd.cpb_size_scale</Cell>
      <Cell>{{ hrd.cpb_size_scale }}</Cell>
    </Row>
    <template v-for="(v, i) in hrd.cpb_cnt_minus1 + 1">
      <Row>
        <Cell>hrd.bit_rate_value_minus1[{{ i }}]</Cell>
        <Cell>{{ hrd.bit_rate_value_minus1[i] }}</Cell>
      </Row>
      <Row>
        <Cell>hrd.cpb_size_value_minus1[{{ i }}]</Cell>
        <Cell>{{ hrd.cpb_size_value_minus1[i] }}</Cell>
      </Row>
      <Row>
        <Cell>hrd.cbr_flag[{{ i }}]</Cell>
        <Cell>{{ hrd.cbr_flag[i] }}</Cell>
      </Row>
    </template>
    <Row>
      <Cell>hrd.initial_cpb_removal_delay_length_minus1</Cell>
      <Cell>{{ hrd.initial_cpb_removal_delay_length_minus1 }}</Cell>
    </Row>
    <Row>
      <Cell>hrd.cpb_removal_delay_length_minus1</Cell>
      <Cell>{{ hrd.cpb_removal_delay_length_minus1 }}</Cell>
    </Row>
    <Row>
      <Cell>hrd.dpb_output_delay_length_minus1</Cell>
      <Cell>{{ hrd.dpb_output_delay_length_minus1 }}</Cell>
    </Row>
    <Row>
      <Cell>hrd.time_offset_length</Cell>
      <Cell>{{ hrd.time_offset_length }}</Cell>
    </Row>
  </tbody>
</template>

<script>
import { Table, Row, Cell, HeaderRow, HeaderCell, TodoRow } from '../Table';

export default {
  components: {
    Table,
    Row,
    Cell,
    HeaderRow,
    HeaderCell,
    TodoRow,
  },
  props: {
    hrd: Object,
  },
};
</script>

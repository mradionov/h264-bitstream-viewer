<template>
  <div>
    <Table>
      <Row>
        <HeaderCell>Type</HeaderCell>
        <Cell>
          {{ unitHeader.type }}
          <i>({{ unitHeader.type | naluTypeDisplayed }})</i>
        </Cell>
      </Row>
      <Row>
        <HeaderCell>Reference idc</HeaderCell>
        <Cell>{{ unitHeader.refIdc }}</Cell>
      </Row>
      <Row>
        <HeaderCell>Forbidden zero bit</HeaderCell>
        <Cell>{{ unitHeader.forbiddenZeroBit }}</Cell>
      </Row>
    </Table>
    <Table :class="$style.range">
      <Row>
        <HeaderCell>Number</HeaderCell>
        <Cell>{{ number }}</Cell>
      </Row>
      <Row>
        <HeaderCell>Offset</HeaderCell>
        <Cell>{{ range.start + 3 }}</Cell>
      </Row>
      <Row>
        <HeaderCell>Size</HeaderCell>
        <Cell>{{ range.size - 3 }}</Cell>
      </Row>
    </Table>
  </div>
</template>

<script>
import { Table, Row, Cell, HeaderCell } from './Table';

export default {
  components: {
    Table,
    Row,
    Cell,
    HeaderCell,
  },

  props: {
    number: {
      type: Number,
      default: -1,
    },
    range: {
      type: Object,
      default: () => ({
        start: -1,
        end: -1,
        size: 0,
      }),
    },
    unitHeader: {
      type: Object,
      default: () => ({
        type: -1,
        refIdc: -1,
        forbiddenZeroBit: -1,
      }),
    },
  },
};
</script>

<style module>
.range {
  margin-top: 10px;
}
</style>

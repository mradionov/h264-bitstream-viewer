<template>
  <div>
    <Table>
      <Row>
        <HeaderCell>Type</HeaderCell>
        <Cell>
          {{ header.type }}
          <i>({{ header.type | naluTypeDisplayed }})</i>
        </Cell>
      </Row>
      <Row>
        <HeaderCell>Reference idc</HeaderCell>
        <Cell>{{ header.refIdc }}</Cell>
      </Row>
      <Row>
        <HeaderCell>Forbidden zero bit</HeaderCell>
        <Cell>{{ header.forbiddenZeroBit }}</Cell>
      </Row>
    </Table>
    <Table :class="$style.location">
      <Row>
        <HeaderCell>Number</HeaderCell>
        <Cell>{{ number }}</Cell>
      </Row>
      <Row>
        <HeaderCell>Offset</HeaderCell>
        <Cell>{{ header.start + 3 }}</Cell>
      </Row>
      <Row>
        <HeaderCell>Size</HeaderCell>
        <Cell>{{ header.size - 3 }}</Cell>
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
    header: {
      type: Object,
      default: () => ({
        start: -1,
        end: -1,
        size: 0,
        type: -1,
        refIdc: -1,
        forbiddenZeroBit: -1,
      }),
    },
  },
};
</script>

<style module>
.location {
  margin-top: 10px;
}
</style>

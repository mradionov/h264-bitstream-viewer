<template>
  <Table>
    <HeaderRow slot="header">
      <HeaderCell sticky>#</HeaderCell>
      <HeaderCell sticky colspan="2">Unit type</HeaderCell>
      <HeaderCell sticky>Reference idc</HeaderCell>
      <HeaderCell sticky>Forbidden zero bit</HeaderCell>
    </HeaderRow>
    <Row
      v-for="(header, index) in headers"
      :key="index"
      :class="[$style.row, isSelected(index) && $style.selected]"
      @click.native="handleRowClick(header, index)"
    >
      <Cell>{{ index + indexOffset }}</Cell>
      <Cell>
        <strong>{{ header.type }}</strong>
      </Cell>
      <Cell>{{ header.type | naluTypeDisplayed }}</Cell>
      <Cell>{{ header.refIdc }}</Cell>
      <Cell>{{ header.forbiddenZeroBit }}</Cell>
    </Row>
  </Table>
</template>

<script>
import { Table, HeaderRow, HeaderCell, Row, Cell } from './Table';

export default {
  components: {
    Table,
    HeaderRow,
    HeaderCell,
    Row,
    Cell,
  },

  props: {
    indexOffset: {
      type: Number,
      default: 0,
    },
    selectedIndex: {
      type: Number,
      default: -1,
    },
    headers: {
      type: Array,
      default: () => [],
    },
  },

  methods: {
    getThruIndex(index) {
      return index + this.indexOffset;
    },
    isSelected(index) {
      return this.selectedIndex === this.getThruIndex(index);
    },
    handleRowClick(unitHeader, index) {
      if (this.isSelected(index)) {
        return;
      }
      this.$emit('select', unitHeader, this.getThruIndex(index));
    },
  },
};
</script>

<style module>
.row {
  user-select: none;
}

.row:hover {
  background: #eee;
  cursor: pointer;
}

.row.selected {
  background: #c5e5ff;
}
</style>

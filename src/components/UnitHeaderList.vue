<template>
  <Table>
    <HeaderRow slot="header">
      <HeaderCell>#</HeaderCell>
      <HeaderCell colspan="2">Unit type</HeaderCell>
      <HeaderCell>Reference idc</HeaderCell>
      <HeaderCell>Forbidden zero bit</HeaderCell>
    </HeaderRow>
    <Row
      v-for="(unitHeader, index) in unitHeaders"
      :key="index"
      :class="[$style.row, isSelected(index) && $style.selected]"
      @click.native="handleRowClick(unitHeader, index)"
    >
      <Cell>{{ index + indexOffset + 1 }}</Cell>
      <Cell>
        <strong>{{ unitHeader.type }}</strong>
      </Cell>
      <Cell>{{ unitHeader.type | naluTypeDisplayed }}</Cell>
      <Cell>{{ unitHeader.refIdc }}</Cell>
      <Cell>{{ unitHeader.forbiddenZeroBit }}</Cell>
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
    unitHeaders: {
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

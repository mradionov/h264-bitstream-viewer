<template>
  <CollapseRows :items="deltaScales" title="delta_scale" />
</template>

<script>
import { Table, Row, Cell, CollapseRows } from '../Table';

export default {
  components: {
    Table,
    Row,
    Cell,
    CollapseRows,
  },

  computed: {
    deltaScales() {
      const selfList = this.list.slice(
        this.index * this.size,
        this.index * this.size + this.size,
      );

      const deltaScales = [];

      deltaScales.push(selfList[0] - 8);

      for (let i = 0; i < this.size - 1; i++) {
        deltaScales.push(selfList[i + 1] - selfList[i]);
      }

      return deltaScales;
    },
  },

  props: {
    list: Array,
    size: Number,
    index: Number,
  },
};
</script>

<style module></style>

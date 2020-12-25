<template>
  <tbody>
    <Row v-for="(deltaScale, i) in deltaScales" :key="i">
      <Cell>delta_scale[{{ i }}]</Cell>
      <Cell>{{ deltaScale }}</Cell>
    </Row>
  </tbody>
</template>

<script>
import { Table, Row, Cell } from '../Table';

export default {
  components: {
    Table,
    Row,
    Cell,
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

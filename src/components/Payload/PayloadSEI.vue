<template>
  <div>
    <Table v-for="(v, i) in sei.size()" :key="i">
      <HeaderRow>
        <HeaderCell> [{{ i }}] </HeaderCell>
        <HeaderCell>
          {{ sei.get(i).payloadType | seiTypeDisplayed }}
        </HeaderCell>
      </HeaderRow>
      <Row>
        <Cell>Type</Cell>
        <Cell>{{ sei.get(i).payloadType }}</Cell>
      </Row>
      <Row>
        <Cell>Size</Cell>
        <Cell>{{ sei.get(i).payloadSize }}</Cell>
      </Row>
      <Row>
        <Cell>Data</Cell>
        <Cell><Bytes :bytes="getBytesArray(i)"/></Cell>
      </Row>
    </Table>
  </div>
</template>

<script>
import { Table, Row, Cell, HeaderCell, HeaderRow } from '../Table';

import Bytes from './Bytes';

export default {
  components: {
    Table,
    Row,
    Cell,
    HeaderRow,
    HeaderCell,
    Bytes,
  },

  props: {
    payload: {
      type: Object,
      default: () => {},
    },
  },

  computed: {
    sei() {
      return this.payload.sei;
    },
  },

  methods: {
    getBytesArray(i) {
      const bytes = this.sei.get(i).data;
      const arr = [];

      for (let i = 0; i < bytes.size(); i++) {
        arr.push(bytes.get(i));
      }

      return arr;
    },
  },
};
</script>

<style module></style>

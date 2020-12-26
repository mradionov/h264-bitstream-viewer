<template>
  <table>
    <HeaderRow>
      <HeaderCell>AUD</HeaderCell>
    </HeaderRow>
    <Row>
      <Cell>primary_pic_type</Cell>
      <Cell>
        {{ aud.primary_pic_type }} ({{
          aud.primary_pic_type | audPrimaryPicTypeDisplayed
        }})
      </Cell>
    </Row>
  </table>
</template>

<script>
import { Table, Row, Cell, HeaderRow, HeaderCell, TodoRow } from '../Table';

export default {
  components: {
    Table,
    Row,
    Cell,
    TodoRow,
    HeaderRow,
    HeaderCell,
  },

  props: {
    payload: Object,
  },

  computed: {
    aud() {
      return this.payload.aud;
    },
  },
};
</script>

<template>
  <div :class="$style.container">
    <span>&#9432; Shortcuts</span>
    <div :class="$style.popup">
      <Table>
        <Row>
          <HeaderCell>Prev page</HeaderCell>
          <Cell>Arrow Left</Cell>
        </Row>
        <Row>
          <HeaderCell>Next page</HeaderCell>
          <Cell>Arrow Right</Cell>
        </Row>
        <Row>
          <HeaderCell>Prev item</HeaderCell>
          <Cell>Arrow Up</Cell>
        </Row>
        <Row>
          <HeaderCell>Next item</HeaderCell>
          <Cell>Arrow Down</Cell>
        </Row>
        <Row>
          <HeaderCell>Go to page</HeaderCell>
          <Cell>P</Cell>
        </Row>
        <Row>
          <HeaderCell>Go to item</HeaderCell>
          <Cell>I</Cell>
        </Row>
      </Table>
    </div>
  </div>
</template>

<script>
import { Table, HeaderCell, Row, Cell } from './Table';

export default {
  components: {
    Table,
    HeaderCell,
    Row,
    Cell,
  },
};
</script>

<style module>
.container {
  padding-top: 3px;
  position: relative;
}

.container:hover .popup {
  display: block;
}

.popup {
  background: #eee;
  border: 1px solid #777;
  bottom: 15px;
  display: none;
  padding: 20px;
  position: absolute;
  right: 0;
  width: 250px;
}
</style>

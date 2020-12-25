<template>
  <div>
    <Table>
      <TodoRow :tag="`type ${payload.header.type}`" />
    </Table>
  </div>
</template>

<script>
import { Table, TodoRow } from '../Table';

export default {
  components: {
    Table,
    TodoRow,
  },

  props: {
    payload: Object,
  },
};
</script>

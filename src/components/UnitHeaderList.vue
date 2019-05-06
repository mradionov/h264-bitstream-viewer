<template>
  <table :class="$style.table">
    <thead>
      <th :class="$style.cell">#</th>
      <th :class="$style.cell" colspan="2">Unit type</th>
      <th :class="$style.cell">Reference idc</th>
      <th :class="$style.cell">Forbidden zero bit</th>
    </thead>
    <tbody :class="$style.body">
      <tr
        v-for="(unitHeader, index) in unitHeaders"
        :key="index"
        :class="$style.row"
        @click="$emit('select', unitHeader, index + indexOffset)"
      >
        <td :class="$style.cell">{{ index + indexOffset + 1 }}</td>
        <td :class="$style.cell">
          <strong>{{ unitHeader.type }}</strong>
        </td>
        <td :class="$style.cell">{{ unitHeader.type | nalTypeDisplayed }}</td>
        <td :class="$style.cell">{{ unitHeader.refIdc }}</td>
        <td :class="$style.cell">{{ unitHeader.forbiddenZeroBit }}</td>
      </tr>
    </tbody>
  </table>
</template>

<script>
export default {
  props: {
    indexOffset: {
      type: Number,
      default: 0,
    },
    unitHeaders: {
      type: Array,
      default: () => [],
    },
  },
};
</script>

<style module>
.table {
  border-collapse: collapse;
}

.body .row:hover {
  background: #eee;
  cursor: pointer;
}

.cell {
  padding: 5px;
}
</style>

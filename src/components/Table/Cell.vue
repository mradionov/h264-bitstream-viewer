<template>
  <td :class="$style.cell" :style="{ paddingLeft: `${level * 10}px` }">
    <slot />
  </td>
</template>

<script>
export default {
  props: {
    level: {
      type: Number,
      default: 0,
    },
  },
};
</script>

<style module>
.cell {
  padding: 5px;
  vertical-align: top;
}
</style>

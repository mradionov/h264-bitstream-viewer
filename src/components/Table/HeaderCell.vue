<template>
  <th :class="{ [$style.cell]: true, [$style.sticky]: sticky }">
    <slot />
  </th>
</template>

<script>
export default {
  props: {
    sticky: {
      type: Boolean,
      default: false,
    },
  },
};
</script>

<style module>
.cell {
  background: #fff;
  text-align: left;
  padding: 5px;
  top: 0;
}

.sticky {
  position: sticky;
}
</style>

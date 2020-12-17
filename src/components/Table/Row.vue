<template>
  <tbody :class="{ [$style.warn]: warn }">
    <tr>
      <slot />
    </tr>
  </tbody>
</template>

<script>
export default {
  props: {
    warn: {
      type: Boolean,
      default: false,
    },
  },
};
</script>

<style module>
.warn {
  background: #fbd7d4;
}
</style>

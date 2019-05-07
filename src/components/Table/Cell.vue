<template>
  <td :class="$style.cell">
    <slot />
  </td>
</template>

<style module>
.cell {
  padding: 5px;
}
</style>

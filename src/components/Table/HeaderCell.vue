<template>
  <th :class="$style.cell">
    <slot />
  </th>
</template>

<style module>
.cell {
  background: #fff;
  padding: 5px;
  position: sticky;
  top: 0;
}
</style>

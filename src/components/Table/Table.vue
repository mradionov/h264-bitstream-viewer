<template>
  <table :class="$style.table">
    <thead>
      <slot name="header" />
    </thead>
    <slot />
  </table>
</template>

<style module>
.table {
  border-collapse: collapse;
  text-align: left;
}
</style>

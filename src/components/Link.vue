<template>
  <a :class="$style.link" :href="to"><slot /></a>
</template>

<script>
export default {
  props: {
    to: String,
  },
};
</script>

<style module>
.link {
  color: #555;
}

.link:hover {
  color: #aaa;
}
</style>

<template>
  <div :class="$style.loading">
    <UiProgressCircular :progress="progress" type="determinate" />
    <span :class="$style.loadingText">Loading ...</span>
  </div>
</template>

<script>
import { UiProgressCircular } from 'keen-ui';

export default {
  components: {
    UiProgressCircular,
  },
  props: {
    progress: Number,
  },
};
</script>

<style module>
.loading {
  display: flex;
  margin-left: 10px;
}

.loadingText {
  margin-left: 10px;
  padding: 7px 0;
}
</style>

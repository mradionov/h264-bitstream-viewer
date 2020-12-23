<template>
  <div :class="$style.about">
    H264 Bitstream Viewer
    <span :class="$style.separator">|</span>
    <Link to="https://github.com/mradionov/h264-bitstream-viewer">
      GitHub
    </Link>
  </div>
</template>

<script>
import Link from './Link';

export default {
  components: { Link },
};
</script>

<style module>
.about {
  color: #555;
}

.separator {
  color: #aaa;
  margin: 0 10px;
}
</style>

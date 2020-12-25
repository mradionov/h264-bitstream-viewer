<template>
  <Row :class="$style.warn">
    <Cell>
      TODO
      <span v-if="tag.length > 0"> ({{ tag }})</span>
    </Cell>
    <Cell>
      Missing details. If you see this please
      <a
        href="https://github.com/mradionov/h264-bitstream-viewer/issues"
        target="_blank"
      >
        create an issue on the GitHub
      </a>
      and provide your h264 for reproduction. It will be fixed if
      <a href="https://github.com/aizvorski/h264bitstream" target="_blank">
        h264bitstream
      </a>
      has it implemented.
    </Cell>
  </Row>
</template>

<script>
import Cell from './Cell';
import Row from './Row';

export default {
  components: {
    Cell,
    Row,
  },

  props: {
    tag: {
      type: String,
      default: '',
    },
  },
};
</script>

<style module>
.warn {
  background: #fbd7d4;
}
</style>

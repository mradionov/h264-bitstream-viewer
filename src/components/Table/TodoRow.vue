<template>
  <Row :class="$style.warn">
    <Cell>TODO</Cell>
    <Cell>
      Missing details. If you see this please
      <a
        href="https://github.com/mradionov/h264-bitstream-viewer/issues"
        target="_blank"
      >
        create an issue on the GitHub
      </a>
      and provide your h264 for reproduction
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
};
</script>

<style module>
.warn {
  background: #fbd7d4;
}
</style>

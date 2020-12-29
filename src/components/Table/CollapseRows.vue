<template>
  <tbody>
    <Row>
      <Cell :class="$style.toggle" colspan="2" @click.native="handleToggle">
        <span :class="$style.symbol" v-html="symbol" />
        {{ title }}[0 ... {{ items.length - 1 }}]
      </Cell>
    </Row>
    <Row v-if="isOpen" v-for="(v, i) in items">
      <Cell :level="2">{{ title }}[{{ i }}]</Cell>
      <Cell>{{ items[i] }}</Cell>
    </Row>
  </tbody>
</template>

<script>
import Row from './Row';
import Cell from './Cell';

export default {
  components: {
    Row,
    Cell,
  },
  props: {
    title: String,
    items: {
      type: Array,
      default: () => [],
    },
  },
  data() {
    return {
      isOpen: false,
    };
  },
  computed: {
    symbol() {
      return this.isOpen ? '&#9660;' : '&#9658;';
    },
  },
  methods: {
    handleToggle() {
      console.log('click');
      this.isOpen = !this.isOpen;
    },
  },
};
</script>

<style module>
.toggle {
  cursor: pointer;
}

.symbol {
  color: #777;
  font-size: 80%;
  display: inline-block;
  width: 12px;
}
</style>

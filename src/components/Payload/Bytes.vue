<template>
  <div>
    <div :class="$style.header">
      <UiRadioGroup :options="options" v-model="selectedValue" name="options" />
    </div>
    <div>{{ output }}</div>
  </div>
</template>

<script>
import { UiRadioGroup } from 'keen-ui';

const VALUE_TYPE = {
  STRING: 'string',
  HEX: 'hex',
};

export default {
  components: {
    UiRadioGroup,
  },

  props: {
    bytes: Array,
  },

  data() {
    return {
      selectedValue: VALUE_TYPE.STRING,
      options: [
        { label: 'string', value: VALUE_TYPE.STRING },
        { label: 'hex', value: VALUE_TYPE.HEX },
      ],
    };
  },

  computed: {
    output() {
      if (this.selectedValue === VALUE_TYPE.STRING) {
        return this.outputString;
      }
      return this.outputHex;
    },
    outputString() {
      let out = '';

      for (let i = 0; i < this.bytes.length; i++) {
        out += String.fromCharCode(this.bytes[i]);
      }

      return out;
    },
    outputHex() {
      let out = '';

      for (let i = 0; i < this.bytes.length; i++) {
        out += this.bytes[i].toString(16) + ' ';
      }

      return out;
    },
  },
};
</script>

<style module>
.header {
  background: #eee;
  margin-bottom: 10px;
  padding: 1px 10px;
}
</style>

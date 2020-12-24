<template>
  <div v-html="formattedPayload" />
</template>

<script>
export default {
  props: {
    payload: {
      type: Object,
    },
  },
  computed: {
    formattedPayload() {
      if (this.payload.naked === null) {
        return;
      }
      const formattedText = this.payload.naked
        .split('\n')
        .map((line) => {
          const match = line.match(/^\s+/);
          if (match) {
            const space = '&nbsp;&nbsp;';
            return (
              space.repeat(match[0].length) + line.substring(match[0].length)
            );
          }
          return line;
        })
        .join('<br />');

      return formattedText;
    },
  },
};
</script>

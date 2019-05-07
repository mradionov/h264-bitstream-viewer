<template>
  <div v-html="formattedDetails" />
</template>

<script>
export default {
  props: {
    details: {
      type: String,
      default: null,
    },
  },
  computed: {
    formattedDetails() {
      if (this.details === null) {
        return '';
      }

      const formattedText = this.details
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

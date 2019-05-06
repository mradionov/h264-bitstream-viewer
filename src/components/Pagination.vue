<template>
  <div :class="$style.container">
    <div :class="$style.text">
      Per page:
    </div>
    <select
      :class="$style.perPage"
      :disabled="!hasPages"
      @change="handlePerPageChange"
    >
      <option
        v-for="perPageOption in perPageOptions"
        :selected="perPage == perPageOption"
        :value="perPageOption"
      >
        {{ perPageOption }}
      </option>
    </select>

    <div
      :class="[$style.button, (!hasPages || isFirst) && $style.disabled]"
      title="First page"
      @click="handleFirstClick"
    >
      <<
    </div>
    <div
      :class="[$style.button, (!hasPages || isFirst) && $style.disabled]"
      title="Prev page"
      @click="handlePrevClick"
    >
      <
    </div>

    <div :class="$style.page">
      {{ hasPages ? currentPage : 0 }}
    </div>
    <div :class="$style.text">
      of
    </div>
    <div :class="$style.page">
      {{ totalPages }}
    </div>

    <div
      :class="[$style.button, (!hasPages || isLast) && $style.disabled]"
      title="Next page"
      @click="handleNextClick"
    >
      >
    </div>
    <div
      :class="[$style.button, (!hasPages || isLast) && $style.disabled]"
      title="Last page"
      @click="handleLastClick"
    >
      >>
    </div>

    <div
      :class="[$style.button, $style.jump, !hasPages && $style.disabled]"
      @click="handleJump"
    >
      Go to page
    </div>
  </div>
</template>

<script>
export default {
  props: {
    currentPage: {
      type: Number,
      default: 1,
    },
    perPage: {
      type: Number,
      default: 20,
    },
    perPageOptions: {
      type: Array,
      default: () => [20, 30, 50, 100],
    },
    totalPages: {
      type: Number,
      default: 0,
    },
    separator: {
      type: String,
      default: '...',
    },
  },

  computed: {
    hasPages() {
      return this.totalPages > 0;
    },
    isFirst() {
      return this.currentPage === 1;
    },
    isLast() {
      return this.currentPage === this.totalPages;
    },
  },

  methods: {
    isActive(page) {
      return page === this.currentPage;
    },
    isSeparator(page) {
      return page === this.separator;
    },

    handlePerPageChange(ev) {
      const nextPerPage = Number(ev.target.value);

      this.$emit('perPageChange', nextPerPage);
    },

    handleFirstClick() {
      const nextPage = 1;

      this.$emit('change', nextPage);
    },
    handleLastClick() {
      const nextPage = this.totalPages;

      this.$emit('change', nextPage);
    },
    handlePrevClick() {
      const nextPage = Math.max(1, this.currentPage - 1);

      this.$emit('change', nextPage);
    },
    handleNextClick() {
      const nextPage = Math.min(this.totalPages, this.currentPage + 1);

      this.$emit('change', nextPage);
    },
    handlePageClick(page) {
      if (this.isActive(page) || this.isSeparator(page)) {
        return;
      }

      this.$emit('change', page);
    },
    handleJump() {
      const answer = window.prompt('Jump to page:');

      let nextPage = Number(answer);
      if (!nextPage) {
        return;
      }

      nextPage = Math.max(1, nextPage);
      nextPage = Math.min(this.totalPages, nextPage);

      this.$emit('change', nextPage);
    },
  },
};
</script>

<style module>
.container {
  color: #555;
  display: flex;
}

.text {
  color: #888;
  padding: 5px;
}

.page {
  color: #222;
  min-width: 35px;
  padding: 5px;
  text-align: center;
}

.button {
  padding: 5px;
  text-decoration: underline;
  user-select: none;
}

.button:hover {
  cursor: pointer;
  color: #aaa;
}

.disabled {
  color: #ccc;
  pointer-events: none;
}

.perPage {
  margin-right: 25px;
}

.jump {
  margin-left: 25px;
}
</style>

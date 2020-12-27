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
      &lt;&lt;
    </div>
    <div
      :class="[$style.button, (!hasPages || isFirst) && $style.disabled]"
      title="Prev page"
      @click="handlePrevClick"
    >
      &lt;
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
      &gt;
    </div>
    <div
      :class="[$style.button, (!hasPages || isLast) && $style.disabled]"
      title="Last page"
      @click="handleLastClick"
    >
      &gt;&gt;
    </div>

    <div
      :class="[$style.button, $style.jump, !hasPages && $style.disabled]"
      @click="handlePageJump"
    >
      Go to page
    </div>

    <div
      :class="[$style.button, $style.jump, !hasPages && $style.disabled]"
      @click="handleItemJump"
    >
      Go to item
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
      default: () => [1, 20, 30, 50, 100],
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
      this.emitChange(1);
    },
    handleLastClick() {
      this.emitChange(this.totalPages);
    },
    handlePrevClick() {
      const nextPage = Math.max(1, this.currentPage - 1);

      this.emitChange(nextPage);
    },
    handleNextClick() {
      const nextPage = Math.min(this.totalPages, this.currentPage + 1);

      this.emitChange(nextPage);
    },
    handlePageClick(page) {
      if (this.isActive(page) || this.isSeparator(page)) {
        return;
      }

      this.emitChange(page);
    },
    handlePageJump() {
      const answer = window.prompt('Jump to page:');

      let nextPage = Number(answer);
      if (!nextPage) {
        return;
      }

      nextPage = this.clampPage(nextPage);

      this.emitChange(nextPage);
    },
    handleItemJump() {
      const answer = window.prompt('Jump to item:');

      let globalItemIndex = Number(answer);
      if (!globalItemIndex) {
        return;
      }

      const page = this.clampPage(Math.ceil(globalItemIndex / this.perPage));

      const localItemIndex = globalItemIndex - (page - 1) * this.perPage;

      this.emitChange(page, globalItemIndex, localItemIndex);
    },
    emitChange(page, globalItemIndex = -1, localItemIndex = -1) {
      const event = { page, globalItemIndex, localItemIndex };

      this.$emit('change', event);
    },
    clampPage(inputPage) {
      let nextPage = inputPage;

      nextPage = Math.max(1, nextPage);
      nextPage = Math.min(this.totalPages, nextPage);

      return nextPage;
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

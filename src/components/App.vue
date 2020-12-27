<template>
  <div :class="$style.app">
    <div v-if="isLoadingModule" :class="$style.loading">
      <div>Loading...</div>
      <br />
      <div>Please refresh the page, if it is not loading for a long time</div>
    </div>
    <div v-else :class="$style.container">
      <div :class="$style.header">
        <div :class="$style.upload">
          <UiFileupload name="file" @change="handleFile" />
          <Loader v-if="isLoadingFile" :progress="progress" />
        </div>
        <About />
      </div>
      <div :class="$style.content">
        <div :class="$style.list">
          <div :class="$style.scrollable">
            <HeaderList
              :indexOffset="indexOffset"
              :selectedIndex="selectedGlobalIndex"
              :headers="pageHeaders"
              @select="handleHeaderSelect"
            />
          </div>
          <div :class="$style.footer">
            <Pagination
              :currentPage="currentPage"
              :perPage="perPage"
              :totalPages="totalPages"
              @change="handlePageChange"
              @perPageChange="handlePerPageChange"
            />
            <Shortcuts :class="$style.shortcuts" />
          </div>
        </div>
        <div :class="$style.data">
          <UiTabs v-if="hasPayload" :class="$style.tabs">
            <UiTab title="Payload">
              <Payload :payload="payload" />
            </UiTab>
            <UiTab title="NAL">
              <HeaderInfo
                :index="selectedGlobalIndex"
                :header="selectedHeader"
              />
            </UiTab>
          </UiTabs>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import { UiFileupload, UiTabs, UiTab } from 'keen-ui';

import About from './About';
import HeaderInfo from './HeaderInfo';
import HeaderList from './HeaderList';
import Loader from './Loader';
import Pagination from './Pagination';
import Payload from './Payload';
import Shortcuts from './Shortcuts';

import {
  H264BitstreamBinding,
  H264BitstreamFile,
  NALU_TYPES,
  makeKeydownListener,
  KEY_CODES,
} from '../lib';

export default {
  components: {
    UiFileupload,
    UiTabs,
    UiTab,

    About,
    HeaderInfo,
    HeaderList,
    Loader,
    Pagination,
    Payload,
    Shortcuts,
  },

  data() {
    return {
      isLoadingModule: true,
      isLoadingFile: false,
      progress: 0,
      totalHeaders: 0,
      selectedGlobalIndex: -1,
      payload: null,
      currentPage: 1,
      perPage: 30,
      pageHeaders: [],
    };
  },

  // https://github.com/vuejs/vue/issues/1988
  binding: null,
  bitstream: null,

  computed: {
    hasPayload() {
      return this.payload !== null;
    },
    indexOffset() {
      return (this.currentPage - 1) * this.perPage;
    },
    totalPages() {
      return Math.ceil(this.totalHeaders / this.perPage);
    },
    selectedHeader() {
      const noHeader = {
        start: -1,
        end: -1,
        size: 0,
        forbiddenZeroBit: -1,
        refIdc: -1,
        type: -1,
      };

      const selectedHeader = this.$options.bitstream.headers[
        this.selectedGlobalIndex
      ];
      if (selectedHeader === undefined) {
        return noHeader;
      }

      return selectedHeader;
    },
    pageStart() {
      return (this.currentPage - 1) * this.perPage;
    },
    pageEnd() {
      return this.pageStart + this.perPage;
    },
    isSelectedIndexOutOfPage() {
      return (
        this.selectedGlobalIndex < this.pageStart ||
        this.selectedGlobalIndex > this.pageEnd
      );
    },
  },

  mounted() {
    Module.onRuntimeInitialized = () => {
      this.isLoadingModule = false;
    };

    // Don't care about removing event listeners as it's only on instance of
    // this component.
    makeKeydownListener(KEY_CODES.ARROW_UP, () => {
      const nextIndex = this.isSelectedIndexOutOfPage
        ? this.localToGlobalIndex(0)
        : this.selectedGlobalIndex - 1;
      this.loadPayload(nextIndex);
    });
    makeKeydownListener(KEY_CODES.ARROW_DOWN, () => {
      const nextIndex = this.isSelectedIndexOutOfPage
        ? this.localToGlobalIndex(0)
        : this.selectedGlobalIndex + 1;
      this.loadPayload(nextIndex);
    });
  },

  methods: {
    reset() {
      this.isLoadingFile = false;
      this.progress = 0;
      this.totalHeaders = 0;
      this.selectedGlobalIndex = -1;
      this.payload = null;
      this.currentPage = 1;
      this.pageHeaders = [];

      if (this.$options.binding !== null) {
        this.$options.binding.destroy();
        this.$options.binding = null;
      }

      if (this.$options.bitstream !== null) {
        this.$options.bitstream.destroy();
        this.$options.bitstream = null;
      }
    },

    handleFile(files) {
      this.reset();

      if (files.length === 0) {
        return;
      }

      const file = files[0];

      const bitstream = new H264BitstreamFile(file);

      bitstream.addEventListener('start', () => {
        this.isLoadingFile = true;
      });

      bitstream.addEventListener('progress', (progress) => {
        this.progress = progress;
      });

      bitstream.addEventListener('end', () => {
        this.isLoadingFile = false;
        this.totalHeaders = this.$options.bitstream.getTotalHeaders();
        this.loadPage();
      });

      const binding = new H264BitstreamBinding(bitstream);

      bitstream.load();

      this.$options.bitstream = bitstream;
      this.$options.binding = binding;
    },

    async handlePageChange({ page, globalItemIndex }) {
      this.currentPage = page;
      await this.loadPage();

      // If entered in pagination component
      if (globalItemIndex !== -1) {
        this.loadPayload(globalItemIndex);
      }
    },

    async handlePerPageChange(perPage) {
      this.currentPage = 1;
      this.perPage = perPage;
      this.loadPage();
    },

    async handleHeaderSelect({ header, globalIndex }) {
      this.loadPayload(globalIndex);
    },

    async loadPayload(globalIndex) {
      const localIndex = this.globalToLocalIndex(globalIndex);

      const header = this.pageHeaders[localIndex];
      if (header === undefined) {
        return;
      }
      const payload = await this.$options.binding.read(header);

      console.log({ header, payload });

      this.selectedGlobalIndex = globalIndex;
      this.payload = payload;
    },

    loadPage() {
      this.pageHeaders = this.$options.bitstream.headers.slice(
        this.pageStart,
        this.pageEnd,
      );
    },

    localToGlobalIndex(localIndex) {
      return (this.currentPage - 1) * this.perPage + localIndex;
    },

    globalToLocalIndex(globalIndex) {
      return globalIndex - (this.currentPage - 1) * this.perPage;
    },
  },
};
</script>

<style module>
.app {
  display: flex;
  flex: 1;
  flex-direction: column;
  min-height: 0;
}

.loading {
  padding: 20px;
  flex: 1;
}

.container {
  display: flex;
  flex: 1;
  flex-direction: column;
  min-height: 0;
  padding: 10px;
}

.header {
  display: flex;
  padding: 10px 0;
}

.upload {
  display: flex;
  flex: 1;
}

.content {
  display: flex;
  flex: 1;
  min-height: 0;
}

.list {
  flex: 1;
  display: flex;
  flex-direction: column;
}

.scrollable {
  flex: 1;
  min-height: 0;
  overflow: auto;
}

.footer {
  display: flex;
  padding: 10px 0;
}

.shortcuts {
  margin-left: 15px;
}

.data {
  display: flex;
  flex: 1;
  flex-direction: column;
  min-height: 0;
  padding: 5px 20px;
}

.tabs {
  display: flex;
  flex: 1;
  flex-direction: column;
  min-height: 0;
}
.tabs > :global(.ui-tabs__body) {
  display: flex;
  flex-direction: column;
  min-height: 0;
  overflow: auto;
}
</style>

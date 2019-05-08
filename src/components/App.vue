<template>
  <div :class="$style.container">
    <div :class="$style.header">
      <UiFileupload name="file" @change="handleFile" />
      <div v-if="isLoading" :class="$style.loading">
        <UiProgressCircular :progress="progress" type="determinate" />
        <span :class="$style.loadingText">Loading ...</span>
      </div>
    </div>
    <div :class="$style.content">
      <div :class="$style.list">
        <div :class="$style.scrollable">
          <UnitHeaderList
            :indexOffset="indexOffset"
            :selectedIndex="selectedIndex"
            :unitHeaders="unitHeaders"
            @select="handleUnitHeaderSelect"
          />
        </div>
        <Pagination
          :class="$style.pagination"
          :currentPage="currentPage"
          :perPage="perPage"
          :totalPages="totalPages"
          @change="handlePageChange"
          @perPageChange="handlePerPageChange"
        />
      </div>
      <div :class="$style.details">
        <UiTabs v-if="hasDetails">
          <UiTab title="NAL">
            <TabUnit
              :number="this.selectedNumber"
              :range="selectedRange"
              :unitHeader="selectedUnitHeader"
            />
          </UiTab>
          <UiTab title="Details">
            <TabDetails :details="details" />
          </UiTab>
        </UiTabs>
      </div>
    </div>
  </div>
</template>

<script>
import { UiFileupload, UiProgressCircular, UiTabs, UiTab } from 'keen-ui';

import Pagination from './Pagination';
import TabDetails from './TabDetails';
import TabUnit from './TabUnit';
import UnitHeaderList from './UnitHeaderList';

import FileChunkReader from '../lib/FileChunkReader';
import FileReadStream from '../lib/FileReadStream';
import H264BitstreamParser from '../lib/H264BitstreamParser';
import H264BitstreamOffsetStream from '../lib/H264BitstreamOffsetStream';

export default {
  components: {
    UiFileupload,
    UiProgressCircular,
    UiTabs,
    UiTab,

    Pagination,
    TabDetails,
    TabUnit,
    UnitHeaderList,
  },

  data() {
    return {
      isLoading: false,
      lastLoadedOffset: 0,
      totalRanges: 0,
      selectedIndex: -1,
      selectedUnitHeader: null,
      details: null,
      currentPage: 1,
      perPage: 30,
      unitHeaders: [],
    };
  },

  // https://github.com/vuejs/vue/issues/1988
  file: null,
  ranges: [],

  computed: {
    progress() {
      if (!this.isLoading) {
        return 0;
      }

      if (!this.$options.file) {
        return 0;
      }

      const progress = (this.lastLoadedOffset / this.$options.file.size) * 100;

      return progress;
    },
    hasDetails() {
      return this.details !== null;
    },
    indexOffset() {
      return (this.currentPage - 1) * this.perPage;
    },
    totalPages() {
      return Math.ceil(this.totalRanges / this.perPage);
    },
    selectedNumber() {
      if (this.selectedIndex === -1) {
        return -1;
      }
      return this.selectedIndex + 1;
    },
    selectedRange() {
      const noRange = {
        start: -1,
        end: -1,
        size: 0,
      };

      const selectedRange = this.$options.ranges[this.selectedIndex];
      if (selectedRange === undefined) {
        return noRange;
      }

      return selectedRange;
    },
  },

  methods: {
    reset() {
      this.$options.file = null;
      this.$options.ranges = [];

      this.isLoading = false;

      this.lastLoadedOffset = 0;
      this.totalRanges = 0;
      this.selectedIndex = -1;
      this.selectedUnitHeader = null;
      this.details = null;
      this.currentPage = 1;
      this.unitHeaders = [];
    },

    handleFile(files) {
      this.reset();

      if (files.length === 0) {
        return;
      }

      const file = files[0];

      this.isLoading = true;
      this.$options.file = file;

      const ranges = [];

      const offsetStream = new H264BitstreamOffsetStream();

      offsetStream.addEventListener('data', async (range) => {
        this.lastLoadedOffset = range.end;
        ranges.push(range);
      });

      offsetStream.addEventListener('end', async () => {
        this.$options.ranges = ranges;
        this.totalRanges = ranges.length;
        this.isLoading = false;

        this.loadPage();
      });

      const fileStream = new FileReadStream(this.$options.file);

      fileStream.addEventListener('data', (chunkBuffer) => {
        offsetStream.appendData(new Uint8Array(chunkBuffer));
      });

      fileStream.addEventListener('end', () => {
        offsetStream.finish();
      });

      fileStream.start();
    },

    handlePageChange(nextPage) {
      this.currentPage = nextPage;
      this.loadPage();
    },

    handlePerPageChange(perPage) {
      this.perPage = perPage;
      this.loadPage();
    },

    async handleUnitHeaderSelect(unitHeader, index) {
      this.selectedUnitHeader = unitHeader;

      const range = this.$options.ranges[index];
      if (range === undefined) {
        return;
      }

      this.selectedIndex = index;

      const chunkReader = new FileChunkReader(this.$options.file);
      const buffer = await chunkReader.readAsArrayBuffer(
        range.start,
        range.end,
      );
      const data = new Uint8Array(buffer);

      const dataNoStartCode = data.slice(3);

      const reader = new window.Module.Reader();
      const text = this.read(reader, dataNoStartCode);

      this.details = text;
    },

    async loadPage() {
      const pageStart = (this.currentPage - 1) * this.perPage;
      const pageEnd = pageStart + this.perPage;

      const pageRanges = this.$options.ranges.slice(pageStart, pageEnd);
      if (pageRanges.length === 0) {
        return;
      }

      const start = pageRanges[0].start;
      const end = pageRanges[pageRanges.length - 1].end;

      const chunkReader = new FileChunkReader(this.$options.file);
      const buffer = await chunkReader.readAsArrayBuffer(start, end);
      const data = new Uint8Array(buffer);

      const unitHeaders = pageRanges.map((range) => {
        const offset = range.start - start;

        const unitHeader = H264BitstreamParser.readUnitHeader(data, offset);

        return unitHeader;
      });

      this.unitHeaders = unitHeaders;
    },

    read(reader, data) {
      const unitData32 = new Int32Array(data);

      const numBytes = unitData32.length * unitData32.BYTES_PER_ELEMENT;
      const ptr = Module._malloc(numBytes);

      const heapBytes = new Uint8Array(Module.HEAPU8.buffer, ptr, numBytes);
      heapBytes.set(new Uint8Array(unitData32.buffer));

      const ret = reader.read(ptr, unitData32.length);

      Module._free(ptr);

      return ret;
    },
  },
};
</script>

<style module>
.container {
  display: flex;
  flex: 1;
  flex-direction: column;
  padding: 10px;
}

.header {
  display: flex;
  padding: 10px 0;
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

.pagination {
  padding: 10px 0;
}

.details {
  flex: 1;
  min-height: 0;
  overflow: auto;
  padding: 5px 20px;
}

.loading {
  display: flex;
  margin-left: 10px;
}

.loadingText {
  margin-left: 10px;
  padding: 7px 0;
}
</style>

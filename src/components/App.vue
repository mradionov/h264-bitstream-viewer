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
      <div :class="$style.details" v-html="formattedDetails" />
    </div>
  </div>
</template>

<script>
import { UiFileupload, UiProgressCircular } from 'keen-ui';

import Pagination from './Pagination';
import UnitHeaderList from './UnitHeaderList';

import FileChunkReader from '../lib/FileChunkReader';
import FileReadStream from '../lib/FileReadStream';
import H264BitstreamParser from '../lib/H264BitstreamParser';
import H264BitstreamOffsetStream from '../lib/H264BitstreamOffsetStream';

export default {
  components: {
    UiFileupload,
    UiProgressCircular,

    Pagination,
    UnitHeaderList,
  },

  data() {
    return {
      isLoading: false,
      lastLoadedOffset: 0,
      details: null,
      currentPage: 1,
      perPage: 30,
      ranges: [],
      unitHeaders: [],
    };
  },

  file: null,

  computed: {
    progress() {
      if (!this.isLoading) {
        return 0;
      }

      if (!this.file) {
        return 0;
      }

      const progress = (this.lastLoadedOffset / this.file.size) * 100;

      return progress;
    },
    indexOffset() {
      return (this.currentPage - 1) * this.perPage;
    },
    totalPages() {
      return Math.ceil(this.ranges.length / this.perPage);
    },
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

  methods: {
    handleFile(files) {
      if (files.length === 0) {
        return;
      }

      const file = files[0];
      this.file = file;

      this.isLoading = true;

      const ranges = [];

      const offsetStream = new H264BitstreamOffsetStream();

      offsetStream.addEventListener('data', (range) => {
        this.lastLoadedOffset = range.end;
        ranges.push(range);
      });

      offsetStream.addEventListener('end', async () => {
        this.ranges = ranges;
        this.isLoading = false;

        this.loadPage();
      });

      const fileStream = new FileReadStream(file);

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

    async loadPage() {
      const pageStart = (this.currentPage - 1) * this.perPage;
      const pageEnd = pageStart + this.perPage;

      const pageRanges = this.ranges.slice(pageStart, pageEnd);
      if (pageRanges.length === 0) {
        return;
      }

      const start = pageRanges[0].start;
      const end = pageRanges[pageRanges.length - 1].end;

      const chunkReader = new FileChunkReader(this.file);
      const buffer = await chunkReader.readAsArrayBuffer(start, end);
      const data = new Uint8Array(buffer);

      const unitHeaders = pageRanges.map((range) => {
        const offset = range.start - start;

        const unitHeader = H264BitstreamParser.readUnitHeader(data, offset);

        return unitHeader;
      });

      this.unitHeaders = unitHeaders;
    },

    createUnit(index, dataWithStartCode) {
      const data = dataWithStartCode.slice(3);
      const header = data[0];
      const forbiddenZeroBit = header >> 7;
      const refIdc = (header >> 5) & 0x3;
      const type = header & 0x1f;

      const unit = {
        index,
        data,
        forbiddenZeroBit,
        refIdc,
        type,
      };

      return unit;
    },

    async handleUnitHeaderSelect(unitHeader, index) {
      const range = this.ranges[index];
      if (range === undefined) {
        return;
      }

      const chunkReader = new FileChunkReader(this.file);
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

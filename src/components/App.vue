<template>
  <div :class="$style.container">
    <div :class="$style.header">
      <UiFileupload name="file" @change="handleFile"/>
    </div>
    <div :class="$style.content">
      <div :class="$style.list">
        <table>
          <thead>
            <th>#</th>
            <th colspan="2">Unit type</th>
            <th>Reference idc</th>
            <th>Forbidden zero bit</th>
          </thead>
          <tbody>
            <tr v-for="unit in units" :key="unit.index" @click="handleDetails(unit)">
              <td>{{unit.index}}</td>
              <td><strong>{{unit.type}}</strong></td>
              <td>{{unit.type | nalTypeDisplayed }}</td>
              <td>{{unit.refIdc}}</td>
              <td>{{unit.forbiddenZeroBit}}</td>
            </tr>
          </tbody>
        </table>
      </div>
      <div :class="$style.details" v-html="formattedDetails" />
    </div>
  </div>
</template>

<script>
import { UiFileupload } from 'keen-ui';

export default {
  components: {
    UiFileupload,
  },

  data() {
    return {
      details: null,
      units: [],
    };
  },

  computed: {
    formattedDetails() {
      if (!this.details) {
        return '';
      }

      const formattedText = this.details.split('\n').map((line) => {
        const match = line.match(/^\s+/);
        if (match) {
          return '&nbsp;&nbsp;'.repeat(match[0].length) + line.substring(match[0].length);
        }
        return line;
      }).join('<br />');

      return formattedText;
    },
  },

  methods: {
    handleFile(files) {
      if (files.length === 0) {
        return;
      }

      const file = files[0];

      const reader = new FileReader();

      this.units = [];

      reader.addEventListener('load', (ev) => {
        this.parse(ev.target.result);
      });
      reader.readAsArrayBuffer(file);
    },

    parse(buffer) {
      const data = new Uint8Array(buffer);

      let offset = 0;

      // Cut off leading zero bytes
      for (; offset < data.length; offset += 1) {
        if (data[offset] === 0
          && data[offset + 1] === 0
          && data[offset + 2] === 0
          && data[offset + 3] === 0
        ) {
          continue;
        }
        break;
      }

      let lastOffset = null;
      const units = [];

      for (; offset < data.length; offset += 1) {
        if (data[offset] === 0
          && data[offset + 1] === 0
          && data[offset + 2] === 0
          && lastOffset !== null
        ) {
          const unitData = data.subarray(lastOffset, offset);
          units.push(this.createUnit(units.length, unitData));
          lastOffset = null;
        }

        if (data[offset] === 0
          && data[offset + 1] === 0
          && data[offset + 2] === 1
        ) {
          if (lastOffset !== null) {
            const unitData = data.subarray(lastOffset, offset);
            units.push(this.createUnit(units.length, unitData));
          }

          lastOffset = offset;
        }

        if (offset === data.length - 1
          && lastOffset !== null
        ) {
          const unitData = data.subarray(lastOffset, data.length);
          units.push(this.createUnit(units.length, unitData));
        }

        // Cut off four-byte start-code sequence (convert it to three-bytes start
        // code sequence).
        if (data[offset] === 0
          && data[offset + 1] === 0
          && data[offset + 2] === 0
          && data[offset + 3] === 1
        ) {
          continue;
        }

        if (lastOffset === null
          && data[offset] === 0
        ) {
          continue;
        }
      }

      this.units = units;
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

    handleDetails(unit) {
      const reader = new window.Module.Reader();
      const text = this.read(reader, unit);

      this.details = text;
    },

    read(reader, unit) {
      const unitData32 = new Int32Array(unit.data);

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

<style>
html, body {
  height: 100%;
  margin: 0;
  padding: 0;
}

body {
  display: flex;
  flex-direction: column;
}

table {
  border-collapse: collapse;
}

tbody tr:hover {
  background: #eee;
  cursor: pointer;
}

th, td {
  padding: 5px;
}
</style>

<style module>
.container {
  display: flex;
  flex: 1;
  flex-direction: column;
  padding: 10px;
}

.header {
  padding: 10px 0;
}

.content {
  display: flex;
  flex: 1;
  min-height: 0;
}

.list {
  flex: 1;
  min-height: 0;
  overflow: auto;
}

.details {
  flex: 1;
  min-height: 0;
  overflow: auto;
  padding: 0 20px;
}
</style>

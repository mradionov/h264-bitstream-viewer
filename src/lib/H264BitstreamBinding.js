import { EventEmitter } from './EventEmitter';
import { NALU_TYPES } from './H264BitstreamConstants';

const MAP_TYPE_TO_METHOD_NAME = {
  [NALU_TYPES.PPS]: 'readPPS',
  [NALU_TYPES.SPS]: 'readSPS',
  [NALU_TYPES.SEI]: 'readSEI',
  [NALU_TYPES.CODED_SLICE_IDR]: 'readSliceHeader',
  [NALU_TYPES.CODED_SLICE_NON_IDR]: 'readSliceHeader',
  [NALU_TYPES.CODED_SLICE_AUX]: 'readSliceHeader',
  [NALU_TYPES.CODED_SLICE_SVC_EXTENSION]: 'readSliceHeader',
};

const STATE = {
  READY: 0,
  DESTROYED: 1,
};

export class H264BitstreamBinding extends EventEmitter {
  constructor(bitstream) {
    super();

    this.bitstream = bitstream;

    this.binding = new window.Module.Reader();
    this.state = STATE.READY;
  }

  destroy() {
    if (this.state === STATE.READY) {
      this.binding.delete();
      this.binding = null;
    }

    this.bitstream = null;
    this.state = STATE.DESTROYED;
  }

  async read(header) {
    const data = await this.bitstream.getUnitData(header);

    let payload = this.createPayload(header);

    if (header.type === NALU_TYPES.SPS) {
      payload.sps = this.readByType(header, data);
    } else if (header.type === NALU_TYPES.PPS) {
      payload.pps = this.readByType(header, data);
    } else if (header.type === NALU_TYPES.SEI) {
      payload.sei = this.readByType(header, data);
    } else if (
      header.type === NALU_TYPES.CODED_SLICE_IDR ||
      header.type === NALU_TYPES.CODED_SLICE_NON_IDR ||
      header.type === NALU_TYPES.CODED_SLICE_AUR
    ) {
      payload = await this.readSliceHeader(header, data);
    } else if (header.type === NALU_TYPES.CODED_SLICE_SVC_EXTENSION) {
      payload = await this.readSliceHeader(header, data);
    } else {
      payload.naked = this.readNaked(header.type, data);
    }

    return payload;
  }

  async readSliceHeader(header, data) {
    const payload = this.createPayload(header);

    // Need to feed pps and sps which are related to this slice header first,
    // because info from them in used to calculate slice header info.
    const ppsHeader = this.bitstream.findPrecedingHeader(
      NALU_TYPES.PPS,
      header.start,
    );
    if (ppsHeader !== undefined) {
      const ppsData = await this.bitstream.getUnitData(ppsHeader);
      payload.pps = this.readByType(ppsHeader, ppsData);
    }

    const spsHeader = this.bitstream.findPrecedingHeader(
      NALU_TYPES.SPS,
      header.start,
    );
    if (spsHeader !== undefined) {
      const spsData = await this.bitstream.getUnitData(spsHeader);
      payload.sps = this.readByType(spsHeader, spsData);
    }

    payload.sh = this.readByType(header, data);

    return payload;
  }

  readByType(header, data) {
    const methodName = MAP_TYPE_TO_METHOD_NAME[header.type];
    if (methodName === undefined) {
      return this.readNaked(header, data);
    }

    return this.invokeBindingMethod(methodName, data);
  }

  readNaked(header, data) {
    return this.invokeBindingMethod('readNaked', data);
  }

  invokeBindingMethod(methodName, data) {
    const unitData32 = new Int32Array(data);

    const numBytes = unitData32.length * unitData32.BYTES_PER_ELEMENT;
    const ptr = Module._malloc(numBytes);

    const heapBytes = new Uint8Array(Module.HEAPU8.buffer, ptr, numBytes);
    heapBytes.set(new Uint8Array(unitData32.buffer));

    const ret = this.binding[methodName](ptr, unitData32.length);

    Module._free(ptr);

    return ret;
  }

  createPayload(header) {
    return {
      header,
      sps: null,
      pps: null,
      sh: null,
      sei: null,
      naked: '',
    };
  }
}

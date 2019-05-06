import EventEmitter from './EventEmitter';
import H264BitstreamParser from './H264BitstreamParser';

class H264BistreamOffsetStream extends EventEmitter {
  constructor() {
    super();

    // Data which is left from previous append
    this.leftoverData = new Uint8Array(0);

    // Keep track of offset through all added data, so all emitted offsets
    // are aligned
    this.thruOffset = 0;
  }

  appendData(appendedData) {
    const combinedData = this.concatData(this.leftoverData, appendedData);

    let combinedOffset = 0;

    let unitInfo = H264BitstreamParser.findUnit(combinedData, combinedOffset);

    // Not able to find any units in appended data, keep it for later appends
    if (unitInfo.size === 0) {
      this.leftoverData = combinedData;
      return;
    }

    while (unitInfo.size !== 0) {
      // If unit end offset matches combined data length, it should not be
      // emitted because we are not sure that unit actually ends here. Next
      // append might have extra data for same unit, therefore keep it till
      // then.
      if (unitInfo.end === combinedData.length - 1) {
        this.leftoverData = combinedData.slice(unitInfo.start);

        if (combinedOffset !== 0) {
          this.thruOffset += combinedOffset + 1;
        }

        return;
      }

      this.emitOffset(unitInfo);

      combinedOffset = unitInfo.end;

      unitInfo = H264BitstreamParser.findUnit(combinedData, combinedOffset);
    }
  }

  finish() {
    const unitInfo = H264BitstreamParser.findUnit(this.leftoverData);
    if (unitInfo.size !== 0) {
      this.emitOffset(unitInfo);
    }

    this.emit('end');
  }

  emitOffset(unitInfo) {
    const unitInfoWithOffset = {
      ...unitInfo,
      start: unitInfo.start + this.thruOffset,
      end: unitInfo.end + this.thruOffset,
    };

    this.emit('data', unitInfoWithOffset);
  }

  concatData(arr1, arr2) {
    const tmp = new Uint8Array(arr1.length + arr2.length);
    tmp.set(arr1, 0);
    tmp.set(arr2, arr1.length);
    return tmp;
  }
}

export default H264BistreamOffsetStream;

import EventEmitter from './EventEmitter';
import H264BitstreamParser from './H264BitstreamParser';

import arrayUtils from '../utils/arrayUtils';

class H264BistreamOffsetStream extends EventEmitter {
  constructor() {
    super();

    // Data which is left from previous append.
    // When #finish() is called, all leftover data will be emitted as the last
    // data chunk.
    this.leftoverData = new Uint8Array(0);

    // Keep track of offset through all added data, so all emitted offsets
    // are aligned to start of the file.
    this.thruOffset = 0;
  }

  appendData(appendedData) {
    const combinedData = arrayUtils.concatUint8Arrays(
      this.leftoverData,
      appendedData,
    );

    let combinedOffset = 0;

    let unitInfo = H264BitstreamParser.findUnit(combinedData, combinedOffset);

    // Not able to find any units in appended data, keep it for later appends
    if (unitInfo.size === 0) {
      this.leftoverData = combinedData;
      return;
    }

    let prevUnitInfo = null;

    while (unitInfo.size !== 0) {
      // If unit end offset matches combined data length, it should not be
      // emitted because we are not sure that unit actually ends here. Next
      // append might have extra data for same unit, therefore keep it till
      // then.
      if (unitInfo.end === combinedData.length - 1) {
        this.leftoverData = combinedData.slice(unitInfo.start);

        if (combinedOffset !== 0) {
          this.thruOffset += combinedOffset;
        }
        this.thruOffset += unitInfo.start - combinedOffset;

        return;
      }

      this.emitOffset(unitInfo);

      combinedOffset = unitInfo.end;

      prevUnitInfo = unitInfo;

      unitInfo = H264BitstreamParser.findUnit(combinedData, combinedOffset);
    }

    this.leftoverData = combinedData.slice(combinedOffset + 1);
    this.thruOffset += combinedOffset + 1;
  }

  finish() {
    const unitInfo = H264BitstreamParser.findUnit(this.leftoverData);
    if (unitInfo.size !== 0) {
      this.emitOffset(unitInfo);
    }

    this.emit('end');
  }

  emitOffset(unitInfo) {
    // Apply thru-file offset
    const unitInfoWithOffset = {
      ...unitInfo,
      start: unitInfo.start + this.thruOffset,
      end: unitInfo.end + this.thruOffset,
    };

    this.emit('data', unitInfoWithOffset);
  }
}

export default H264BistreamOffsetStream;

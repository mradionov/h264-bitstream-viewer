const START_CODE_SHORT = [0, 0, 1];
const START_CODE_LONG = [0, 0, 0, 1];
const ZEROS_SHORT = [0, 0, 0];

class H264BitstreamParser {
  // Parse H264 bistream according to ISO/IEC 14496 - 10 Annex B,
  // but keep the 3-byte start code
  static findUnit(data, offset = 0) {
    const noResult = { start: -1, end: -1, size: 0 };

    // Cut off leading zeros and other trash
    while (!H264BitstreamParser.isStartCode(data, offset)) {
      offset += 1;

      // In case no start code found in entire data
      if (offset >= data.length) {
        return noResult;
      }
    }

    if (H264BitstreamParser.isStartCodeLong(data, offset)) {
      offset += 1;
    }

    // Include 3-byte start-code in result
    const start = offset;

    // Skip 3-byte start code
    offset += 3;

    // If payload start is in the end of the stream
    if (offset === data.length) {
      return noResult;
    }

    // Move forward until another start code is encountered, preceding it
    while (
      !H264BitstreamParser.isZerosShort(data, offset + 1) &&
      !H264BitstreamParser.isStartCodeShort(data, offset + 1)
    ) {
      offset += 1;

      // Reached end of data while searching for unit ending.
      // Consider unit ends with data.
      if (offset >= data.length - 1) {
        const end = data.length - 1;

        return {
          start,
          end,
          size: end - start + 1,
        };
      }
    }

    const end = offset;

    return {
      start,
      end,
      size: end - start + 1,
    };
  }

  static readUnitHeader(data, offset = 0) {
    const noHeader = {
      forbiddenZeroBit: -1,
      refIdc: -1,
      type: -1,
    };

    if (!H264BitstreamParser.isStartCode(data, offset)) {
      return noHeader;
    }

    const headerOffset = offset + START_CODE_SHORT.length;

    if (data.length - 1 < headerOffset) {
      return noHeader;
    }

    const header = data[headerOffset];
    const forbiddenZeroBit = header >> 7;
    const refIdc = (header >> 5) & 0x3;
    const type = header & 0x1f;

    return {
      forbiddenZeroBit,
      refIdc,
      type,
    };
  }

  static isStartCodeShort(data, offset = 0) {
    return (
      data[offset] === START_CODE_SHORT[0] &&
      data[offset + 1] === START_CODE_SHORT[1] &&
      data[offset + 2] === START_CODE_SHORT[2]
    );
  }

  static isStartCodeLong(data, offset = 0) {
    return (
      data[offset] === START_CODE_LONG[0] &&
      data[offset + 1] === START_CODE_LONG[1] &&
      data[offset + 2] === START_CODE_LONG[2] &&
      data[offset + 3] === START_CODE_LONG[3]
    );
  }

  static isStartCode(data, offset = 0) {
    return (
      H264BitstreamParser.isStartCodeShort(data, offset) ||
      H264BitstreamParser.isStartCodeLong(data, offset)
    );
  }

  static isZerosShort(data, offset = 0) {
    return (
      data[offset] === ZEROS_SHORT[0] &&
      data[offset + 1] === ZEROS_SHORT[1] &&
      data[offset + 2] === ZEROS_SHORT[2]
    );
  }
}

export default H264BitstreamParser;

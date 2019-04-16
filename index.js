const fileInput = document.querySelector('[data-file-input');

fileInput.addEventListener('change', () => {
  const files = fileInput.files;
  const file = files[0];

  const reader = new FileReader();

  reader.addEventListener('load', (ev) => {
    parse(ev.target.result);
  });
  reader.readAsArrayBuffer(file);
});

const unitsContainer = document.querySelector('[data-units-container]');


const NAL_UNIT_TYPES = {
  UNSPECIFIED: 0,
  CODED_SLICE_NON_IDR: 1,
  CODED_SLICE_DATA_PARTITION_A: 2,
  CODED_SLICE_DATA_PARTITION_B: 3,
  CODED_SLICE_DATA_PARTITION_C: 4,
  CODED_SLICE_IDR: 5,
  SEI: 6,
  SPS: 7,
  PPS: 8,
  AUD: 9,
  END_OF_SEQUENCE: 10,
  END_OF_STREAM: 11,
  FILLER: 12,
  SPS_EXT: 13,
  PREFIX_NAL: 14,
  SUBSET_SPS: 15,
  DPS: 16,
  // 17..18 reserved
  CODED_SLICE_AUX: 19,
  CODED_SLICE_SVC_EXTENSION: 20,
  // 20..23 reserved
  // 24..31 unspecified
};

function parse(buffer) {

  const data = new Uint8Array(buffer);

  const units = [];
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

  for (; offset < data.length; offset += 1) {
    if (data[offset] === 0
      && data[offset + 1] === 0
      && data[offset + 2] === 0
      && lastOffset !== null
    ) {
      const unitData = data.subarray(lastOffset + 3, offset);
      units.push(createUnit(unitData));
      lastOffset = null;
    }

    if (data[offset] === 0
      && data[offset + 1] === 0
      && data[offset + 2] === 1
    ) {
      if (lastOffset !== null) {
        const unitData = data.subarray(lastOffset + 3, offset);
        units.push(createUnit(unitData));
      }

      lastOffset = offset;
    }

    if (offset === data.length - 1
      && lastOffset !== null
    ) {
      const unitData = data.subarray(lastOffset + 3, data.length);
      units.push(createUnit(unitData));
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

  console.log(units);

  units.forEach((unit, index) => {
    const row = createRow(index, unit);
    unitsContainer.appendChild(row);
  });
}

function createUnit(data) {
  const header = data[0];
  const forbiddenZeroBit = header >> 7;
  const refIdc = (header >> 5) & 0x3;
  const type = header & 0x1f;

  const unit = {
    data,
    forbiddenZeroBit,
    refIdc,
    type,
  };

  return unit;
}

function readUnitShort(reader, unit) {
  const unitData32 = new Int32Array(unit.data);

  const numBytes = unitData32.length * unitData32.BYTES_PER_ELEMENT;
  const ptr = Module._malloc(numBytes);

  const heapBytes = new Uint8Array(Module.HEAPU8.buffer, ptr, numBytes);
  heapBytes.set(new Uint8Array(unitData32.buffer));

  const unitShort = reader.readShort(ptr, unitData32.length);

  Module._free(ptr);

  return unitShort;
}

function createRow(index, unit) {
  const row = document.createElement('tr');
  row.appendChild(createCell(index));
  row.appendChild(createCell(`<b>${unit.type}</b>`));
  row.appendChild(createCell(getDisplayedType(unit.type)));
  row.appendChild(createCell(unit.refIdc));
  row.appendChild(createCell(unit.forbiddenZeroBit));
  return row;
}

function createCell(text) {
  const cell = document.createElement('td');
  cell.innerHTML = text;
  return cell;
}

function getDisplayedType(type) {
  switch (type) {
    case NAL_UNIT_TYPES.UNSPECIFIED:
      return 'Unspecified';
    case NAL_UNIT_TYPES.CODED_SLICE_NON_IDR:
      return 'Coded slice a of non-IDR picture';
    case NAL_UNIT_TYPES.CODED_SLICE_DATA_PARTITION_A:
      return 'Coded slice data partition A';
    case NAL_UNIT_TYPES.CODED_SLICE_DATA_PARTITION_B:
      return 'Coded slice data partition B';
    case NAL_UNIT_TYPES.CODED_SLICE_DATA_PARTITION_C:
      return 'Coded slice data partition C';
    case NAL_UNIT_TYPES.CODED_SLICE_IDR:
      return 'Coded slice of an IDR picture';
    case NAL_UNIT_TYPES.SEI:
      return 'Supplemental enhancement information (SEI)';
    case NAL_UNIT_TYPES.SPS:
      return 'Sequence parameter set';
    case NAL_UNIT_TYPES.PPS:
      return 'Picture parameter set';
    case NAL_UNIT_TYPES.AUD:
      return 'Access unit delimiter';
    case NAL_UNIT_TYPES.END_OF_SEQUENCE:
      return 'End of sequence';
    case NAL_UNIT_TYPES.END_OF_STREAM:
      return 'End of stream';
    case NAL_UNIT_TYPES.FILLER:
      return 'Filler data';
    case NAL_UNIT_TYPES.SPS_EXT:
      return 'Sequence parameter set extension';
    case NAL_UNIT_TYPES.PREFIX_NAL:
      return 'Prefix NAL unit';
    case NAL_UNIT_TYPES.SUBSET_SPS:
      return 'Subset Sequence parameter set';
    case NAL_UNIT_TYPES.DPS:
      return 'Depth Parameter Set';
    case NAL_UNIT_TYPES.CODED_SLICE_AUX:
      return 'Coded slice of an auxiliary coded picture without partitioning';
    case NAL_UNIT_TYPES.CODED_SLICE_SVC_EXTENSION:
      return 'Coded slice of SVC extension';
    default:
      return 'Unknown';
  }
}

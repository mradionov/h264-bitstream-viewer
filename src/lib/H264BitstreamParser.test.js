import test from 'ava';

import { H264BitstreamParser } from './H264BitstreamParser';

test('findUnit: empty data, no offset', (t) => {
  const data = new Uint8Array(0);

  const result = H264BitstreamParser.findUnit(data);

  t.deepEqual(result, { start: -1, end: -1, size: 0 });
});

test('findUnit: no start-codes', (t) => {
  const data = new Uint8Array([1, 2, 3, 4, 5]);

  const result = H264BitstreamParser.findUnit(data);

  t.deepEqual(result, { start: -1, end: -1, size: 0 });
});

test('findUnit: 3-byte start-code in the end', (t) => {
  const data = new Uint8Array([1, 2, 3, 0, 0, 1]);

  const result = H264BitstreamParser.findUnit(data);

  t.deepEqual(result, { start: -1, end: -1, size: 0 });
});

test('findUnit: 4-byte start-code in the end', (t) => {
  const data = new Uint8Array([1, 2, 3, 0, 0, 0, 1]);

  const result = H264BitstreamParser.findUnit(data);

  t.deepEqual(result, { start: -1, end: -1, size: 0 });
});

test('findUnit: single unit, leading zeros', (t) => {
  const data = new Uint8Array([0, 0, 0, 0, 0, 0, 1, 5, 6]);

  const result = H264BitstreamParser.findUnit(data);

  t.deepEqual(result, { start: 4, end: 8, size: 5 });
});

test('findUnit: single unit, leading trash', (t) => {
  const data = new Uint8Array([1, 2, 3, 4, 0, 0, 1, 5, 6]);

  const result = H264BitstreamParser.findUnit(data);

  t.deepEqual(result, { start: 4, end: 8, size: 5 });
});

test('findUnit: two units, 3-byte start-codes', (t) => {
  const data = new Uint8Array([0, 0, 1, 5, 6, 0, 0, 1, 7, 8, 9]);

  const result1 = H264BitstreamParser.findUnit(data, 0);
  const result2 = H264BitstreamParser.findUnit(data, 4);

  t.deepEqual(result1, { start: 0, end: 4, size: 5 });
  t.deepEqual(result2, { start: 5, end: 10, size: 6 });
});

test('findUnit: two units, second one has only header', (t) => {
  const data = new Uint8Array([0, 0, 1, 5, 6, 0, 0, 1, 5]);

  const result1 = H264BitstreamParser.findUnit(data, 0);
  const result2 = H264BitstreamParser.findUnit(data, 4);

  t.deepEqual(result1, { start: 0, end: 4, size: 5 });
  t.deepEqual(result2, { start: 5, end: 8, size: 4 });
});

test('findUnit: two units, second one with 4-byte start-codes', (t) => {
  const data = new Uint8Array([0, 0, 1, 5, 6, 0, 0, 0, 1, 7, 8, 9]);

  const result1 = H264BitstreamParser.findUnit(data, 0);
  const result2 = H264BitstreamParser.findUnit(data, 4);

  t.deepEqual(result1, { start: 0, end: 4, size: 5 });
  t.deepEqual(result2, { start: 6, end: 11, size: 6 });
});

test('findUnit: two units, all with 4-byte start-codes', (t) => {
  const data = new Uint8Array([0, 0, 0, 1, 5, 6, 0, 0, 0, 1, 7, 8, 9]);

  const result1 = H264BitstreamParser.findUnit(data, 0);
  const result2 = H264BitstreamParser.findUnit(data, 5);

  t.deepEqual(result1, { start: 1, end: 5, size: 5 });
  t.deepEqual(result2, { start: 7, end: 12, size: 6 });
});

test('findUnitWithHeader: no start-codes', (t) => {
  const data = new Uint8Array([1, 2, 3, 4, 5]);

  const result = H264BitstreamParser.findUnitWithHeader(data);

  t.deepEqual(result, {
    start: -1,
    end: -1,
    size: 0,
    forbiddenZeroBit: -1,
    refIdc: -1,
    type: -1,
  });
});

test('findUnitWithHeader: single unit, leading zeros', (t) => {
  const data = new Uint8Array([0, 0, 0, 0, 0, 0, 1, 103, 6]);

  const result = H264BitstreamParser.findUnitWithHeader(data);

  t.deepEqual(result, {
    start: 4,
    end: 8,
    size: 5,
    forbiddenZeroBit: 0,
    refIdc: 3,
    type: 7,
  });
});

test('findUnitWithHeader: single unit, leading trash', (t) => {
  const data = new Uint8Array([1, 2, 3, 4, 0, 0, 1, 6, 7]);

  const result = H264BitstreamParser.findUnitWithHeader(data);

  t.deepEqual(result, {
    start: 4,
    end: 8,
    size: 5,
    forbiddenZeroBit: 0,
    refIdc: 0,
    type: 6,
  });
});

test('readUnitHeader: empty data', (t) => {
  const header = H264BitstreamParser.readUnitHeader(new Uint8Array([]));

  t.deepEqual(header, {
    forbiddenZeroBit: -1,
    refIdc: -1,
    type: -1,
  });
});

test('readUnitHeader: different units', (t) => {
  const header1 = H264BitstreamParser.readUnitHeader(
    new Uint8Array([0, 0, 1, 6]),
  );
  const header2 = H264BitstreamParser.readUnitHeader(
    new Uint8Array([0, 0, 1, 103]),
  );
  const header3 = H264BitstreamParser.readUnitHeader(
    new Uint8Array([0, 0, 1, 104]),
  );
  const header4 = H264BitstreamParser.readUnitHeader(
    new Uint8Array([0, 0, 1, 101]),
  );
  const header5 = H264BitstreamParser.readUnitHeader(
    new Uint8Array([0, 0, 1, 65]),
  );

  t.deepEqual(header1, {
    forbiddenZeroBit: 0,
    refIdc: 0,
    type: 6,
  });
  t.deepEqual(header2, {
    forbiddenZeroBit: 0,
    refIdc: 3,
    type: 7,
  });
  t.deepEqual(header3, {
    forbiddenZeroBit: 0,
    refIdc: 3,
    type: 8,
  });
  t.deepEqual(header4, {
    forbiddenZeroBit: 0,
    refIdc: 3,
    type: 5,
  });
  t.deepEqual(header5, {
    forbiddenZeroBit: 0,
    refIdc: 2,
    type: 1,
  });
});

test('readUnitHeader: offset on start-code', (t) => {
  const header = H264BitstreamParser.readUnitHeader(
    new Uint8Array([1, 2, 3, 0, 0, 1, 6]),
    3,
  );

  t.deepEqual(header, {
    forbiddenZeroBit: 0,
    refIdc: 0,
    type: 6,
  });
});

test('readUnitHeader: offset before start-code', (t) => {
  const header = H264BitstreamParser.readUnitHeader(
    new Uint8Array([1, 2, 3, 0, 0, 1, 6]),
    2,
  );

  t.deepEqual(header, {
    forbiddenZeroBit: -1,
    refIdc: -1,
    type: -1,
  });
});

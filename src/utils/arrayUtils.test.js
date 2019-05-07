import test from 'ava';

import arrayUtils from './arrayUtils';

test('range: empty', (t) => {
  const range = arrayUtils.range();

  t.deepEqual(range, []);
});

test('range: no start', (t) => {
  const range = arrayUtils.range(3);

  t.deepEqual(range, [0, 1, 2]);
});

test('range: start and end', (t) => {
  const range = arrayUtils.range(2, 5);

  t.deepEqual(range, [2, 3, 4]);
});

test('concatUint8Arrays: empty', (t) => {
  const result = arrayUtils.concatUint8Arrays();

  t.deepEqual(result, new Uint8Array([]));
});

test('concatUint8Arrays: one input', (t) => {
  const input1 = new Uint8Array([1, 2, 3]);

  const result = arrayUtils.concatUint8Arrays(input1);

  t.deepEqual(result, input1);
  t.not(result, input1);
});

test('concatUint8Arrays: two inputs', (t) => {
  const input1 = new Uint8Array([1, 2, 3]);
  const input2 = new Uint8Array([4, 5]);

  const result = arrayUtils.concatUint8Arrays(input1, input2);

  t.deepEqual(result, new Uint8Array([1, 2, 3, 4, 5]));
});

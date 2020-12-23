import avaTest from 'ava';
import ninos from 'ninos';

import { FileChunkReader } from './FileChunkReader';

const test = ninos(avaTest);

test('empty file', async (t) => {
  const data = new Uint8Array([]);
  const file = new File([data.buffer], 'test');

  const reader = new FileChunkReader(file);

  const buffer = await reader.readAsArrayBuffer();

  t.deepEqual(new Uint8Array(buffer), data);
});

test('no args full file', async (t) => {
  const data = new Uint8Array([1, 2, 3, 4, 5]);
  const file = new File([data.buffer], 'test');

  const reader = new FileChunkReader(file);

  const buffer = await reader.readAsArrayBuffer();

  t.deepEqual(new Uint8Array(buffer), data);
});

test('read till the end', async (t) => {
  const data = new Uint8Array([1, 2, 3, 4, 5]);
  const file = new File([data.buffer], 'test');

  const reader = new FileChunkReader(file);

  const buffer = await reader.readAsArrayBuffer(1);

  t.deepEqual(new Uint8Array(buffer), new Uint8Array([2, 3, 4, 5]));
});

test('read chunk', async (t) => {
  const data = new Uint8Array([1, 2, 3, 4, 5]);
  const file = new File([data.buffer], 'test');

  const reader = new FileChunkReader(file);

  const buffer = await reader.readAsArrayBuffer(1, 2);

  t.deepEqual(new Uint8Array(buffer), new Uint8Array([2, 3]));
});

test('start exceeds length', async (t) => {
  const data = new Uint8Array([1, 2, 3, 4, 5]);
  const file = new File([data.buffer], 'test');

  const reader = new FileChunkReader(file);

  const buffer = await reader.readAsArrayBuffer(10);

  t.deepEqual(new Uint8Array(buffer), new Uint8Array([]));
});

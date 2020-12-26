import avaTest from 'ava';
import ninos from 'ninos';

import { FileReadStream } from './FileReadStream';

const test = ninos(avaTest);

test.cb('empty file', (t) => {
  const file = new File([], 'test');
  const stream = new FileReadStream(file);

  const chunkListener = t.context.stub();
  const endListener = t.context.stub();

  t.plan(1);

  stream.addEventListener('data', chunkListener);

  stream.addEventListener('end', () => {
    t.is(chunkListener.calls.length, 0);
    t.end();
  });

  stream.start();
});

test.cb('entire file in one chunk', (t) => {
  const data = new Uint8Array([1, 2, 3, 4, 5]);
  const file = new File([data.buffer], 'test');

  const stream = new FileReadStream(file, {
    chunkSize: 10,
  });

  const chunkListener = t.context.stub();
  const endListener = t.context.stub();

  t.plan(2);

  stream.addEventListener('data', chunkListener);

  stream.addEventListener('end', () => {
    t.is(chunkListener.calls.length, 1);
    t.deepEqual(chunkListener.calls[0].arguments[0], data.buffer);
    t.end();
  });

  stream.start();
});

test.cb('entire file in multiple chunks', (t) => {
  const data = new Uint8Array([1, 2, 3, 4, 5]);
  const file = new File([data.buffer], 'test');

  const stream = new FileReadStream(file, {
    chunkSize: 1,
  });

  const chunkListener = t.context.stub();
  const endListener = t.context.stub();

  t.plan(6);

  stream.addEventListener('data', chunkListener);

  stream.addEventListener('end', () => {
    t.is(chunkListener.calls.length, 5);
    t.deepEqual(chunkListener.calls[0].arguments[0], data.buffer.slice(0, 1));
    t.deepEqual(chunkListener.calls[1].arguments[0], data.buffer.slice(1, 2));
    t.deepEqual(chunkListener.calls[2].arguments[0], data.buffer.slice(2, 3));
    t.deepEqual(chunkListener.calls[3].arguments[0], data.buffer.slice(3, 4));
    t.deepEqual(chunkListener.calls[4].arguments[0], data.buffer.slice(4, 5));
    t.end();
  });

  stream.start();
});

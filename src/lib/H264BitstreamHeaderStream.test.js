import avaTest from 'ava';
import ninos from 'ninos';

import { H264BitstreamHeaderStream } from './H264BitstreamHeaderStream';

const test = ninos(avaTest);

test.cb('clean chunks, 3-byte start-code', (t) => {
  const stream = new H264BitstreamHeaderStream();

  const chunkListener = t.context.stub();

  t.plan(3);

  stream.addEventListener('data', chunkListener);
  stream.addEventListener('end', () => {
    t.is(chunkListener.calls.length, 2);
    t.deepEqual(chunkListener.calls[0].arguments[0], {
      start: 0,
      end: 4,
      size: 5,
      forbiddenZeroBit: 0,
      refIdc: 3,
      type: 7,
    });
    t.deepEqual(chunkListener.calls[1].arguments[0], {
      start: 5,
      end: 10,
      size: 6,
      forbiddenZeroBit: 0,
      refIdc: 3,
      type: 8,
    });
    t.end();
  });

  stream.appendData(new Uint8Array([0, 0, 1, 103, 4]));
  stream.appendData(new Uint8Array([0, 0, 1, 104, 5, 6]));
  stream.finish();
});

test.cb('clean chunks, 4-byte start-code', (t) => {
  const stream = new H264BitstreamHeaderStream();

  const chunkListener = t.context.stub();

  t.plan(3);

  stream.addEventListener('data', chunkListener);
  stream.addEventListener('end', () => {
    t.is(chunkListener.calls.length, 2);
    t.deepEqual(chunkListener.calls[0].arguments[0], {
      start: 1,
      end: 5,
      size: 5,
      forbiddenZeroBit: 0,
      refIdc: 3,
      type: 7,
    });
    t.deepEqual(chunkListener.calls[1].arguments[0], {
      start: 7,
      end: 12,
      size: 6,
      forbiddenZeroBit: 0,
      refIdc: 3,
      type: 8,
    });
    t.end();
  });

  stream.appendData(new Uint8Array([0, 0, 0, 1, 103, 4]));
  stream.appendData(new Uint8Array([0, 0, 0, 1, 104, 5, 6]));
  stream.finish();
});

test.cb('second chunk zeros in first chunk', (t) => {
  const stream = new H264BitstreamHeaderStream();

  const chunkListener = t.context.stub();

  t.plan(3);

  stream.addEventListener('data', chunkListener);
  stream.addEventListener('end', () => {
    t.is(chunkListener.calls.length, 2);
    t.deepEqual(chunkListener.calls[0].arguments[0], {
      start: 1,
      end: 5,
      size: 5,
      forbiddenZeroBit: 0,
      refIdc: 3,
      type: 7,
    });
    t.deepEqual(chunkListener.calls[1].arguments[0], {
      start: 7,
      end: 12,
      size: 6,
      forbiddenZeroBit: 0,
      refIdc: 3,
      type: 8,
    });
    t.end();
  });

  stream.appendData(new Uint8Array([0, 0, 0, 1, 103, 4, 0, 0, 0]));
  stream.appendData(new Uint8Array([1, 104, 5, 6]));
  stream.finish();
});

test.cb('combine chunks, 3-byte start-code', (t) => {
  const stream = new H264BitstreamHeaderStream();

  const chunkListener = t.context.stub();

  t.plan(6);

  stream.addEventListener('data', chunkListener);
  stream.addEventListener('end', () => {
    t.is(chunkListener.calls.length, 5);
    t.deepEqual(chunkListener.calls[0].arguments[0], {
      start: 0,
      end: 5,
      size: 6,
      forbiddenZeroBit: 0,
      refIdc: 3,
      type: 7,
    });
    t.deepEqual(chunkListener.calls[1].arguments[0], {
      start: 6,
      end: 14,
      size: 9,
      forbiddenZeroBit: 0,
      refIdc: 3,
      type: 8,
    });
    t.deepEqual(chunkListener.calls[2].arguments[0], {
      start: 15,
      end: 19,
      size: 5,
      forbiddenZeroBit: 0,
      refIdc: 3,
      type: 5,
    });
    t.deepEqual(chunkListener.calls[3].arguments[0], {
      start: 20,
      end: 27,
      size: 8,
      forbiddenZeroBit: 0,
      refIdc: 2,
      type: 1,
    });
    t.deepEqual(chunkListener.calls[4].arguments[0], {
      start: 28,
      end: 31,
      size: 4,
      forbiddenZeroBit: 0,
      refIdc: 0,
      type: 6,
    });
    t.end();
  });

  stream.appendData(new Uint8Array([0, 0, 1, 103, 3, 4, 0, 0, 1, 104]));
  stream.appendData(new Uint8Array([6, 7, 8, 9, 10, 0]));
  stream.appendData(new Uint8Array([0, 1, 101, 12]));
  stream.appendData(new Uint8Array([0, 0, 1, 65]));
  stream.appendData(new Uint8Array([14, 15, 16, 17]));
  stream.appendData(new Uint8Array([0, 0, 1, 6]));
  stream.finish();
});

test.cb('combine chunks, 4-byte start-code', (t) => {
  const stream = new H264BitstreamHeaderStream();

  const chunkListener = t.context.stub();

  t.plan(7);

  stream.addEventListener('data', chunkListener);
  stream.addEventListener('end', () => {
    t.is(chunkListener.calls.length, 6);
    t.deepEqual(chunkListener.calls[0].arguments[0], {
      start: 1,
      end: 6,
      size: 6,
      forbiddenZeroBit: 0,
      refIdc: 3,
      type: 7,
    });
    t.deepEqual(chunkListener.calls[1].arguments[0], {
      start: 8,
      end: 16,
      size: 9,
      forbiddenZeroBit: 0,
      refIdc: 3,
      type: 8,
    });
    t.deepEqual(chunkListener.calls[2].arguments[0], {
      start: 18,
      end: 22,
      size: 5,
      forbiddenZeroBit: 0,
      refIdc: 3,
      type: 5,
    });
    t.deepEqual(chunkListener.calls[3].arguments[0], {
      start: 24,
      end: 31,
      size: 8,
      forbiddenZeroBit: 0,
      refIdc: 2,
      type: 1,
    });
    t.deepEqual(chunkListener.calls[4].arguments[0], {
      start: 33,
      end: 36,
      size: 4,
      forbiddenZeroBit: 0,
      refIdc: 0,
      type: 6,
    });
    t.deepEqual(chunkListener.calls[5].arguments[0], {
      start: 38,
      end: 43,
      size: 6,
      forbiddenZeroBit: 0,
      refIdc: 3,
      type: 7,
    });
    t.end();
  });

  stream.appendData(new Uint8Array([0, 0, 0, 1, 103, 3, 4, 0, 0, 0, 1, 104]));
  stream.appendData(new Uint8Array([6, 7, 8, 9, 10, 0, 0]));
  stream.appendData(new Uint8Array([0, 1, 101, 12]));
  stream.appendData(new Uint8Array([0, 0, 0, 1, 65]));
  stream.appendData(new Uint8Array([14, 15, 16, 17, 0]));
  stream.appendData(new Uint8Array([0, 0, 1, 6, 0, 0, 0]));
  stream.appendData(new Uint8Array([1, 103, 20, 21]));
  stream.finish();
});

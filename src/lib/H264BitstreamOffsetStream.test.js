import avaTest from 'ava';
import ninos from 'ninos';

import H264BitstreamOffsetStream from './H264BitstreamOffsetStream';

const test = ninos(avaTest);

test.cb('clean chunks', (t) => {
  const stream = new H264BitstreamOffsetStream();

  const chunkListener = t.context.stub();

  t.plan(3);

  stream.addEventListener('data', chunkListener);
  stream.addEventListener('end', () => {
    t.is(chunkListener.calls.length, 2);
    t.deepEqual(chunkListener.calls[0].arguments[0], {
      start: 0,
      end: 4,
      size: 5,
    });
    t.deepEqual(chunkListener.calls[1].arguments[0], {
      start: 5,
      end: 10,
      size: 6,
    });
    t.end();
  });

  stream.appendData(new Uint8Array([0, 0, 1, 3, 4]));
  stream.appendData(new Uint8Array([0, 0, 1, 4, 5, 6]));
  stream.finish();
});

test.cb('combine chunks', (t) => {
  const stream = new H264BitstreamOffsetStream();

  const chunkListener = t.context.stub();

  t.plan(6);

  stream.addEventListener('data', chunkListener);
  stream.addEventListener('end', () => {
    t.is(chunkListener.calls.length, 5);
    t.deepEqual(chunkListener.calls[0].arguments[0], {
      start: 0,
      end: 5,
      size: 6,
    });
    t.deepEqual(chunkListener.calls[1].arguments[0], {
      start: 6,
      end: 14,
      size: 9,
    });
    t.deepEqual(chunkListener.calls[2].arguments[0], {
      start: 15,
      end: 19,
      size: 5,
    });
    t.deepEqual(chunkListener.calls[3].arguments[0], {
      start: 20,
      end: 27,
      size: 8,
    });
    t.deepEqual(chunkListener.calls[4].arguments[0], {
      start: 28,
      end: 31,
      size: 4,
    });
    t.end();
  });

  stream.appendData(new Uint8Array([0, 0, 1, 2, 3, 4, 0, 0, 1, 5]));
  stream.appendData(new Uint8Array([6, 7, 8, 9, 10, 0]));
  stream.appendData(new Uint8Array([0, 1, 11, 12]));
  stream.appendData(new Uint8Array([0, 0, 1, 13]));
  stream.appendData(new Uint8Array([14, 15, 16, 17]));
  stream.appendData(new Uint8Array([0, 0, 1, 18]));
  stream.finish();
});

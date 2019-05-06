import avaTest from 'ava';
import ninos from 'ninos';

import EventEmitter from './EventEmitter';

const test = ninos(avaTest);

test('multiple events', (t) => {
  const emitter = new EventEmitter();

  const listener1 = t.context.stub();
  const listener2 = t.context.stub();

  emitter.addEventListener('foo', listener1);
  emitter.addEventListener('bar', listener2);

  emitter.emit('foo', 1, '2');
  emitter.emit('bar', 3, '4');

  t.is(listener1.calls.length, 1);
  t.is(listener2.calls.length, 1);

  t.deepEqual(listener1.calls[0].arguments, [1, '2']);
  t.deepEqual(listener2.calls[0].arguments, [3, '4']);
});

test('multiple listeners', (t) => {
  const emitter = new EventEmitter();

  const listener1 = t.context.stub();
  const listener2 = t.context.stub();

  emitter.addEventListener('foo', listener1);
  emitter.addEventListener('foo', listener2);

  emitter.emit('foo', 1, '2');

  t.is(listener1.calls.length, 1);
  t.is(listener2.calls.length, 1);

  t.deepEqual(listener1.calls[0].arguments, [1, '2']);
  t.deepEqual(listener2.calls[0].arguments, [1, '2']);
});

test('multiple listeners, remove particular', (t) => {
  const emitter = new EventEmitter();

  const listener1 = t.context.stub();
  const listener2 = t.context.stub();

  emitter.addEventListener('foo', listener1);
  emitter.addEventListener('foo', listener2);

  emitter.removeEventListener('foo', listener1);

  emitter.emit('foo', 1, '2');

  t.is(listener1.calls.length, 0);
  t.is(listener2.calls.length, 1);

  t.deepEqual(listener2.calls[0].arguments, [1, '2']);
});

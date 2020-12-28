import { EventEmitter } from './EventEmitter';
import { FileChunkReader } from './FileChunkReader';

const DEFAULT_CHUNK_SIZE = 2000000; // 2 MB
const STATE = {
  IDLE: 0,
  READING: 1,
  DESTROYED: 2,
};

// Reads entire file in chunks of "chunkSize" size and emits "data" event
// for each chunk. Emits "end" event when done reading.
export class FileReadStream extends EventEmitter {
  constructor(file, options = {}) {
    super();

    const { chunkSize = DEFAULT_CHUNK_SIZE } = options;

    this.state = STATE.IDLE;
    this.file = file;
    this.chunkSize = chunkSize;
    this.offset = 0;
    this.chunkReader = new FileChunkReader(this.file);
  }

  start() {
    if (this.state !== STATE.IDLE) {
      return;
    }

    this.state = STATE.READING;
    this.readNextChunk();
  }

  destroy() {
    if (this.state === STATE.DESTROYED) {
      return;
    }

    this.state = STATE.DESTROYED;
    this.emit('destroyed');
    this.removeAllEventListeners();
  }

  async readNextChunk() {
    if (this.state === STATE.DESTROYED) {
      return;
    }

    const buffer = await this.chunkReader.readAsArrayBuffer(
      this.offset,
      this.chunkSize,
    );

    if (buffer.byteLength === 0) {
      this.emit('end');
      return;
    }

    this.offset += buffer.byteLength;

    this.emit('data', buffer);

    // Don't lock thread with endless processing, work as soon as it is ready
    window.requestIdleCallback(() => {
      this.readNextChunk();
    });
  }
}

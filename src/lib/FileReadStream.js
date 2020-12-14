import EventEmitter from './EventEmitter';
import FileChunkReader from './FileChunkReader';

const DEFAULT_CHUNK_SIZE = 2000000; // 2 MB

class FileReadStream extends EventEmitter {
  constructor(file, options = {}) {
    super();

    const { chunkSize = DEFAULT_CHUNK_SIZE } = options;

    this.file = file;
    this.chunkSize = chunkSize;
    this.offset = 0;
    this.chunkReader = new FileChunkReader(this.file);
  }

  start() {
    this.readNextChunk();
  }

  async readNextChunk() {
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

export default FileReadStream;

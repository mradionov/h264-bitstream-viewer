import { EventEmitter } from './EventEmitter';
import { FileChunkReader } from './FileChunkReader';
import { FileReadStream } from './FileReadStream';
import { H264BitstreamHeaderStream } from './H264BitstreamHeaderStream';

export class H264BitstreamFile extends EventEmitter {
  constructor(file) {
    super();

    this.file = file;
    this.headers = [];
    this.lastLoadedOffset = 0;
  }

  load() {
    this.emit('start');

    const headers = [];

    const offsetStream = new H264BitstreamHeaderStream();

    offsetStream.addEventListener('data', async (header) => {
      this.lastLoadedOffset = header.end;
      headers.push(header);
      this.emitProgress();
    });

    offsetStream.addEventListener('end', async () => {
      this.headers = headers;
      this.emitProgress();
      this.emit('end');
    });

    const fileStream = new FileReadStream(this.file);

    fileStream.addEventListener('data', (chunkBuffer) => {
      offsetStream.appendData(new Uint8Array(chunkBuffer));
    });

    fileStream.addEventListener('end', () => {
      offsetStream.finish();
    });

    fileStream.start();
  }

  destroy() {
    this.file = null;
    this.headers = [];
  }

  emitProgress() {
    this.emit('progress', this.getProgress());
  }

  findPrecedingHeader(type, maxStartOffset = 0) {
    let foundHeader = undefined;

    let currentIndex = 0;
    let currentHeader = this.headers[currentIndex];

    while (currentHeader) {
      if (currentHeader.start >= maxStartOffset) {
        return foundHeader;
      }

      if (currentHeader.type === type) {
        foundHeader = currentHeader;
      }

      currentIndex++;
      currentHeader = this.headers[currentIndex];
    }

    return foundHeader;
  }

  getProgress() {
    return (this.lastLoadedOffset / this.file.size) * 100;
  }

  getTotalHeaders() {
    return this.headers.length;
  }

  async getUnitData(header) {
    const chunkReader = new FileChunkReader(this.file);
    const buffer = await chunkReader.readAsArrayBuffer(
      header.start,
      header.size,
    );
    const data = new Uint8Array(buffer);

    const dataNoStartCode = data.slice(3);

    return dataNoStartCode;
  }
}

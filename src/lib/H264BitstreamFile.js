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

    this.fileStream = new FileReadStream(this.file);
    this.fileStream.addEventListener('data', this.handleFileData.bind(this));
    this.fileStream.addEventListener('end', this.handleFileEnd.bind(this));

    this.offsetStream = new H264BitstreamHeaderStream();
    this.offsetStream.addEventListener(
      'data',
      this.handleOffsetData.bind(this),
    );
    this.offsetStream.addEventListener('end', this.handleOffsetEnd.bind(this));
  }

  load() {
    this.fileStream.start();
    this.emit('start');
  }

  handleFileData(chunkBuffer) {
    this.offsetStream.appendData(new Uint8Array(chunkBuffer));
  }

  handleFileEnd() {
    this.offsetStream.finish();
  }

  handleOffsetData(header) {
    this.lastLoadedOffset = header.end;
    this.headers.push(header);
    this.emitProgress();
  }

  handleOffsetEnd() {
    this.emitProgress();
    this.emit('end');
  }

  destroy() {
    this.file = null;
    this.headers = [];

    this.fileStream.destroy();
    this.offsetStream.destroy();

    this.removeAllEventListeners();
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

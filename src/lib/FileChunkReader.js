class FileChunkReader {
  constructor(file) {
    this.file = file;
  }

  async readAsArrayBuffer(start = 0, end = undefined) {
    if (end === undefined) {
      end = Math.max(0, this.file.size);
    }

    const blob = this.file.slice(start, end);
    if (blob.size === 0) {
      return new ArrayBuffer(0);
    }

    const fileReader = new FileReader();

    const promise = new Promise((resolve, reject) => {
      fileReader.addEventListener('load', (ev) => {
        const buffer = ev.target.result;
        resolve(buffer);
      });

      fileReader.addEventListener('error', (err) => {
        reject(err);
      });
    });

    fileReader.readAsArrayBuffer(blob);

    return promise;
  }
}

export default FileChunkReader;

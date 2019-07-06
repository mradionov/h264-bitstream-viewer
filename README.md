# h264-bitstream-viewer

## Prerequisites

- Docker - for building WASM version of [h264bitstream](h264bitstream)
- Node.js, npm - for building Frontend Application

## Dependencies

Fetches [h264bitstream](h264bitstream) as a submodule:

```bash
$ git submodule update --init --recursive
```

## Build

Build WASM:

```bash
$ ./build.sh
```

Build Frontend Application:

```bash
$ npm run build
```

## Develop

Open serve `dist/` folder using any web-server and open `index.html` in browser.

[h264bitstream]: https://github.com/aizvorski/h264bitstream

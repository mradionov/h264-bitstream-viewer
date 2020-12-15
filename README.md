# h264-bitstream-viewer [![Build status](https://travis-ci.com/mradionov/h264-bitstream-viewer.svg?branch=master)](https://travis-ci.com/mradionov/h264-bitstream-viewer)

> Web UI on top of [h264bitstream][h264bitstream], inspired by [H264Naked][h264naked], to display information about NAL units of H264 bitstream.

[Web application available here][web]

## Prerequisites

- Docker - for building WASM version of [h264bitstream][h264bitstream]
- Node.js, npm - for building Frontend Application

## Dependencies

Fetch [h264bitstream][h264bitstream] as a submodule:

```bash
git submodule update --init --recursive
```

Fetch NPM dependencies:

```bash
npm install
```

## Build

Build WASM:

```bash
./build.sh
```

Build Frontend Application:

```bash
npm run build
npm run build:watch
```

## Develop

Serve `dist/` folder using any web-server and open `index.html` in browser.

[h264bitstream]: https://github.com/aizvorski/h264bitstream

## Test

```bash
npm run test
npm run test:watch
```

[h264bitstream]: https://github.com/aizvorski/h264bitstream
[h264naked]: https://github.com/shi-yan/H264Naked
[web]: https://mradionov.github.io/h264-bitstream-viewer/

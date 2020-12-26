# Development

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

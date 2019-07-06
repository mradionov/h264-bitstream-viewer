mkdir -p dist
docker build -t mradionov/h264bitstream-wasm .
docker create -ti --name h264bitstream-wasm-container mradionov/h264bitstream-wasm
docker cp h264bitstream-wasm-container:/build/dist/ .
docker rm -fv h264bitstream-wasm-container

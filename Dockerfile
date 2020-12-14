FROM trzeci/emscripten:sdk-tag-1.38.30-64bit

RUN apt-get update && apt-get install -y autoconf libtool

COPY ./h264bitstream/ /build/h264bitstream/
COPY ./src/wrapper/ /build/src/wrapper/
COPY ./Makefile /build/Makefile

WORKDIR /build

RUN make

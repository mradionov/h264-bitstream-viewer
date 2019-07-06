FROM trzeci/emscripten

RUN apt-get update && apt-get install -y autoconf libtool

COPY ./h264bitstream/ /build/h264bitstream/
COPY ./src/h264bitstream-wrapper.cpp /build/src/h264bitstream-wrapper.cpp
COPY ./Makefile /build/Makefile

WORKDIR /build

RUN make

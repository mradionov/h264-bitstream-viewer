FROM trzeci/emscripten

RUN apt-get update && apt-get install -y autoconf libtool

COPY ./h264bitstream/ /build/h264bitstream/

# Comment the line so that it won't build binaries. We only need shared library.
# Otherwise, Emscripten won't be able to complete the build, as the target is
# not a JS target, so it will ignore shared library. But binaries use shared
# libraries, therefore the whole build will fail.
RUN sed -i 's/bin_PROGRAMS/#bin_PROGRAMS/' /build/h264bitstream/Makefile.am

COPY ./src/binding/ /build/src/binding/
COPY ./Makefile /build/Makefile

WORKDIR /build

RUN make

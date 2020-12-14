#include <emscripten.h>
#include <emscripten/bind.h>

#include "reader.h"

extern "C" {

EMSCRIPTEN_BINDINGS(H264Bitstream) {

  emscripten::class_<Reader>("Reader")
    .constructor<>()
    .function("read", &Reader::read)
    ;

};

}

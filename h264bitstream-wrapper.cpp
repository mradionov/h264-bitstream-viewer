#include <iostream>

#include <emscripten.h>
#include <emscripten/bind.h>

#include <h264_stream.h>

using namespace emscripten;

extern "C" {

struct UnitShort {
  int forbidden_zero_bit;
  int nal_ref_idc;
  int nal_unit_type;
};

struct Reader {
  Reader() {}

  UnitShort readShort(uintptr_t input, int size) {
    const int32_t* data = reinterpret_cast<int32_t*>(input);

    uint8_t* buf = new uint8_t[size];

    for (int i = 0; i < size; i += 1) {
      buf[i] = (uint8_t) (data[i] & 0xff);
    }

    h264_stream_t* h = h264_new();

    int ret = read_nal_unit(h, buf, size);

    UnitShort us = UnitShort();
    us.forbidden_zero_bit = h->nal->forbidden_zero_bit;
    us.nal_ref_idc = h->nal->nal_ref_idc;
    us.nal_unit_type = h->nal->nal_unit_type;

    h264_free(h);

    delete [] buf;

    return us;
  }
};


EMSCRIPTEN_BINDINGS(H264Bitstream) {
  value_object<UnitShort>("UnitShort")
    .field("forbidden_zero_bit", &UnitShort::forbidden_zero_bit)
    .field("nal_ref_idc", &UnitShort::nal_ref_idc)
    .field("nal_unit_type", &UnitShort::nal_unit_type)
    ;

  class_<Reader>("Reader")
    .constructor<>()
    .function("readShort", &Reader::readShort)
    ;

}

}

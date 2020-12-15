#ifndef READER_H
#define READER_H

#include <string>

#include <h264_stream.h>

#include "payloads/payload-pps.h"

class Reader {
public:
  Reader() {}
  std::string readNaked(uintptr_t input, int size);
  PayloadPPS readPPS(uintptr_t input, int size);
};

#endif


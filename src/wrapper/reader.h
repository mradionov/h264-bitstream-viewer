#ifndef READER_H
#define READER_H

#include <string>

#include <h264_stream.h>

class Reader {
public:
  Reader() {}
  std::string readNaked(uintptr_t input, int size);
  pps_t readPPS(uintptr_t input, int size);
};

#endif


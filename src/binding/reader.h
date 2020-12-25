#ifndef READER_H
#define READER_H

#include <string>

#include <h264_stream.h>

class Reader {
public:
  Reader();
  ~Reader();
  std::string readNaked(uintptr_t input, int size);
  pps_t readPPS(uintptr_t input, int size);
  sps_t readSPS(uintptr_t input, int size);
  slice_header_t readSliceHeader(uintptr_t input, int size);
private:
  h264_stream_t* m_h264_stream;
};

#endif

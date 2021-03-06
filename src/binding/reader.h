#ifndef READER_H
#define READER_H

#include <string>
#include <vector>

#include <h264_stream.h>

#include "types.h"

class Reader {
public:
  Reader();
  ~Reader();
  pps_t readPPS(uintptr_t input, int size);
  sps_t readSPS(uintptr_t input, int size);
  aud_t readAUD(uintptr_t input, int size);
  slice_header_t readSliceHeader(uintptr_t input, int size);
  std::vector<bind_sei_t> readSEI(uintptr_t input, int size);
  bind_sps_subset_t readSPSSubset(uintptr_t input, int size);
  prefix_nal_svc_t readPrefixNAL(uintptr_t input, int size);
  nal_svc_ext_t readNALHeaderSVCEXT(uintptr_t input, int size);
private:
  h264_stream_t* m_h264_stream;
};

#endif


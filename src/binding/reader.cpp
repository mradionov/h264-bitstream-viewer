#include <iostream>
#include <sstream>

#include <h264_stream.h>

#include "h264naked-print.h"
#include "reader.h"

Reader::Reader() {
  m_h264_stream = h264_new();
}

Reader::~Reader() {
  h264_free(m_h264_stream);
}

std::string Reader::readNaked(uintptr_t input, int size) {
  const int32_t* data = reinterpret_cast<int32_t*>(input);

  uint8_t* buf = new uint8_t[size];

  for (int i = 0; i < size; i += 1) {
    buf[i] = (uint8_t) (data[i] & 0xff);
  }

  int ret = read_nal_unit(m_h264_stream, buf, size);

  std::stringstream ss;

  print_nal(ss, m_h264_stream, m_h264_stream->nal);

  delete [] buf;

  return ss.str();
}

pps_t Reader::readPPS(uintptr_t input, int size) {
  const int32_t* data = reinterpret_cast<int32_t*>(input);

  uint8_t* buf = new uint8_t[size];

  for (int i = 0; i < size; i += 1) {
    buf[i] = (uint8_t) (data[i] & 0xff);
  }

  int ret = read_nal_unit(m_h264_stream, buf, size);

  pps_t pps = *(m_h264_stream->pps);

  delete [] buf;

  return pps;
}

sps_t Reader::readSPS(uintptr_t input, int size) {
  const int32_t* data = reinterpret_cast<int32_t*>(input);

  uint8_t* buf = new uint8_t[size];

  for (int i = 0; i < size; i += 1) {
    buf[i] = (uint8_t) (data[i] & 0xff);
  }

  int ret = read_nal_unit(m_h264_stream, buf, size);

  sps_t sps = *(m_h264_stream->sps);

  delete [] buf;

  return sps;
}

slice_header_t Reader::readCodedSliceNonIDR(uintptr_t input, int size) {
  const int32_t* data = reinterpret_cast<int32_t*>(input);

  uint8_t* buf = new uint8_t[size];

  for (int i = 0; i < size; i += 1) {
    buf[i] = (uint8_t) (data[i] & 0xff);
  }

  int ret = read_nal_unit(m_h264_stream, buf, size);

  slice_header_t sh = *(m_h264_stream->sh);

  delete [] buf;

  return sh;
}

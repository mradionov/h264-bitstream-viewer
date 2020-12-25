#include <iostream>
#include <sstream>

#include <h264_stream.h>

#include "h264naked-print.h"
#include "reader.h"
#include "types.h"

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

slice_header_t Reader::readSliceHeader(uintptr_t input, int size) {
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

std::vector<vec_sei_t> Reader::readSEI(uintptr_t input, int size) {
  const int32_t* data = reinterpret_cast<int32_t*>(input);

  uint8_t* buf = new uint8_t[size];

  for (int i = 0; i < size; i += 1) {
    buf[i] = (uint8_t) (data[i] & 0xff);
  }

  int ret = read_nal_unit(m_h264_stream, buf, size);

  std::vector<vec_sei_t> result(m_h264_stream->num_seis);

  for (int i = 0; i < m_h264_stream->num_seis; i++) {
    sei_t* s = m_h264_stream->seis[i];

    result[i].payloadType = s->payloadType;
    result[i].payloadSize = s->payloadSize;
    result[i].data = std::vector<uint8_t>(s->data, s->data + s->payloadSize);
  }

  return result;
}

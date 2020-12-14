#include <sstream>

#include <h264_stream.h>

#include "h264naked-print.h"
#include "reader.h"

std::string Reader::read(uintptr_t input, int size) {
  const int32_t* data = reinterpret_cast<int32_t*>(input);

  uint8_t* buf = new uint8_t[size];

  for (int i = 0; i < size; i += 1) {
    buf[i] = (uint8_t) (data[i] & 0xff);
  }

  h264_stream_t* h = h264_new();

  int ret = read_nal_unit(h, buf, size);

  // cout << "ret = " << ret << endl;

  std::stringstream ss;

  print_nal(ss, h, h->nal);

  // cout << ss.str() << endl;

  h264_free(h);

  delete [] buf;

  return ss.str();
}

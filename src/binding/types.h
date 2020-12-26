#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <vector>

// Alternative to sei_t to use vector instead of array.
struct bind_sei_t {
  int payloadType;
  int payloadSize;
  std::vector<uint8_t> data;
};

struct bind_sps_subset_t {
  sps_t sps;
  sps_svc_ext_t sps_svc_ext;
  bool additional_extension2_flag;
};

#endif

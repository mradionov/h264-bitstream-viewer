#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <vector>

// Alternative to sei_t to use vector instead of array.
struct vec_sei_t {
  int payloadType;
  int payloadSize;
  std::vector<uint8_t> data;
};

#endif

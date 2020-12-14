#ifndef READER_H
#define READER_H

#include <string>

class Reader {
public:
  Reader() {}
  std::string read(uintptr_t input, int size);
};

#endif


#ifndef BINARIES_H
#define BINARIES_H

#include <cstdint>
#include <fstream>

namespace utils {
  namespace binaries {
    void writeLE(std::ofstream& out, uint16_t value);
    void writeLE(std::ofstream& out, uint32_t value);
  }
}

#endif
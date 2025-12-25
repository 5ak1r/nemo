#ifndef BINARIES_H
#define BINARIES_H

#include <cstdint>
#include <fstream>

namespace utils {
namespace binary {
  
void WriteLE(std::ofstream& out, uint16_t value);
void WriteLE(std::ofstream& out, uint32_t value);

}
}

#endif
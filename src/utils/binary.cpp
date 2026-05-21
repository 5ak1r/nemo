#include "binary.hpp"

namespace utils {
namespace binary {

uint16_t ReadLE16(std::ifstream& in) {
  unsigned char bytes[2];
  in.read(reinterpret_cast<char*>(bytes), 2);

  uint16_t result =
    (uint16_t)bytes[0] |
    (uint16_t)bytes[1] << 8;

  return result;
}

uint32_t ReadLE32(std::ifstream& in) {
  unsigned char bytes[4];
  in.read(reinterpret_cast<char*>(bytes), 4);

  uint32_t result =
    (uint32_t)bytes[0] |
    (uint32_t)bytes[1] << 8 |
    (uint32_t)bytes[2] << 16 |
    (uint32_t)bytes[3] << 24;

  return result;
}

void WriteLE16(std::ofstream& out, uint16_t value) {
  unsigned char bytes[2];

  bytes[0] = value & 0xFF;
  bytes[1] = (value >> 8) & 0xFF;

  out.write(reinterpret_cast<const char*>(bytes), 2);
}

void WriteLE32(std::ofstream& out, uint32_t value) {
  unsigned char bytes[4];

  bytes[0] = value & 0xFF;
  bytes[1] = (value >> 8) & 0xFF;
  bytes[2] = (value >> 16) & 0xFF;
  bytes[3] = (value >> 24) & 0xFF;

  out.write(reinterpret_cast<const char*>(bytes), 4);
}

} // namespace binary
} // namespace utils
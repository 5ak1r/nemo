#include "binary.hpp"

namespace utils {
  namespace binary {
    void writeLE(std::ofstream& out, uint16_t value) {
      char bytes[2];

      bytes[0] = value & 0xFF;
      bytes[1] = (value >> 8) & 0xFF;

      out.write(bytes, 2);
    }
    
    void writeLE(std::ofstream& out, uint32_t value) {
      char bytes[4];

      bytes[0] = value & 0xFF;
      bytes[1] = (value >> 8) & 0xFF;
      bytes[2] = (value >> 16) & 0xFF;
      bytes[3] = (value >> 24) & 0xFF;

      out.write(bytes, 4);
    }
  }
}
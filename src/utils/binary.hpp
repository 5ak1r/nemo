#ifndef BINARY_H
#define BINARY_H

#include <cstdint>
#include <fstream>

namespace utils {
namespace binary {

uint16_t ReadLE16(std::ifstream& in);
uint32_t ReadLE32(std::ifstream& in);

void WriteLE16(std::ofstream& out, uint16_t value);
void WriteLE32(std::ofstream& out, uint32_t value);

} // namespace binary
} // namespace utils

#endif // BINARY_H
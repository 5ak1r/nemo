#ifndef BINARY_H
#define BINARY_H

#include <cstdint>
#include <fstream>

namespace utils {
namespace binary {

void WriteLE(std::ofstream& out, uint16_t value);
void WriteLE(std::ofstream& out, uint32_t value);

} // namespace binary
} // namespace utils

#endif // BINARY_H
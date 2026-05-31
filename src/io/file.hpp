#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace io {
namespace file {

bool Open(std::ifstream& file, const std::string& name);
std::string ReadToString(const std::string& name);

} // namespace file
} // namespace io

#endif // FILE_H
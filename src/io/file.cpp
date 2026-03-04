#include "file.hpp"
#include <stdexcept>

namespace io {
namespace file {

bool Open(std::ifstream& file, const std::string& name) {
  file.open(name, std::ios::in);

  if (!file.is_open()) {
    throw std::runtime_error("failed to open file");
    return false;
  }

  return true;
}

std::string ReadToString(const std::string& name) {
  std::ifstream file;

  if(!Open(file, name))
    throw std::runtime_error("failed to open file");

  std::stringstream ss;
  ss << file.rdbuf();

  std::string fileContent = ss.str();

  return fileContent;
}

} // namespace file
} // namespace io
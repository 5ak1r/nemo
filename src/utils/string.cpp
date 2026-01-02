#include "string.hpp"

namespace utils {
namespace string {

std::vector<std::string> Split(const std::string& line, const std::string& delimiter) {
  std::vector<std::string> tokens;
  int last = 0;
  int next = 0;

  while ((next = line.find(delimiter, last)) != std::string::npos) {
    tokens.push_back(line.substr(last, next - last));
    last = next + 1;
  }
  tokens.push_back(line.substr(last));

  return tokens;
}

}
}
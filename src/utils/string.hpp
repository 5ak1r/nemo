#ifndef STRING_H
#define STRING_H

#include <string>
#include <vector>

namespace utils {
namespace string {

std::vector<std::string> Split(const std::string& line, const std::string& delimiter = " ");

} // namespace string
} // namespace utils

#endif // STRING_H
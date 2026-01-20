#ifndef FILE_H
#define FILE_H

#include <cstdio>
#include <fstream>
#include <iostream>


namespace utils {
namespace file {

bool Read(std::ifstream& file, const std::string& name);

} // namespace file
} // namespace utils

#endif // FILE_H
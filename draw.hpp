#ifndef DRAW_H
#define DRAW_H

#include "float.hpp"

#include <iostream>
#include <string>
#include <cstdint>
#include <fstream>
#include <vector>

namespace draw {
  void writeLittleEndian(std::ofstream& out, uint16_t value);
  void writeLittleEndian(std::ofstream& out, uint32_t value);
  void toBMP(const std::vector<std::vector<math::float3>>& image, const std::string& name);
}

#endif
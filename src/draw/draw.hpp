#ifndef DRAW_H
#define DRAW_H

#include <iostream>
#include <string>
#include <cstdint>
#include <fstream>
#include <vector>

#include "../helpers/binaries.hpp"

#include "../maths/float2.hpp"
#include "../maths/float3.hpp"
#include "../maths/math.hpp"

namespace draw {
  namespace BMP {
    void write(const std::vector<std::vector<maths::float3>>& image, const std::string& name);
  }
}

#endif
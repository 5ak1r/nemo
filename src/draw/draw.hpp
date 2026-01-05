#ifndef DRAW_H
#define DRAW_H

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../math/double2.hpp"
#include "../math/double3.hpp"
#include "../math/vector.hpp"
#include "../math/triangle.hpp"

#include "../utils/binary.hpp"

namespace draw {
namespace BMP {

void Write(const std::vector<std::vector<math::double3>>& image, const std::string& name);

}
}

#endif
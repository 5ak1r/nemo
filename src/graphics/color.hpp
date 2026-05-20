#ifndef COLOR_H
#define COLOR_H

#include "../math/double3.hpp"

#include <cstdint>

namespace graphics {

struct Color {
  uint8_t r, g, b;

  Color() : r(0.0), g(0.0), b(0.0) {}
  Color(uint8_t x, uint8_t y, uint8_t z) : r(x), g(y), b(z) {}
  Color(const math::double3& rgb) : r(rgb.x), g(rgb.y), b(rgb.z) {}
};

} // namespace graphics

#endif // COLOR_H
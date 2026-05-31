#ifndef LIGHTING_H
#define LIGHTING_H

#include "color.hpp"
#include "../math/double3.hpp"

namespace graphics {

struct DirectionalLight {
  math::double3 direction;
  Color color;
  double intensity;
};

struct PointLight {
  math::double3 position;
  Color color;
  double intensity;
};

} // namespace graphics

#endif // LIGHTING_H
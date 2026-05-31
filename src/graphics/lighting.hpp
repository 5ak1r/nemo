#ifndef LIGHTING_H
#define LIGHTING_H

#include "../math/double3.hpp"

namespace graphics {

struct DirectionalLight {
  math::double3 direction = {0.0, 0.0, 0.0};
  math::double3 color = {1.0, 1.0, 1.0};
  double intensity = 1.0;
};

struct PointLight {
  math::double3 position = {0.0, 0.0, 0.0};
  math::double3 color = {1.0, 1.0, 1.0};
  double intensity = 1.0;
};

} // namespace graphics

#endif // LIGHTING_H
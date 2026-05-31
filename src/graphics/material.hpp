#ifndef MATERIAL_H
#define MATERIAL_H

#include "texture.hpp"
#include "../math/double3.hpp"

#include "../math/double3.hpp"

namespace graphics {

struct Material {
  Texture texture;

  math::double3 albedo = {1.0, 1.0, 1.0};
  double ambient = 0.1;
  double diffuse = 1.0;
  //double specular = 0.5;
  //double shininess = 32.0;
};

}

#endif // MATERIAL_H
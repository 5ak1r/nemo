#ifndef SCENE_H
#define SCENE_H

#include <utility>
#include <vector>

#include "camera.hpp"

#include "../math/transform.hpp"

#include "../model/mesh.hpp"
#include "lighting.hpp"

namespace graphics {

struct Scene {
  Camera camera;
  std::vector<std::pair<model::Mesh, math::Transform>> components;
  std::vector<DirectionalLight> directionalLights;
  std::vector<PointLight> pointLights;
};

} // namespace graphics

#endif // SCENE_H
#ifndef SCENE_H
#define SCENE_H

#include <utility>
#include <vector>

#include "camera.hpp"

#include "../math/transform.hpp"

#include "../model/mesh.hpp"

namespace graphics {
namespace scene {

struct Scene {
  Camera camera;
  std::vector<std::pair<model::Mesh, math::Transform>> components;
};

} // namespace scene
} // namespace graphics

#endif // SCENE_H
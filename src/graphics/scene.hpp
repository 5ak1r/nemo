#ifndef SCENE_H
#define SCENE_H

#include <utility>
#include <vector>

#include "../math/transform.hpp"
#include "../model/mesh.hpp"

namespace graphics {
namespace scene {

struct Scene {
  double fov;
  std::vector<std::pair<model::Mesh, math::Transform>> components;
};

}
}

#endif // SCENE_H
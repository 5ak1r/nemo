#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "../math/double2.hpp"
#include "../math/double3.hpp"

namespace model {

struct Vertex {
  math::double3 position;
  math::double2 texture;
  math::double3 normal;

  Vertex(math::double3 v, math::double2 vt, math::double3 vn) : position(v), texture(vt), normal(vn) {}
};

struct Mesh {
  std::vector<Vertex> vertices;
  std::vector<int> triangles;
};

}

#endif
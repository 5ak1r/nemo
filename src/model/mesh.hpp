#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "../math/float2.hpp"
#include "../math/float3.hpp"

namespace model {
  struct Vertex {
    math::float3 position;
    math::float3 normal;
    math::float2 texture;

    Vertex(math::float3 v, math::float3 vn, math::float2 vt) : position(v), normal(vn), texture(vt) {}
  };

  struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<int> triangles;
  };

}

#endif
#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "../math/float2.hpp"
#include "../math/float3.hpp"

namespace model {
  struct Vertex {
    math::float3 position;
    math::float2 texture;
    math::float3 normal;

    Vertex(math::float3 v, math::float2 vt, math::float3 vn) : position(v), texture(vt), normal(vn) {}
  };

  struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<int> triangles;
  };

}

#endif
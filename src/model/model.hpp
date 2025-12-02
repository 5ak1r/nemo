#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "../maths/float2.hpp"
#include "../maths/float3.hpp"

namespace model {
  struct Model {
    std::vector<maths::float3> vertices;
    std::vector<maths::float3> normals;
    std::vector<maths::float2> textures;
    int s;
    std::vector<std::string> faces;
  };
}

#endif
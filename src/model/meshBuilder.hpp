#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "mesh.hpp"

#include <unordered_map>
#include <vector>

namespace model {
  struct vKey {
    int v, vn, vt;

    vKey(int v, int vn, int vt) : v(v), vn(vn), vt(vt) {}

    bool operator==(const vKey& other) const {
      return v == other.v && vn == other.vn && vt == other.vt;
    }
  };

  struct vHash {
    size_t operator()(const vKey& key) const {
      return (key.v * 6291469) ^ (key.vn * 3145739) ^ (key.vt * 1572869);
    }
  };

  class MeshBuilder {
  public:
    MeshBuilder(Mesh& mesh);

    int getVIndex(const vKey& key);

    std::vector<math::float3> positions;
    std::vector<math::float3> normals;
    std::vector<math::float2> textures;

  private:
    Mesh& mesh;
    std::unordered_map<vKey, int, vHash> vMap;
  };
}


#endif
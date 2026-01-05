#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "mesh.hpp"

#include <unordered_map>
#include <vector>

// f v/vt/vn
namespace model {

struct vKey {
  int v, vt, vn;

  vKey(int v, int vt, int vn) : v(v), vt(vt), vn(vn) {}

  bool operator==(const vKey& other) const {
    return v == other.v && vt == other.vt && vn == other.vn;
  }
};

struct vHash {
  size_t operator()(const vKey& key) const {
    return (key.v * 6291469) ^ (key.vt * 3145739) ^ (key.vn * 1572869);
  }
};

class MeshBuilder {
public:
  MeshBuilder(Mesh& mesh);

  int getVIndex(const vKey& key);

  std::vector<math::double3> positions;
  std::vector<math::double2> textures;
  std::vector<math::double3> normals;

private:
  Mesh& mMesh;
  std::unordered_map<vKey, int, vHash> mMap;
};
}


#endif
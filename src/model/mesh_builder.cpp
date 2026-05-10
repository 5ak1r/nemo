#include "mesh_builder.hpp"

namespace model {

MeshBuilder::MeshBuilder(Mesh& mesh) : mMesh(mesh) {}

int MeshBuilder::getVIndex(const vKey &key) {
  auto it = mMap.find(key);
  if (it != mMap.end()) return it->second;

  math::double3 position = positions[key.v];
  math::double2 texture = key.vt >= 0 ? textures[key.vt] : math::double2(0.0, 0.0);
  math::double3 normal = key.vn >= 0 ? normals[key.vn] : math::double3(0.0, 0.0, 0.0);

  Vertex v(position, texture, normal);

  int index = mMesh.vertices.size();

  mMesh.vertices.push_back(v);
  mMap[key] = index;

  return index;
}

} // namespace model
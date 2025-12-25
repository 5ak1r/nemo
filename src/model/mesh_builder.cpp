#include "mesh_builder.hpp"

namespace model {

MeshBuilder::MeshBuilder(Mesh& mesh) : mMesh(mesh) {}

int MeshBuilder::getVIndex(const vKey &key) {
  auto it = mMap.find(key);
  if (it != mMap.end()) return it->second;

  Vertex v(
    positions[key.v],
    textures[key.vt],
    normals[key.vn]
  );

  int index = mMesh.vertices.size();
  
  mMesh.vertices.push_back(v);
  mMap[key] = index;
  
  return index;
}

}
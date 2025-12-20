#include "meshBuilder.hpp"

namespace model {
  MeshBuilder::MeshBuilder(Mesh& mesh) : mesh(mesh) {}
  
  int MeshBuilder::getVIndex(const vKey &key) {
    auto it = vMap.find(key);
    if (it != vMap.end()) return it->second;

    Vertex v(
      positions[key.v],
      textures[key.vt],
      normals[key.vn]
    );

    int index = mesh.vertices.size();
    
    mesh.vertices.push_back(v);
    vMap[key] = index;
    
    return index;
  }
}
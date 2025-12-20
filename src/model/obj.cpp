#include "obj.hpp"

#include "meshBuilder.hpp"

#include <unordered_map>
#include <vector>

namespace model {
  namespace OBJ {
    Mesh read(const std::string& filename) {
      std::ifstream file;
      if(!utils::files::read(file, filename)) {
        exit(1);
      }

      Mesh mesh;
      MeshBuilder meshBuilder(mesh);

      std::string line;
      while(std::getline(file, line)) {
        //skip comments, s (for now) and object name
        if(!line.empty() && std::string("#os").find(line[0]) != std::string::npos) continue;
        
        std::vector<std::string> splitLine = utils::strings::split(line);

        //TODO : error handling
        if(splitLine[0] == "v") {
          math::float3 vertex(
            std::stof(splitLine[1]),
            std::stof(splitLine[2]),
            std::stof(splitLine[3])
          );
          meshBuilder.positions.push_back(vertex);
        } else if(splitLine[0] == "vn") {
          math::float3 normal(
            std::stof(splitLine[1]),
            std::stof(splitLine[2]),
            std::stof(splitLine[3])
          );
          meshBuilder.normals.push_back(normal);
        } else if(splitLine[0] == "vt") {
          math::float2 texture(
            std::stof(splitLine[1]),
            std::stof(splitLine[2])
          );
          meshBuilder.textures.push_back(texture);
        } else if(splitLine[0] == "f") {
          std::vector<vKey> face;

          for(int f = 1; f < splitLine.size(); f++) {
            std::vector<std::string> data = utils::strings::split(splitLine[f], "/");

            face.push_back(vKey(
              std::stoi(data[0]) - 1,
              std::stoi(data[1]) - 1,
              std::stoi(data[2]) - 1
            ));
          }
        
          for(int i = 1; i < face.size() - 1; i++) {
            int idx = meshBuilder.getVIndex(face[0]);
            int idy = meshBuilder.getVIndex(face[i]);
            int idz = meshBuilder.getVIndex(face[i + 1]);

            mesh.triangles.insert(mesh.triangles.end(), {idx, idy, idz});
          }
        }
      }

      return mesh;
    }
  }
}
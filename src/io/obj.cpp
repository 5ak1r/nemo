#include "obj.hpp"

namespace io {
namespace obj {

int CheckNegative(int idx, int size) {
  if (idx == 0) throw std::invalid_argument("cannot have 0 index in OBJ files");

  int result = (idx > 0) ? idx - 1 : idx + size;
  if (result < 0 || result >= size)
    throw std::out_of_range("index out of range");

  return result;
}

model::Mesh Read(const std::string& filename) {
  std::ifstream file;

  if (!io::file::Open(file, filename)) {
    throw std::invalid_argument("not a valid OBJ file");
  }

  model::Mesh mesh;
  model::MeshBuilder meshBuilder(mesh);

  std::string line;
  while(std::getline(file, line)) {
    //skip comments, s (for now) and object name
    if (line.empty()) continue;

    line.erase(std::remove(line.begin(), line.end(), '\r' ), line.end());
    line.erase(std::remove(line.begin(), line.end(), '\n' ), line.end());

    std::vector<std::string> splitLine = utils::string::Split(line);
    if (splitLine.empty()) continue;

    const int lineSize = splitLine.size();
    const std::string& lineType = splitLine[0];

    if (lineType == "v" && lineSize >= 4) {
      math::double3 vertex(
        std::stod(splitLine[1]),
        std::stod(splitLine[2]),
        std::stod(splitLine[3])
      );

      meshBuilder.positions.push_back(vertex);
    }

    else if (lineType == "vt" && lineSize >= 3) {
      math::double2 texture(
        std::stod(splitLine[1]),
        std::stod(splitLine[2])
      );

      meshBuilder.textures.push_back(texture);
    }

    else if (lineType == "vn" && lineSize >= 4) {
      math::double3 normal(
        std::stod(splitLine[1]),
        std::stod(splitLine[2]),
        std::stod(splitLine[3])
      );

      meshBuilder.normals.push_back(normal);
    }

    else if (lineType == "f" && lineSize >= 4) {
      std::vector<model::vKey> face;
      face.reserve(lineSize - 1);

      for (int f = 1; f < lineSize; f++) {
        std::vector<std::string> data = utils::string::Split(splitLine[f], "/");

        const int dataSize = data.size();

        model::vKey vtn = {-1, -1, -1};

        if (dataSize > 0 && !data[0].empty()) {
          int temp = std::stoi(data[0]);
          vtn.v = CheckNegative(temp, meshBuilder.positions.size());
        }

        if (dataSize > 1 && !data[1].empty()) {
          int temp = std::stoi(data[1]);
          vtn.vt = CheckNegative(temp, meshBuilder.textures.size());
        }

        if (dataSize > 2 && !data[2].empty()) {
          int temp = std::stoi(data[2]);
          vtn.vn = CheckNegative(temp, meshBuilder.normals.size());
        }

        face.emplace_back(vtn);
      }

      for (int i = 1; i < face.size() - 1; i++) {
        int idx = meshBuilder.getVIndex(face[0]);
        int idy = meshBuilder.getVIndex(face[i]);
        int idz = meshBuilder.getVIndex(face[i + 1]);

        mesh.triangles.push_back(idx);
        mesh.triangles.push_back(idy);
        mesh.triangles.push_back(idz);
      }
    }
  }

  return mesh;
}

} // namespace OBJ
} // namespace model
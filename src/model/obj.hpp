#ifndef OBJ_H
#define OBJ_H

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "mesh.hpp"
#include "mesh_builder.hpp"
#include "../math/double2.hpp"
#include "../math/double3.hpp"
#include "../utils/file.hpp"
#include "../utils/string.hpp"

namespace model {
namespace OBJ {

Mesh Read(const std::string& filename);

}
}

#endif
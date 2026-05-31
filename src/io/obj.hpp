#ifndef OBJ_H
#define OBJ_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "../io/file.hpp"

#include "../math/double2.hpp"
#include "../math/double3.hpp"

#include "../model/mesh.hpp"
#include "../model/mesh_builder.hpp"

#include "../utils/string.hpp"

namespace io {
namespace obj {

int CheckNegative(int idx, int size);
model::Mesh Read(const std::string& filename);

} // namespace OBJ
} // namespace model

#endif // OBJ_H
#ifndef OBJ_H
#define OBJ_H

#include <fstream>
#include <iostream>
#include <unordered_map>

#include "mesh.hpp"
#include "../utils/file.hpp"
#include "../utils/string.hpp"

namespace model {
namespace OBJ {

Mesh Read(const std::string& filename);

}
}

#endif
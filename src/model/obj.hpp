#ifndef OBJ_H
#define OBJ_H

#include <fstream>
#include <iostream>
#include <unordered_map>

#include "mesh.hpp"
#include "../utils/files.hpp"
#include "../utils/strings.hpp"

namespace model {
  namespace OBJ {
    Mesh read(const std::string& filename);
  }
}

#endif
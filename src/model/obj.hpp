#ifndef OBJ_H
#define OBJ_H

#include <iostream>
#include <fstream>

#include "model.hpp"
#include "../utils/files.hpp"
#include "../utils/strings.hpp"

namespace model {
  namespace OBJ {
    Model read(const std::string& filename);
  }
}

#endif
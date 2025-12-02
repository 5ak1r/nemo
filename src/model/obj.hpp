#ifndef OBJ_H
#define OBJ_H

#include <iostream>
#include <fstream>

#include "model.hpp"
#include "../helpers/files.hpp"
#include "../helpers/strings.hpp"

namespace model {
  namespace OBJ {
    Model read(const std::string& filename);
  }
}

#endif
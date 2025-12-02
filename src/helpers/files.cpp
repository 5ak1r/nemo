
#include "files.hpp"

namespace helpers {
  namespace files {
    bool read(std::ifstream& file, const std::string& name) {
      file.open(name, std::ios::in);

      if(!file.is_open()) {
        std::cerr << "error opening file" << std::endl;
        return false;
      }

      return true;
    }
  }
}

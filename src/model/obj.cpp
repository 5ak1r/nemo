#include "obj.hpp"

namespace model {
  namespace OBJ {
    Model read(const std::string& filename) {
      std::ifstream file;
      if(!helpers::files::read(file, filename)) {
        exit(1);
      }

      std::string line;
      while(std::getline(file, line)) {
        if(line[0] == '#' || line[0] == 'o') continue;
          std::vector<std::string> splitLine = helpers::strings::split(line);
          std::cout << splitLine[0] << std::endl;
        }
    }
  }
}
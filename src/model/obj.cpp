#include "obj.hpp"
#include "model.hpp"

namespace model {
  namespace OBJ {
    Model read(const std::string& filename) {
      std::ifstream file;
      if(!utils::files::read(file, filename)) {
        exit(1);
      }

      std::string line;
      while(std::getline(file, line)) {
        if(line[0] == '#' || line[0] == 'o') continue;
        
        std::vector<std::string> splitLine = utils::strings::split(line);
        for(auto s: splitLine) {
          std::cout << s << std::endl;
        }
      }

      return Model{};
    }
  }
}
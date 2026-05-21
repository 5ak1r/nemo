#ifndef BMP_H
#define BMP_H

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "file.hpp"

#include "../graphics/color.hpp"
#include "../graphics/render_target.hpp"
#include "../graphics/texture.hpp"

#include "../math/double2.hpp"
#include "../math/double3.hpp"
#include "../math/vector.hpp"
#include "../math/triangle.hpp"

#include "../utils/binary.hpp"

namespace io {
namespace bmp {

graphics::Texture Read(const std::string& name);
void Write(const graphics::render::RenderTarget& image, const std::string& name);

}
}

#endif // IO_H
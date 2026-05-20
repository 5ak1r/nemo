#ifndef TEXTURE_H
#define TEXTURE_H

#include "color.hpp"
#include "../math/double2.hpp"

#include <vector>

namespace graphics {

class Texture {
public:
  Texture() = default;
  Texture(std::vector<math::double3> image, int width, int height) : mImage(std::move(image)), mWidth(width), mHeight(height) {}

  Color Sample(const math::double2& texCoord) const;

private:
  std::vector<math::double3> mImage;

  int mWidth;
  int mHeight;
};

} // namespace graphics

#endif // TEXTURE_H
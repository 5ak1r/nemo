#include "texture.hpp"

namespace graphics {

math::double3 Texture::Sample(const math::double2& texCoord) const {
  if (mImage.empty())
    return {1.0, 0.0, 0.0};

  int x = static_cast<int>((texCoord.x - std::floor(texCoord.x)) * (mWidth - 1));
  int y = static_cast<int>((texCoord.y - std::floor(texCoord.y)) * (mHeight - 1));

  Color color = mImage[y * mWidth + x];

  return {
    color.r / 255.0,
    color.g / 255.0,
    color.b / 255.0
  };
}

} // namespace graphics

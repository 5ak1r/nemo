#include "texture.hpp"

namespace graphics {

Color Texture::Sample(const math::double2& texCoord) const {
  if (mImage.empty())
    return {255, 0, 0};

  int x = static_cast<int>((texCoord.x - std::floor(texCoord.x)) * (mWidth - 1));
  int y = static_cast<int>((texCoord.y - std::floor(texCoord.y)) * (mHeight - 1));

  return mImage[y * mWidth + x];
}

} // namespace graphics

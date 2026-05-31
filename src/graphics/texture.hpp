#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>

#include "color.hpp"

#include "../math/double2.hpp"

namespace graphics {

class Texture {
public:
  Texture() = default;
  Texture(std::vector<graphics::Color> image, int width, int height) : mImage(std::move(image)), mWidth(width), mHeight(height) {}

  int Width() const { return mWidth; }
  int Height() const { return mHeight; }
  const std::vector<graphics::Color>& Image() const { return mImage; }

  void setWidth(int w) { mWidth = w; }
  void setHeight(int h) { mHeight = h; }
  void setImage(std::vector<graphics::Color> img) { mImage = std::move(img); }

  math::double3 Sample(const math::double2& texCoord) const;

private:
  std::vector<graphics::Color> mImage;

  int mWidth;
  int mHeight;
};

} // namespace graphics

#endif // TEXTURE_H
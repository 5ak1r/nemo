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

  int Width() const { return mWidth; }
  int Height() const { return mHeight; }
  const std::vector<math::double3>& Image() const { return mImage; }

  void setWidth(int w) { mWidth = w; }
  void setHeight(int h) { mHeight = h; }
  void setImage(std::vector<math::double3> img) { mImage = std::move(img); }

  Color Sample(const math::double2& texCoord) const;

private:
  std::vector<math::double3> mImage;

  int mWidth;
  int mHeight;
};

} // namespace graphics

#endif // TEXTURE_H
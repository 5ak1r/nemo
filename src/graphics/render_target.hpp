#ifndef RENDER_TARGET_H
#define RENDER_TARGET_H

#include <limits>
#include <vector>

#include "../math/double3.hpp"

namespace graphics {
namespace render {

class RenderTarget {
public:
  RenderTarget(int w, int h);

  int getWidth() const;
  int getHeight() const;
  int getSize() const;

  const std::vector<math::double3>& getColorBuffer() const;
  const std::vector<double>& getDepthBuffer() const;

  const math::double3& getColor(int pos) const;
  const math::double3& getColor(int x, int y) const;
  double getDepth(int pos) const;
  double getDepth(int x, int y) const;

  void setColor(int x, int y, const math::double3& value);
  void setDepth(int x, int y, double value);

  void resetBuffers();

private:
  const int mWidth;
  const int mHeight;
  const int mSize;

  std::vector<math::double3> mColorBuffer;
  std::vector<double> mDepthBuffer;
};

} // namespace render
} // namespace graphics


#endif // RENDER_TARGET_H
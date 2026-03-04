#ifndef RENDER_TARGET_H
#define RENDER_TARGET_H

#include <cstdint>
#include <limits>
#include <vector>

namespace graphics {
namespace render {

struct Color {
  uint8_t r, g, b;

  Color() : r(0.0), g(0.0), b(0.0) {}
  Color(uint8_t x, uint8_t y, uint8_t z) : r(x), g(y), b(z) {}
};

class RenderTarget {
public:
  RenderTarget(int w, int h);

  int getWidth() const;
  int getHeight() const;
  int getSize() const;

  const std::vector<Color>& getColorBuffer() const;
  const std::vector<double>& getDepthBuffer() const;

  const Color& getColor(int pos) const;
  const Color& getColor(int x, int y) const;
  double getDepth(int pos) const;
  double getDepth(int x, int y) const;

  void setColor(int x, int y, const Color& value);
  void setDepth(int x, int y, double value);

  void clear();

private:
  const int mWidth;
  const int mHeight;
  const int mSize;

  std::vector<Color> mColorBuffer;
  std::vector<double> mDepthBuffer;
};

} // namespace render
} // namespace graphics

#endif // RENDER_TARGET_H
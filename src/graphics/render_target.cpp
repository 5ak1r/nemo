#include "render_target.hpp"
#include <limits>

namespace graphics {
namespace render {

RenderTarget::RenderTarget(int w, int h)
  : width(w),
    height(h),
    size(w * h),
    colorBuffer(size),
    depthBuffer(size, std::numeric_limits<double>::infinity()) {}

int RenderTarget::getWidth() const {
  return width;
}

int RenderTarget::getHeight() const {
  return height;
}

int RenderTarget::getSize() const {
  return size;
}

const std::vector<math::double3>& RenderTarget::getColorBuffer() const {
  return colorBuffer;
}

const std::vector<double>& RenderTarget::getDepthBuffer() const {
  return depthBuffer;
}

const math::double3& RenderTarget::getColor(int pos) const {
  return colorBuffer[pos];
}

const math::double3& RenderTarget::getColor(int x, int y) const {
  return colorBuffer[y * width + x];
}

double RenderTarget::getDepth(int pos) const {
  return depthBuffer[pos];
}

double RenderTarget::getDepth(int x, int y) const {
  return depthBuffer[y * width + x];
}

void RenderTarget::setColor(int x, int y, const math::double3& value) {
  colorBuffer[y * width + x] = value;
}

void RenderTarget::setDepth(int x, int y, double value) {
  depthBuffer[y * width + x] = value;
}

void RenderTarget::resetBuffers() {
  std::fill(colorBuffer.begin(), colorBuffer.end(), math::double3{0.0, 0.0, 0.0});
  std::fill(depthBuffer.begin(), depthBuffer.end(), std::numeric_limits<double>::infinity());
}

} // namespace render
} // namespace graphics
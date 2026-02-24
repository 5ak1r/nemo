#include "render_target.hpp"
#include <limits>

namespace graphics {
namespace render {

RenderTarget::RenderTarget(int w, int h)
  : mWidth(w),
    mHeight(h),
    mSize(w * h),
    mColorBuffer(mSize),
    mDepthBuffer(mSize, std::numeric_limits<double>::infinity()) {}

int RenderTarget::getWidth() const {
  return mWidth;
}

int RenderTarget::getHeight() const {
  return mHeight;
}

int RenderTarget::getSize() const {
  return mSize;
}

const std::vector<math::double3>& RenderTarget::getColorBuffer() const {
  return mColorBuffer;
}

const std::vector<double>& RenderTarget::getDepthBuffer() const {
  return mDepthBuffer;
}

const math::double3& RenderTarget::getColor(int pos) const {
  return mColorBuffer[pos];
}

const math::double3& RenderTarget::getColor(int x, int y) const {
  return mColorBuffer[y * mWidth + x];
}

double RenderTarget::getDepth(int pos) const {
  return mDepthBuffer[pos];
}

double RenderTarget::getDepth(int x, int y) const {
  return mDepthBuffer[y * mWidth + x];
}

void RenderTarget::setColor(int x, int y, const math::double3& value) {
  mColorBuffer[y * mWidth + x] = value;
}

void RenderTarget::setDepth(int x, int y, double value) {
  mDepthBuffer[y * mWidth + x] = value;
}

void RenderTarget::resetBuffers() {
  std::fill(mColorBuffer.begin(), mColorBuffer.end(), math::double3{0.0, 0.0, 0.0});
  std::fill(mDepthBuffer.begin(), mDepthBuffer.end(), std::numeric_limits<double>::infinity());
}

} // namespace render
} // namespace graphics
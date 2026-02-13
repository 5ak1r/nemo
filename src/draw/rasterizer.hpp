#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <algorithm>
#include <vector>

#include "../math/double2.hpp"
#include "../math/double3.hpp"
#include "../math/triangle.hpp"

using namespace math;

namespace draw {
namespace rasterizer {

void RasterizeTriangle(const double2& a, const double2& b, const double2& c, std::vector<std::vector<double3>>& image, int width, int height);

} // namespace rasterizer
} // namespace draw


#endif // RASTERIZER_H
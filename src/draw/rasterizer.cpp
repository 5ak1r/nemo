#include "rasterizer.hpp"
#include <iostream>
namespace draw {
namespace rasterizer {

void RasterizeTriangle(const double2& a, const double2& b, const double2& c, std::vector<std::vector<double3>>& image, int width, int height) {
  int minX = std::floor(std::min({a.x, b.x, c.x}));
  int minY = std::floor(std::min({a.y, b.y, c.y}));
  int maxX = std::ceil(std::max({a.x, b.x, c.x}));
  int maxY = std::ceil(std::max({a.y, b.y, c.y}));

  minX = std::max(0, minX);
  minY = std::max(0, minY);
  maxX = std::min(width - 1, maxX);
  maxY = std::min(height - 1, maxY);

  for (int y = minY; y < maxY; y++) {
    for (int x = minX; x < maxX; x++) {
      if (triangle::InTriangle(a, b, c, {x + 0.5, y + 0.5})) {
        //image[y][x] = double3(0.0, 0.0, 1.0);
        image[y][x] = double3((double)x / width, (double)y / height, 0.0);
      }
    }
  }
}

} // namespace rasterizer
} // namespace draw
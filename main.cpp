#include "draw.hpp"

int main() {
  const int width = 64;
	const int height = 64;

	std::vector<std::vector<math::float3>> image(width);

	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			float r = x / (width - 1.0f);
			float g = y / (height - 1.0f);
			image[x].push_back({r, g, 0});
		}
	}

  draw::toBMP(image, "test");
}
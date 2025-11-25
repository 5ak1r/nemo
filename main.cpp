#include "draw.hpp"

int main() {
  const int width = 64;
	const int height = 64;

	std::vector<std::vector<math::float3>> image(width);

	const math::float2 a = math::float2(2.0f, 34.0f);
	const math::float2 b = math::float2(22.0f, 3.0f);
	const math::float2 c = math::float2(63.0f, 0.0f);

	for(float y = 0; y < height; y++) {
		for(float x = 0; x < width; x++) {
			if (math::inTriangle(a, b, c, {x, y})) {
				image[x].push_back(math::float3(0.0f, 0.0f, 1.0f));
			} else {
				image[x].push_back(math::float3(0.0f,0.0f,0.0f));
			}
		}
	}

  draw::toBMP(image, "test");
}
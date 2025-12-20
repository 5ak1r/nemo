#include "src/draw/draw.hpp"
#include "src/model/obj.hpp"
#include "src/model/mesh.hpp"

int main() {
  const int width = 64;
	const int height = 64;

	std::vector<std::vector<math::float3>> image(width);

	const math::float2 a = math::float2(2.0f, 34.0f);
	const math::float2 b = math::float2(22.0f, 3.0f);
	const math::float2 c = math::float2(63.0f, 0.0f);

	for(float y = 0; y < height; y++) {
		for(float x = 0; x < width; x++) {
			if (math::triangles::inTriangle(a, b, c, {x, y})) {
				image[x].push_back(math::float3(0.0f, 0.0f, 1.0f));
			} else {
				image[x].push_back(math::float3(0.0f,0.0f,0.0f));
			}
		}
	}

  draw::BMP::write(image, "test");
	model::Mesh mesh = model::OBJ::read("resources/fox.obj");

	const int foxW = 2560;
	const int foxH = 1600;

	std::vector<std::vector<math::float3>> foxI(width);
}
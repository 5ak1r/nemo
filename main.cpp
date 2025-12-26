#include "src/draw/draw.hpp"
#include "src/math/matrix.hpp"
#include "src/model/mesh.hpp"
#include "src/model/obj.hpp"

int main() {
  const int width = 1024;
	const int height = 1024;

	model::Mesh mesh = model::OBJ::Read("resources/cube.obj");

	std::vector<math::float3> imgRow(width, math::float3(0,0,0));
	std::vector<std::vector<math::float3>> image(height, imgRow);

	for(int i = 0; i < mesh.vertices.size(); i += 3) {
		//math::float2 a = mesh.vertices[mesh.triangles[i]];
		//math::float2 b = mesh.vertices[mesh.triangles[i + 1]];
		//math::float2 c = mesh.vertices[mesh.triangles[i + 2]];

		for(float y = 0; y < height; y++) {
			for(float x = 0; x < width; x++) {
				//if (math::triangle::inTriangle(a, b, c, {x, y}))
					image[x][y] = math::float3(0.0f, 0.0f, 1.0f);
			}
		}
	}

  draw::BMP::Write(image, "test");
}
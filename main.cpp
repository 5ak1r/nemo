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

  math::Matrix<int> mat1(2, 2);
  math::Matrix<int> mat2(2, 2);
  math::Matrix<float> mat3(4, 2);
  for(int i = 0; i < 4; i++) {
    mat1.setData(i, i);
    mat2.setData(i, i);
    mat3.setData(i, i);
  }

  for(int i = 0; i < 4; i++) mat3.setData(i + 4, i + 4);

  mat1 *= mat2;
  std::cout << mat1 << "\n\n";

  auto mat4 = mat1 * mat2;
  std::cout << (mat1 * mat2) << "\n\n";

  std::cout << mat3 << "\n\n";
  std::cout << mat3 * mat2 << "\n\n";

  std::cout << math::det(mat2) << "\n\n";

  std::vector<int> data5 = { 1, 2, 3, 4, 5, 5, 52, 24, 12, 23, 1, 44, 234, 9, 2, 1 };
  math::Matrix<int> mat5(4, 4, data5);

  std::cout << mat5 << math::det(mat5) << "\n\n";
}
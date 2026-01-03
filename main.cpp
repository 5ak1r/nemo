#include "src/draw/draw.hpp"
#include "src/math/lu_decomp.hpp"
#include "src/math/matrix.hpp"
#include "src/model/mesh.hpp"
#include "src/model/obj.hpp"

int main() {
  const int width = 1024;
	const int height = 1024;

	model::Mesh mesh = model::OBJ::Read("resources/cube.obj");

	std::vector<math::float3> imgRow(width, math::float3(0,0,0));
	std::vector<std::vector<math::float3>> image(height, imgRow);

	for (int i = 0; i < mesh.vertices.size(); i += 3) {
		//math::float2 a = mesh.vertices[mesh.triangles[i]];
		//math::float2 b = mesh.vertices[mesh.triangles[i + 1]];
		//math::float2 c = mesh.vertices[mesh.triangles[i + 2]];

		for (float y = 0; y < height; y++) {
			for (float x = 0; x < width; x++) {
				//if (math::triangle::inTriangle(a, b, c, {x, y}))
					image[x][y] = math::float3(0.0f, 0.0f, 1.0f);
			}
		}
	}

  draw::BMP::Write(image, "test");

  math::Matrix<int> mat1(2, 2);
  math::Matrix<int> mat2(2, 2);
  math::Matrix<float> mat3(4, 2);
  for (int i = 0; i < 4; i++) {
    mat1(i) = i;
    mat2(i) = i;
    mat3(i) = i;
  }

  for (int i = 0; i < 4; i++) mat3(i + 4) = i + 4;

  mat1 *= mat2;
  std::cout << mat1 << "\n\n";

  auto mat4 = mat1 * mat2;
  std::cout << (mat1 * mat2) << "\n\n";

  std::cout << mat3 << "\n\n";
  std::cout << mat3 * mat2 << "\n\n";

  std::cout << mat2 << "\n\n";
  std::cout << math::det(mat2) << "\n\n";

  std::vector<int> data5 = { 1, 2, 3, 4, 5, 5, 52, 24, 12, 23, 1, 44, 234, 9, 2, 1 };
  math::Matrix<int> mat5(4, 4, data5);

  std::cout << mat5 << "\n\n";
  std::cout << math::det(mat5) << "\n\n";
  std::cout << mat5 * mat5 << "\n\n";

  math::Matrix<int> mat6 = math::Matrix<int>::identity(4);
  std::cout << mat6 << "\n\n";

  mat2(0, 0) = 2;
  std::cout << mat2 << "\n\n";

  math::Matrix<int> mat7 = math::Matrix<int>(3, 3, { 2, -1, -2, -4, 6, 3, -4, -2, 8 });

  auto res7 = math::DoolittleLU(mat7);
  std::cout << res7.pivot << "\n\n";
  std::cout << res7.upper << "\n\n";
  std::cout << res7.lower << "\n\n";
  std::cout << math::det(mat7) << "\n\n";

  std::vector<int> data8 = {
    7, 12, -3,  8,  0, 15,
    -6,  4,  9, -1, 11,  2,
    14, -8,  5,  3, -2, 10,
    1, 13, -5,  6,  9, -7,
    8,  0, 16, -4,  2, 11,
    -9,  5,  3, 12, -1,  4
  };
  math::Matrix<int> mat8 = math::Matrix<int>(6, 6, data8 );
  auto res8 = math::DoolittleLU(mat8);
  std::cout << res8.upper << "\n\n";
  std::cout << math::det(mat8) << "\n\n";
}
#ifndef HESSENBERG_H
#define HESSENBERG_H

#include <vector>

#include "matrix.hpp"
#include "vector.hpp"

// https://en.wikipedia.org/wiki/Hessenberg_matrix
namespace math {
namespace hessenberg {

std::vector<double> Omega(const std::vector<double>& aPrime);
Matrix HouseholderMatrix(const std::vector<double>& aPrime);
Matrix BlockMatrix(const Matrix& mat, const int& amount);
Matrix UpperHessenbergMatrix(const Matrix& mat);

} // namespace hessenberg
} // namespace math

#endif // HESSENBERG_H
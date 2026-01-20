#ifndef MATRIX_HELPERS_H
#define MATRIX_HELPERS_H

#include <stdexcept>
#include <vector>

#include "lu_decomp.hpp"
#include "matrix.hpp"

namespace math {

// forward declaration
struct Matrix;

namespace matrix {

double Determinant(const Matrix& mat);
Matrix Transpose(const Matrix& mat);
Matrix Adjugate(const Matrix& mat);
Matrix Cofactors(const Matrix& mat);
Matrix Inverse(const Matrix& mat);
Matrix Multiply(const Matrix& a, const Matrix& b);
Matrix RemoveMatrixRow(const Matrix& mat, int idx);
Matrix RemoveMatrixCol(const Matrix& mat, int idx);

} // namespace matrix
} // namespace math

#endif // MATRIX_HELPERS_H
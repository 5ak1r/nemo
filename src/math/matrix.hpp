#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

#include "float3.hpp"

/*
- create a matrix
  - 2d array or flat array with manipulation (index = row * cols + col)
  - mat struct -> rows, cols, data
- access and modify elements
  - check bounds, decide if 0 based
- addition / subtraction
- multiplication / division
- transpose
- determinant, inverse
- eigenvalues
- optimisations (BLAS)
- sparce matrices
*/

namespace math {
  
template <typename T> 
class Matrix {
public:
  Matrix(int rows, int cols);
  T& operator()(int i, int j);
  T operator()(int i, int j) const;
  
private:
  int mRows;
  int mCols;
  std::vector<T> mData;
};

}

#include "matrix.tpp"

#endif
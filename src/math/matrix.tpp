#ifndef MATRIX_T
#define MATRIX_T


namespace math {

template <typename T>
Matrix<T>::Matrix(int rows, int cols) : mRows(rows), mCols(cols), mData(rows * cols) {}

}

#endif
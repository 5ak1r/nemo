#include "matrix.hpp"

// avoid circular includes
#include "lu_decomp.hpp"
#include "matrix_helpers.hpp"
#include "qr_algorithm.hpp"

namespace math {
// easier multiplication
Matrix::Matrix(double2 a) : mRows(2), mCols(1), mSize(2), mData({a.x, a.y}) {}
Matrix::Matrix(double3 a) : mRows(3), mCols(1), mSize(3), mData({a.x, a.y, a.z}) {}

Matrix::Matrix(int rows, int cols) : mRows(rows), mCols(cols), mSize(rows * cols), mData(mSize) {
  if (mRows <= 0 || mCols <= 0)
    throw std::invalid_argument("Rows and Columns must be greater than zero");
}

Matrix::Matrix(int rows, int cols, std::vector<double> data) : mRows(rows), mCols(cols), mSize(rows * cols) {
  if (mRows <= 0 || mCols <= 0)
    throw std::invalid_argument("Rows and Columns must be greater than zero");
  if (data.size() != mSize)
    throw std::invalid_argument("Data does not match row and column size");

  mData = data;
}

Matrix Matrix::identity(int n) {
  Matrix I(n, n);

  for (int i = 0; i < n; i++) {
    I.mData[i * n + i] = 1.0;
  }

  return I;
}

// getters
std::vector<double> Matrix::row(int idx) const {
  std::vector<double> result;

  for (int c = 0; c < mCols; c++)
    result.push_back(mData[idx * mCols + c]);

  return result;
}

std::vector<double> Matrix::col(int idx) const {
  std::vector<double> result;

  for (int r = 0; r < mRows; r++)
    result.push_back(mData[r * mCols + idx]);

  return result;
}

int Matrix::rows() const { return mRows; }
int Matrix::cols() const { return mCols; }
int Matrix::size() const { return mSize; }
std::vector<double> Matrix::data() const { return mData; }
bool Matrix::isSquare() const { return mRows == mCols; }

std::vector<double> Matrix::getRow(const int& idx) const {
  if (idx < 0 || idx >= mRows)
    throw std::invalid_argument("Row index out of bounds");

  int start = idx * mCols;

  return std::vector<double>(mData.begin() + start, mData.begin() + start + mCols);
}

std::vector<double> Matrix::getCol(const int& idx) const {
  if (idx < 0 || idx >= mCols)
    throw std::invalid_argument("Column index out of bounds");

  std::vector<double> result;
  result.reserve(mRows);

  for (int row = 0; row < mRows; row++) {
    result.push_back(mData[row * mCols + idx]);
  }

  return result;
}

int Matrix::whichRow(int idx) const { return idx / mCols; }
int Matrix::whichCol(int idx) const { return idx % mCols; }

// helpers
void Matrix::swapRows(const int& r1, const int& r2) {
  if (r1 == r2) return;

  if (r1 < 0 || r1 >= mRows || r2 < 0 || r2 >= mRows)
    throw std::out_of_range("Row index out of bounds");

  for (int c = 0; c < mCols; c++)
    std::swap((*this)(r1, c), (*this)(r2, c));
}

Matrix Matrix::adjugate() const {
  if (!isSquare())
    throw std::invalid_argument("Cannot compute the adjugate of a non-square matrix");

  return matrix::Adjugate(*this);
}

// we don't need to convert data types as the determinant matches the type of the data
Matrix Matrix::cofactors() const {
  return matrix::Cofactors(*this);
}

double Matrix::determinant() const {
  return matrix::Determinant(*this);
}

Matrix Matrix::inverse() const {
  return matrix::Inverse(*this);
}

Matrix Matrix::transpose() const {
  return matrix::Transpose(*this);
}

std::vector<std::complex<double>> Matrix::eigenvalues() const {
  return matrix::Eigenvalues(*this);
}

// operator overloads
// 2d indexing
double& Matrix::operator()(int i, int j) {
  if (i < 0 || i >= mRows || j < 0 || j >= mCols)
    throw std::out_of_range("Matrix index out of range");

  return mData[i * mCols + j];
}

double Matrix::operator()(int i, int j) const {
  if (i < 0 || i >= mRows || j < 0 || j >= mCols)
    throw std::out_of_range("Matrix index out of range");

  return mData[i * mCols + j];
}

// 1d indexing
double& Matrix::operator()(int ij) {
  if (ij < 0 || ij >= mSize)
    throw std::out_of_range("Matrix index out of range");

  return mData[ij];
}

double Matrix::operator()(int ij) const {
  if (ij < 0 || ij >= mSize)
    throw std::out_of_range("Matrix index out of range");

  return mData[ij];
}

Matrix& Matrix::operator+=(const Matrix& other) {
  if (mRows != other.rows() || mCols != other.cols())
    throw std::invalid_argument("Matrix dimensions must be equal");

  for (int i = 0; i < mSize; i++) mData[i] += other(i);

  return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
  if (mRows != other.rows() || mCols != other.cols())
    throw std::invalid_argument("Matrix dimensions must be equal");

  for (int i = 0; i < mSize; i++) mData[i] -= other(i);

  return *this;
}

Matrix& Matrix::operator*=(const Matrix& other) {
  if (mCols != other.rows())
    throw std::invalid_argument("Other matrix column count must equal row count");

  *this = matrix::Multiply(*this, other);
  return *this;
}

// more operator overloads
Matrix operator+(const Matrix& a, const Matrix& b) {
  if (a.rows() != b.rows() || a.cols() != b.cols())
    throw std::invalid_argument("Matrix dimensions must be equal");

  Matrix result(a.rows(), a.cols());

  for (int i = 0; i < a.size(); i++) {
    result(i) = a(i) + b(i);
  }

  return result;
}

Matrix operator-(const Matrix& a, const Matrix& b) {
  if (a.rows() != b.rows() || a.cols() != b.cols())
    throw std::invalid_argument("Matrix dimensions must be equal");

  Matrix result(a.rows(), b.cols());

  for (int i = 0; i < a.size(); i++) {
    result(i) = a(i) - b(i);
  }

  return result;
}

Matrix operator*(const Matrix& a, const Matrix& b) {
  if (a.cols() != b.rows())
    throw std::invalid_argument("Other matrix column count must equal row count");

  Matrix res = matrix::Multiply(a, b);
  return res;
}

Matrix operator*(const double& scalar, const Matrix& mat) {
  Matrix result(mat.rows(), mat.cols());

  for (int i = 0; i < mat.size(); i++) {
    result(i) = scalar * mat(i);
  }

  return result;
}

bool operator==(const Matrix& a, const Matrix& b) {
  if (a.size() != b.size())
    return false;

  for (int i = 0; i < a.size(); i++) {
    if (a(i) != b(i)) return false;
  }

  return true;
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
  int width = 0;
  int precision = 6;

  for (int i = 0; i < mat.size(); i++) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << mat(i);
    width = std::max(width, static_cast<int>(oss.str().length()));
  }

  for (int i = 0; i < mat.rows(); i++) {
    for (int j = 0; j < mat.cols(); j++) {
      os << std::fixed << std::setw(width + 1) << std::setprecision(precision) << mat(i, j);
    }
    os << "\n";
  }

  return os;
}

} // namespace math
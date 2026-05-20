#ifndef MATRIX_H
#define MATRIX_H

#include <complex>
#include <iomanip>
#include <vector>

#include "../double2.hpp"
#include "../double3.hpp"

namespace math {

class Matrix {
public:
  Matrix(const double2& a);
  Matrix(const double3& a);
  Matrix(int rows, int cols);
  Matrix(int rows, int cols, const std::vector<double>& data);

  static Matrix identity(int n);

  std::vector<double> row(int idx) const;
  std::vector<double> col(int idx) const;

  int rows() const;
  int cols() const;
  int size() const;
  std::vector<double> data() const;
  bool isSquare() const;

  std::vector<double> getRow(int idx) const;
  std::vector<double> getCol(int idx) const;

  int whichRow(int idx) const;
  int whichCol(int idx) const;

  void swapRows(int r1, int r2);

  Matrix adjugate() const;
  Matrix cofactors() const;
  double determinant() const;
  Matrix inverse() const;
  Matrix transpose() const;
  std::vector<std::complex<double>> eigenvalues() const;

  double& operator()(int i, int j);
  double operator()(int i, int j) const;
  double& operator()(int ij);
  double operator()(int ij) const;
  Matrix& operator+=(const Matrix& other);
  Matrix& operator-=(const Matrix& other);
  Matrix& operator*=(const Matrix& other);

private:
  int mRows;
  int mCols;
  int mSize;
  std::vector<double> mData;

};

Matrix operator+(const Matrix& a, const Matrix& b);
Matrix operator-(const Matrix& a, const Matrix& b);
Matrix operator*(const Matrix& a, const Matrix& b);
Matrix operator*(const double& scalar, const Matrix& mat);

bool operator==(const Matrix& a, const Matrix& b);

std::ostream& operator<<(std::ostream& os, const Matrix& mat);

} // namespace math

#endif // MATRIX_H
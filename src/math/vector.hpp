#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <vector>

#include "double2.hpp"
#include "double3.hpp"

namespace math {
namespace vector {

// version that works with matrix rows and columns
inline double Dot(const std::vector<double>& vec) {
  double result = 0.0;
  for (auto v : vec) result += v * v;

  return result;
}

inline double Dot(const std::vector<double>& vec1, const std::vector<double>& vec2) {
  if (vec1.size() != vec2.size())
    throw std::invalid_argument("vectors must be the same size to compute the dot product");

  double result = 0.0;
  for (int i = 0; i < vec1.size(); i++) result += vec1[i] * vec2[i];

  return result;
}

inline double Norm(const std::vector<double>& vec) {
  return std::sqrt(Dot(vec));
}

inline std::vector<double> StandardBasis(int pos, int size) {
  if (pos >= size)
    throw std::invalid_argument("position cannot be greater than or equal to size");

  std::vector<double> result(size);
  result[pos] = 1.0;

  return result;
}

template<typename F, typename T1, typename T2>
auto Operation(const std::vector<T1>& a, const std::vector<T2>& b, F&& func) {
  using T3 = std::decay_t<decltype(func(a[0], b[0]))>;

  std::vector<T3> result;
  result.reserve(a.size());

  for (int i = 0; i < a.size(); i++) result.push_back(func(a[i], b[i]));

  return result;
}

template<typename T1, typename T2>
auto Add(const std::vector<T1>& a, const std::vector<T2>& b) {
  if (a.size() != b.size())
    throw std::invalid_argument("cannot perform addition on vectors of different lengths");

  return Operation(a, b, [](T1 x, T2 y){ return x + y; });
}

template<typename T1, typename T2>
auto Subtract(const std::vector<T1>& a, const std::vector<T2>& b) {
  if (a.size() != b.size())
    throw std::invalid_argument("cannot perform subtraction on vectors of different lengths");

  return Operation(a, b, [](T1 x, T2 y){ return x - y; });
}

template<typename T1, typename T2>
auto Multiply(const std::vector<T1>& a, const std::vector<T2>& b) {
  if (a.size() != b.size())
    throw std::invalid_argument("cannot perform multiplication on vectors of different lengths");

  return Operation(a, b, [](T1 x, T2 y){ return x * y; });
}

template<typename T1, typename T2>
auto Multiply(T1 scalar, const std::vector<T2>& vec) {
  using T3 = std::common_type_t<T1, T2>;

  std::vector<T3> result;
  for (auto v : vec) result.push_back(scalar * v);

  return result;
}

template<typename T1, typename T2>
auto Multiply(const std::vector<T1>& vec, T2 scalar) {
  return Multiply(scalar, vec);
}

template<typename T1, typename T2>
auto Divide(const std::vector<T1>& a, const std::vector<T2>& b) {
  if (a.size() != b.size())
    throw std::invalid_argument("cannot perform division on vectors of different lengths");

  return Operation(a, b, [](T1 x, T2 y){ return static_cast<double>(x) / y; });
}

} // namespace vector
} // namespace math

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
  os << "{ ";
  for (int i = 0; i < vec.size(); i++) os << vec[i] << ((i == vec.size() - 1) ? "" : ", ");
  os << " }";

  return os;
}

#endif // VECTOR_H
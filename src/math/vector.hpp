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

inline double Dot(const double2& a, const double2& b) {
  return a.x * b.x + a.y * b.y;
}

inline double Dot(const double3& a, const double3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

// version that works with matrix rows and columns
template<typename T>
auto Dot(const std::vector<T>& vec) {
  static_assert(std::is_arithmetic<T>::value, "Not an arithmetic data type");

  using T3 = std::common_type_t<T, double>;

  T3 result = T3{};
  for (auto v : vec) result += static_cast<T3>(v) * static_cast<T3>(v);

  return result;
}

template<typename T>
auto Norm(const T& vec) {
  return std::sqrt(Dot(vec));
}

inline double2 Perpendicular(const double2& a) {
  return { a.y, -a.x };
}

inline std::vector<double> StandardBasis(int pos, int size) {
  if (pos >= size)
    throw std::invalid_argument("Position cannot be greater than or equal to size");

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
    throw std::invalid_argument("Cannot perform addition on vectors of different lengths");

  return Operation(a, b, [](T1 x, T2 y){ return x + y; });
}

template<typename T1, typename T2>
auto Subtract(const std::vector<T1>& a, const std::vector<T2>& b) {
  if (a.size() != b.size())
    throw std::invalid_argument("Cannot perform subtraction on vectors of different lengths");

  return Operation(a, b, [](T1 x, T2 y){ return x - y; });
}

template<typename T1, typename T2>
auto Multiply(const std::vector<T1>& a, const std::vector<T2>& b) {
  if (a.size() != b.size())
    throw std::invalid_argument("Cannot perform multiplication on vectors of different lengths");

  return Operation(a, b, [](T1 x, T2 y){ return x * y; });
}

template<typename T1, typename T2>
auto Multiply(const T1& scalar, const std::vector<T2>& vec) {
  using T3 = std::common_type_t<T1, T2>;

  std::vector<T3> result;
  for (auto v : vec) result.push_back(scalar * v);

  return result;
}

template<typename T1, typename T2>
auto Multiply(const std::vector<T1>& vec, const T2& scalar) {
  return Multiply(scalar, vec);
}

template<typename T1, typename T2>
auto Divide(const std::vector<T1>& a, const std::vector<T2>& b) {
  if (a.size() != b.size())
    throw std::invalid_argument("Cannot perform division on vectors of different lengths");

  return Operation(a, b, [](T1 x, T2 y){ return static_cast<double>(x) / y; });
}

}
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
  os << "{ ";
  for (int i = 0; i < vec.size(); i++) os << vec[i] << ((i == vec.size() - 1) ? "" : ", ");
  os << " }";

  return os;
}

#endif
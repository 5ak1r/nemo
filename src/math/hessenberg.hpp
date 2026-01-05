#ifndef HESSENBERG_H
#define HESSENBERG_H

#include <type_traits>
#include <vector>

#include "vector.hpp"

namespace math {
namespace hessenberg {

template<typename T>
std::vector<T> HouseholderVector() {

}

template<typename T>
std::vector<double> Omega(std::vector<T> vector) {
  static_assert(std::is_arithmetic<T>::value, "Not an arithmetic data type");

  double norm = vector::Norm(vector);
  std::vector<double> e = vector::StandardBasis(0, vector.size());
  std::vector<double> eNorm = vector::Multiply(e, norm);

  if (vector[0] == T{})
    return vector::Subtract(eNorm, vector);

  return vector::Add(eNorm, vector::Multiply(vector[0] / std::abs(vector[0]), vector));
}

}
}

#endif
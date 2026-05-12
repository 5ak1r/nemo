#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace math {
namespace constants {

constexpr double PI = 3.1415926536;

} // namespace constants

namespace conversions {

inline double ToDegrees(double rad) { return rad * 180 / constants::PI; }
inline double ToRadians(double deg) { return deg * constants::PI / 180; }

} // namespace conversions
} // namespace math

#endif // CONSTANTS_H
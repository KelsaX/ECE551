#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
void Vector2D::initVector(double init_x, double init_y) {
  init_x = 0;
  init_y = 0;
}

double Vector2D::getMagnitude() const {
  double vectorMagnitude = std::sqrt(x * x + y * y);
  return vectorMagnitude;
}
Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}
double Vector2D::dot(const Vector2D & rhs) const {
  return x * rhs.x + y * rhs.y;
}

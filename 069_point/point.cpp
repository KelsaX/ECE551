#include "point.hpp"

#include <cmath>
#include <cstdio>

Point::Point() : x(0), y(0) {
}
void Point::move(double dx, double dy) {
  x += dx;
  y += dy;
}
double Point::distanceFrom(const Point & p) {
  return std::sqrt(std::pow(x - p.x, 2) + std::pow(y - p.y, 2));
}

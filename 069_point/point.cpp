#include <cmath>
#include <cstdio>
#include "point.hpp"

Point::Point():x(0), y(0){}
void Point:: move(double dx, double dy){
  x += dx;
  y += dy;
}

double Point:: distanceFrom(const Point & p){
   return  std::sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));

}

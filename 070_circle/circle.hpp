#include "point.hpp"

class Circle{
private:
public:
  Point center;
  const double radius;
  Circle(Point p, double r);
  void move (double dx, double dy);
  double intersectionArea(const Circle & otherCircle);

};

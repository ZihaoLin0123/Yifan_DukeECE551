#include "circle.hpp"
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;
const double PI = acos(-1);

Circle:: Circle(Point p, double r):center(p), radius(r){}

void Circle::move (double dx, double dy){
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle){
  double distance = center.distanceFrom(otherCircle.center);
  if((distance + min(radius, otherCircle.radius)) <= max(radius, otherCircle.radius)){ 
    if(radius < otherCircle.radius){ 
      return PI * radius * radius;
    } else{
      return PI * otherCircle.radius * otherCircle.radius ;
    }
  }
    else if(distance >= (radius + otherCircle.radius)){  
      return 0.0;
    }
    else  {
            double d1 = 2 * acos((radius * radius + distance * distance - otherCircle.radius *  otherCircle.radius)
				 /(2 * radius * distance)); 
            double d2= 2 * acos((otherCircle.radius *  otherCircle.radius + distance * distance -radius * radius)
				/(2 * otherCircle.radius * distance)); 
            double area1 = radius * radius * d1 / 2 - radius * radius * sin(d1) / 2;
            double area2 = otherCircle.radius *  otherCircle.radius * d2 / 2
	      - otherCircle.radius *  otherCircle.radius * sin(d2) / 2;
            double area= area1 + area2;
            return area;
    }




}

#include "Point.hpp"

Point::Point(PaperUnit aX, PaperUnit aY) :
  x(aX),
  y(aY)
{
}

bool operator!=(const Point &left, const Point &right)
{
  return !(left == right);
}

bool operator==(const Point &left, const Point &right)
{
  return (left.x == right.x) && (left.y == right.y);
}

std::ostream &operator<<(std::ostream &stream, const Point &point)
{
  stream << "(" << point.x << "," << point.y << ")";
  return stream;
}

Point operator+(const Point &left, const Point &right)
{
  return Point(left.x + right.x, left.y + right.y);
}

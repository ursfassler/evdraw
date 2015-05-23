#include "types.hpp"


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


std::ostream &operator<<(std::ostream &stream, const ConnectorSide &connectorSide)
{
  switch (connectorSide) {
    case ConnectorSide::Right: {
      stream << "right";
      break;
    }
    case ConnectorSide::Left: {
      stream << "left";
      break;
    }
  }
  return stream;
}

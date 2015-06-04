#include "Endpoint.hpp"

Endpoint::Endpoint(const Point &aPosition) :
  RelativePosition(aPosition)
{
}

bool Endpoint::freeMovable() const
{
  return !hasAnchor();
}

std::ostream &operator<<(std::ostream &stream, const Endpoint &endpoint)
{
  stream << endpoint.getAbsolutePosition();
  return stream;
}


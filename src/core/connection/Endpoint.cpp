#include "Endpoint.hpp"

Endpoint::Endpoint(const Point &aPosition) :
  Positionable(nullptr, aPosition)
{
}

bool Endpoint::freeMovable() const
{
  return getAnchor() == nullptr;
}

std::ostream &operator<<(std::ostream &stream, const Endpoint &endpoint)
{
  stream << endpoint.getAbsolutePosition();
  return stream;
}


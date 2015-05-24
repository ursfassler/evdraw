#include "Endpoint.hpp"

Endpoint::Endpoint(PaperUnit aX, PaperUnit aY) :
  ObserverCollection(),
  x(aX),
  y(aY)
{
}

Endpoint::~Endpoint()
{
}

PaperUnit Endpoint::getX() const
{
  return x;
}

void Endpoint::setX(PaperUnit value)
{
  if (value != x) {
    x = value;
    notifyObservers(this);
  }
}

PaperUnit Endpoint::getY() const
{
  return y;
}

void Endpoint::setY(PaperUnit value)
{
  if (value != y) {
    y = value;
    notifyObservers(this);
  }
}

std::ostream &operator<<(std::ostream &stream, const Endpoint &endpoint)
{
  stream << "(" << endpoint.getX() << "," << endpoint.getY() << ")";
  return stream;
}


PortPoint::PortPoint(PaperUnit aX, PaperUnit aY) :
  Endpoint(aX, aY)
{
}

bool PortPoint::freeMovable() const
{
  return false;
}


IntermediatePoint::IntermediatePoint(PaperUnit aX, PaperUnit aY) :
  Endpoint(aX, aY)
{
}

bool IntermediatePoint::freeMovable() const
{
  return true;
}


#include "Endpoint.hpp"

Endpoint::Endpoint(PaperUnit aX, PaperUnit aY) :
  listener(this),
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
    listener.notifyListeners<&EndpointListener::changeX>();
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
    listener.notifyListeners<&EndpointListener::changeY>();
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


EndpointListener::~EndpointListener()
{
}

void EndpointListener::changeX(const Endpoint *)
{
}

void EndpointListener::changeY(const Endpoint *)
{
}

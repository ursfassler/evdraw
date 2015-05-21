#include "Endpoint.hpp"

Endpoint::Endpoint(PaperUnit aX, PaperUnit aY) :
  x(aX),
  y(aY),
  listeners()
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
    notifyXchange();
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
    notifyYchange();
  }
}

bool Endpoint::hasListener() const
{
  return !listeners.empty();
}

void Endpoint::addListener(EndpointListener *listener)
{
  listeners.push_back(listener);
}

void Endpoint::removeListener(EndpointListener *listener)
{
  listeners.remove(listener);
}

void Endpoint::notifyXchange()
{
  for (EndpointListener *itr : listeners) {
    itr->changeX(this, x);
  }
}

void Endpoint::notifyYchange()
{
  for (EndpointListener *itr : listeners) {
    itr->changeY(this, y);
  }
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

void EndpointListener::changeX(Endpoint *sender, PaperUnit value)
{
}

void EndpointListener::changeY(Endpoint *sender, PaperUnit value)
{
}

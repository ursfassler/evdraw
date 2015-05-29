#include "Endpoint.hpp"

Endpoint::Endpoint(const Point &aPosition) :
  ObserverCollection(),
  position(aPosition)
{
}

Endpoint::~Endpoint()
{
}

const Point &Endpoint::getPosition() const
{
  return position;
}

void Endpoint::setPosition(const Point &value)
{
  if (position != value) {
    position = value;
    notify(&EndpointObserver::positionChanged, static_cast<const Endpoint *>(this));
  }
}

std::ostream &operator<<(std::ostream &stream, const Endpoint &endpoint)
{
  stream << endpoint.getPosition();
  return stream;
}


PortPoint::PortPoint(const Point &position) :
  Endpoint(position)
{
}

bool PortPoint::freeMovable() const
{
  return false;
}


IntermediatePoint::IntermediatePoint(const Point &position) :
  Endpoint(position)
{
}

bool IntermediatePoint::freeMovable() const
{
  return true;
}


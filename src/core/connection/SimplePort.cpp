#include "SimplePort.hpp"


SimplePort::SimplePort() :
  position(Point(0,0))
{
}

SimplePort::SimplePort(const Point &aPosition) :
  position(aPosition)
{
}

void SimplePort::addConnectionPoint(RelativePosition *port)
{
  ports.insert(port);
}

void SimplePort::removeConnectionPoint(RelativePosition *port)
{
  ports.erase(port);
}

std::string SimplePort::getName() const
{
  return "";
}

Point SimplePort::getPosition() const
{
  return position;
}

void SimplePort::accept(Visitor &) const
{
}

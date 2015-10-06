#include "PortMock.hpp"

PortMock::PortMock()
{
}

PortMock::PortMock(const Point &aPosition) :
  position{aPosition}
{
}

PortMock::PortMock(const std::string &aName) :
  name{aName}
{
}

void PortMock::addConnectionPoint(RelativePosition *port)
{
  ports.insert(port);
}

void PortMock::removeConnectionPoint(RelativePosition *port)
{
  ports.erase(port);
}

std::string PortMock::getName() const
{
  return name;
}

Point PortMock::getPosition() const
{
  return position;
}

void PortMock::accept(Visitor &)
{
}

void PortMock::accept(ConstVisitor &) const
{
}

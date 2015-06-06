#include "SimplePort.hpp"


void SimplePort::addConnectionPoint(RelativePosition *port)
{
  ports.insert(port);
}

void SimplePort::removeConnectionPoint(RelativePosition *port)
{
  ports.erase(port);
}

void SimplePort::accept(Visitor &) const
{
}

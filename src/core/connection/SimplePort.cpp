#include "SimplePort.hpp"


void SimplePort::addConnectionPoint(Positionable *port)
{
  ports.insert(port);
}

void SimplePort::removeConnectionPoint(Positionable *port)
{
  ports.erase(port);
}

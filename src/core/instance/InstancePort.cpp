#include "InstancePort.hpp"

#include "../component/InstanceAppearance.hpp"

#include <stdexcept>

InstancePort::InstancePort(Base *parent, ComponentPort *aCompPort, const Point &aOffset) :
  Base(parent, aOffset),
  compPort(aCompPort),
  connector(this, Point(0,0))
{
}

Connector &InstancePort::getConnector()
{
    return connector;
}

ComponentPort *InstancePort::getCompPort() const
{
  return compPort;
}

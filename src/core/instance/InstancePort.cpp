#include "InstancePort.hpp"

#include "../component/InstanceAppearance.hpp"

#include <stdexcept>

InstancePort::InstancePort(Instance *aInstance, ComponentPort *aCompPort, const Point &aOffset) :
  Positionable(aInstance, aOffset),
  owner(aInstance),
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

const std::string &InstancePort::getName() const
{
  return compPort->getName();
}

Instance *InstancePort::getInstance() const
{
  return owner;
}

void InstancePort::addConnectionPoint(Positionable *point)
{
  connector.addPoint(point);
}

void InstancePort::removeConnectionPoint(Positionable *point)
{
  (void)(point);
}

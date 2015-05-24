#include "InstancePort.hpp"

#include "../component/InstanceAppearance.hpp"

#include <stdexcept>

InstancePort::InstancePort(ComponentPort &aCompPort, const Point &aOffset, const Connector &aConnector) :
  compPort(aCompPort),
  offset(aOffset),
  connector(aConnector)
{
}

const Connector &InstancePort::getConnector() const
{
    return connector;
}

ComponentPort &InstancePort::getCompPort() const
{
  return compPort;
}

const Point &InstancePort::getOffset() const
{
  return offset;
}

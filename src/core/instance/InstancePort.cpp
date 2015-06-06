#include "InstancePort.hpp"

#include "../component/InstanceAppearance.hpp"
#include "../util/list.hpp"

#include <stdexcept>

InstancePort::InstancePort(Instance *aInstance, ComponentPort *aCompPort, const Point &aOffset) :
  RelativePosition(aOffset),
  owner(aInstance),
  compPort(aCompPort),
  connector(Point(0,0))
{
  precondition(aInstance != nullptr);

  replaceAnchor(aInstance);
  connector.replaceAnchor(this);
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

Side InstancePort::side() const
{
  return owner->getComponent()->sideOf(compPort);
}

void InstancePort::addConnectionPoint(RelativePosition *point)
{
  connector.addPoint(point);
}

void InstancePort::removeConnectionPoint(RelativePosition *point)
{
  (void)(point);
}

void InstancePort::accept(Visitor &visitor) const
{
  visitor.visit(*this);
}

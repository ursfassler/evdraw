#include "InstancePortFactory.hpp"

#include "../util/list.hpp"

#include <stdexcept>

InstancePort *InstancePortFactory::produce(ComponentPort &compPort, Instance &instance)
{
  Component *comp = instance.getComponent();
  ConnectorSide side;
  if (contains(comp->getPortLeft().begin(), comp->getPortLeft().end(), &compPort)) {
    side = ConnectorSide::Left;
  } else if (contains(comp->getPortRight().begin(), comp->getPortRight().end(), &compPort)) {
    side = ConnectorSide::Right;
  } else {
    throw std::invalid_argument("port not part of component");
  }

  return new InstancePort(compPort, instance, side);
}

void InstancePortFactory::dispose(InstancePort *port)
{
  delete port;
}

#include "InstancePortFactory.hpp"

#include "../util/list.hpp"

#include <stdexcept>

InstancePort *InstancePortFactory::produce(ComponentPort &compPort, Instance &instance)
{
  Component *comp = instance.getComponent();
  ConnectorSide side;
  if (contains(&compPort, comp->getPortLeft())) {
    side = ConnectorSide::Left;
  } else if (contains(&compPort, comp->getPortRight())) {
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

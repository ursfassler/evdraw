#include "InstancePortFactory.hpp"

#include "Connector.hpp"
#include "../component/InstanceAppearance.hpp"

#include "../util/list.hpp"

#include <stdexcept>

InstancePort *InstancePortFactory::produce(Instance *instance, ComponentPort *compPort)
{
  Component *comp = instance->getComponent();
  Side side;
  if (contains(comp->getPortLeft().begin(), comp->getPortLeft().end(), compPort)) {
    side = Side::Left;
  } else if (contains(comp->getPortRight().begin(), comp->getPortRight().end(), compPort)) {
    side = Side::Right;
  } else {
    throw std::invalid_argument("port not part of component");
  }

  const Point portOffset = getOffset(side, compPort);

  InstancePort *port = new InstancePort(instance, compPort, portOffset);

  const Point conOfs = connectorOffset(side);
  port->getConnector().setOffset(conOfs);

  return port;
}

Point InstancePortFactory::getOffset(Side side, const ComponentPort *compPort)
{
  switch (side) {
    case Side::Left: {
        return InstanceAppearance::leftPortPosition(compPort->getTopIndex());
      }
    case Side::Right: {
        return InstanceAppearance::rightPortPosition(compPort->getTopIndex());
      }
  }

  throw std::runtime_error("reached unreachable position");
}

Point InstancePortFactory::connectorOffset(Side side)
{
  const int sideMul = side == Side::Left ? -1 : 1;
  const PaperUnit offset = sideMul * InstanceAppearance::portWidth() / 2;
  return Point(offset, 0);
}


void InstancePortFactory::dispose(AbstractPort *port)
{
  delete port;
}

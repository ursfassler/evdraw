#include "InstancePortFactory.hpp"

#include "Connector.hpp"
#include "../component/InstanceAppearance.hpp"

#include "../util/list.hpp"

#include <stdexcept>

InstancePort *InstancePortFactory::produce(Base *parent, ComponentPort *compPort, Instance &instance)
{
  Component *comp = instance.getComponent();
  ConnectorSide side;
  if (contains(comp->getPortLeft().begin(), comp->getPortLeft().end(), compPort)) {
    side = ConnectorSide::Left;
  } else if (contains(comp->getPortRight().begin(), comp->getPortRight().end(), compPort)) {
    side = ConnectorSide::Right;
  } else {
    throw std::invalid_argument("port not part of component");
  }

  const Point portOffset = getOffset(side, compPort);

  InstancePort *port = new InstancePort(parent, compPort, portOffset);

  const Point conOfs = connectorOffset(side);
  port->getConnector().setOffset(conOfs);

  return port;
}

Point InstancePortFactory::getOffset(ConnectorSide side, const ComponentPort *compPort)
{
  switch (side) {
    case ConnectorSide::Left: {
        return InstanceAppearance::leftPortPosition(compPort->getTopIndex());
      }
    case ConnectorSide::Right: {
        return InstanceAppearance::rightPortPosition(compPort->getTopIndex());
      }
  }

  throw std::runtime_error("reached unreachable position");
}

Point InstancePortFactory::connectorOffset(ConnectorSide side)
{
  const int sideMul = side == ConnectorSide::Left ? -1 : 1;
  const PaperUnit offset = sideMul * InstanceAppearance::portWidth() / 2;
  return Point(offset, 0);
}


void InstancePortFactory::dispose(InstancePort *port)
{
  delete port;
}

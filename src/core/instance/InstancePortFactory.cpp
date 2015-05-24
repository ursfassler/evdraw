#include "InstancePortFactory.hpp"

#include "Connector.hpp"
#include "../component/InstanceAppearance.hpp"

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

  const Point portOffset = getOffset(side, compPort);
  const Point conOfs = connectorOffset(portOffset, side);
  Connector connector(conOfs);

  return new InstancePort(compPort, portOffset, connector);
}

Point InstancePortFactory::getOffset(ConnectorSide side, const ComponentPort &compPort)
{
  switch (side) {
    case ConnectorSide::Left: {
        const PaperUnit x = InstanceAppearance::leftPortXOffset();
        const PaperUnit y = InstanceAppearance::portYOffset(compPort.getTopIndex());
        return Point(x, y);
      }
    case ConnectorSide::Right: {
        const PaperUnit x = InstanceAppearance::rightPortXOffset();
        const PaperUnit y = InstanceAppearance::portYOffset(compPort.getTopIndex());
        return Point(x, y);
      }
  }

  throw std::runtime_error("reached unreachable position");
}

Point InstancePortFactory::connectorOffset(const Point &portOffset, ConnectorSide side)
{
  const int sideMul = side == ConnectorSide::Left ? -1 : 1;
  const PaperUnit offset = sideMul * InstanceAppearance::portWidth() / 2;
  return Point(portOffset.x + offset, portOffset.y);
}


void InstancePortFactory::dispose(InstancePort *port)
{
  delete port;
}

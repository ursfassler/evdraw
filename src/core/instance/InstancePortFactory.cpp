// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstancePortFactory.hpp"

#include "Connector.hpp"
#include "../component/InstanceAppearance.hpp"

#include "../util/list.hpp"

#include <stdexcept>

InstancePort *InstancePortFactory::produce(AbstractInstance *instance, ComponentPort *compPort)
{
  const Side side = compPort->side();
  const Point portOffset = getOffset(side, compPort);

  InstancePort *port = new InstancePort(instance, compPort, portOffset);

  const Point conOfs = connectorOffset(side);
  port->getConnector().setOffset(conOfs);

  return port;
}

///TODO: delete function, move functionality into InstancePort
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


void InstancePortFactory::dispose(InstancePort *port)
{
  delete port;
}

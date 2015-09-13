// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ConnectorFactory.hpp"

#include "../util/contract.hpp"


void ConnectorFactory::cleanup(Connector &connector)
{
  std::vector<RelativePosition *> points = connector.getPoints();
  for (RelativePosition *pos : points) {
    connector.removePoint(pos);
  }
}

void ConnectorFactory::dispose(Connector *connector)
{
  precondition(connector != nullptr);

  cleanup(*connector);

  delete connector;
}

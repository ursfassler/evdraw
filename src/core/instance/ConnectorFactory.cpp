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

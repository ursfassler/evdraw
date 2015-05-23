#include "InstancePort.hpp"

#include "../component/InstanceAppearance.hpp"

#include <stdexcept>

InstancePort::InstancePort(ComponentPort &aCompPort, Instance &aInstance, ConnectorSide aConnectorSide) :
  compPort(aCompPort),
  instance(aInstance),
  connectorSide(aConnectorSide),
  connections()
{
}

InstancePort::~InstancePort()
{
}

void InstancePort::addConnection(Connection *connection)
{
  connections.push_back(connection);
  updateConnectionPosition();
}

const std::vector<Connection *> &InstancePort::getConnections() const
{
  return connections;
}

ConnectorSide InstancePort::getConnectorSide() const
{
  return connectorSide;
}

ComponentPort &InstancePort::getCompPort() const
{
  return compPort;
}

PortPoint &InstancePort::getConnectedPoint(Connection *connection) const
{
  switch (connectorSide) {
    case ConnectorSide::Left:
      return connection->getEnd();
    case ConnectorSide::Right:
      return connection->getStart();
  }

  throw std::runtime_error("reached unreachable position");
}

void InstancePort::updateConnectionPosition() const
{
  for (size_t i = 0; i < connections.size(); i++) {
    Connection *con = connections[i];
    Endpoint &ep = getConnectedPoint(con);
    PaperUnit y = calcLocalConnectorY(i);
    ep.setY(getOffset().y + y);
    ep.setX(getOffset().x);
  }
}

PaperUnit InstancePort::calcLocalConnectorY(size_t idx) const
{
  const PaperUnit height = InstanceAppearance::portHeight();
  const PaperUnit offset = (idx+1) * height / (connections.size()+1);
  const PaperUnit pos = offset - height / 2;
  return pos;
}

Point InstancePort::getOffset() const
{
  switch (connectorSide) {
    case ConnectorSide::Left: {
        const PaperUnit x = InstanceAppearance::leftPortXOffset();
        const PaperUnit y = InstanceAppearance::leftPortYOffset(*instance.getComponent(), &compPort);
        return Point(x, y);
      }
    case ConnectorSide::Right: {
        const PaperUnit x = InstanceAppearance::rightPortXOffset();
        const PaperUnit y = InstanceAppearance::rightPortYOffset(*instance.getComponent(), &compPort);
        return Point(x, y);
      }
  }

  throw std::runtime_error("reached unreachable position");
}

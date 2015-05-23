#include "InstancePort.hpp"

#include <stdexcept>

InstancePort::InstancePort(PaperUnit aX, PaperUnit aY, ConnectorSide aConnectorSide) :
  x(aX),
  y(aY),
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

PaperUnit InstancePort::getX() const
{
  return x;
}

PaperUnit InstancePort::getY() const
{
  return y;
}

PaperUnit InstancePort::getHeight() const
{
  return height;
}

ConnectorSide InstancePort::getConnectorSide() const
{
  return connectorSide;
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
     ep.setY(getY() + y);
     ep.setX(getX());
  }
}

PaperUnit InstancePort::calcLocalConnectorY(size_t idx) const
{
  PaperUnit offset = (idx+1) * getHeight() / (connections.size()+1);
  PaperUnit pos = offset - getHeight() / 2;
  return pos;
}

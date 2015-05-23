#ifndef INSTANCEPORT_HPP
#define INSTANCEPORT_HPP

#include "Connection.hpp"
#include "Endpoint.hpp"
#include "types.hpp"

#include <vector>

class InstancePort
{
  public:
    InstancePort(PaperUnit aX, PaperUnit aY, ConnectorSide aConnectorSide);
    virtual ~InstancePort();

    void addConnection(Connection *connection);
    const std::vector<Connection *> &getConnections() const;
    PaperUnit getX() const;
    PaperUnit getY() const;
    PaperUnit getHeight() const;
    ConnectorSide getConnectorSide() const;

  private:
    PaperUnit x;
    PaperUnit y;
    const ConnectorSide connectorSide;
    const PaperUnit height = 10000;
    std::vector<Connection*> connections;
    PortPoint &getConnectedPoint(Connection *connection) const;
    void updateConnectionPosition() const;
    PaperUnit calcLocalConnectorY(size_t idx) const;

};

#endif // INSTANCEPORT_HPP

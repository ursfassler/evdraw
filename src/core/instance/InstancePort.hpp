#ifndef INSTANCEPORT_HPP
#define INSTANCEPORT_HPP

#include "../component/ComponentPort.hpp"
#include "../connection/Connection.hpp"
#include "../connection/Endpoint.hpp"
#include "../types.hpp"

#include "Instance.hpp"

#include <vector>

class InstancePort
{
  public:
    InstancePort(ComponentPort &compPort, Instance &instance, ConnectorSide aConnectorSide);
    virtual ~InstancePort();

    void addConnection(Connection *connection);
    const std::vector<Connection *> &getConnections() const;
    ConnectorSide getConnectorSide() const;
    ComponentPort &getCompPort() const;
    Point getOffset() const;

  private:
    ComponentPort &compPort;
    Instance &instance;
    const ConnectorSide connectorSide;
    std::vector<Connection*> connections;

    PortPoint &getConnectedPoint(Connection *connection) const;
    void updateConnectionPosition() const;
    PaperUnit calcLocalConnectorY(size_t idx) const;

};


#endif // INSTANCEPORT_HPP

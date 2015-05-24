#ifndef INSTANCEPORT_HPP
#define INSTANCEPORT_HPP

#include "Connector.hpp"

#include "../component/ComponentPort.hpp"
#include "../types.hpp"

#include <vector>

class InstancePort final
{
  public:
    InstancePort(ComponentPort &compPort, const Point &offset, const Connector &connector);

    const Point &getOffset() const;
    ComponentPort &getCompPort() const;
    const Connector &getConnector() const;

  private:
    ComponentPort &compPort;
    Point offset;
    Connector connector;

};


#endif // INSTANCEPORT_HPP

#ifndef INSTANCEPORT_HPP
#define INSTANCEPORT_HPP

#include "Connector.hpp"

#include "../component/ComponentPort.hpp"
#include "../types.hpp"
#include "../base/Base.hpp"

#include <vector>

class InstancePort final : public Base
{
  public:
    InstancePort(Base *parent, ComponentPort *compPort, const Point &offset);

    ComponentPort *getCompPort() const;
    Connector &getConnector();

  private:
    ComponentPort * const compPort;
    Connector connector;

};

#endif // INSTANCEPORT_HPP

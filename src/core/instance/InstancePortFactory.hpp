#ifndef INSTANCEPORTFACTORY_HPP
#define INSTANCEPORTFACTORY_HPP

#include "InstancePort.hpp"
#include "Instance.hpp"
#include "../component/Component.hpp"
#include "../component/ComponentPort.hpp"

class InstancePortFactory
{
  public:
    static InstancePort *produce(Base *parent, ComponentPort *compPort, Instance &instance);
    static void dispose(InstancePort *port);

  private:
    static Point getOffset(ConnectorSide side, const ComponentPort *compPort);
    static Point connectorOffset(ConnectorSide side);
};

#endif // INSTANCEPORTFACTORY_HPP

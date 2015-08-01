#ifndef INSTANCEPORTFACTORY_HPP
#define INSTANCEPORTFACTORY_HPP

#include "AbstractInstance.hpp"
#include "InstancePort.hpp"
#include "../component/Component.hpp"
#include "../component/ComponentPort.hpp"

class InstancePortFactory
{
  public:
    static InstancePort *produce(AbstractInstance *instance, ComponentPort *compPort);
    static void dispose(InstancePort *port);

  private:
    static Point getOffset(Side side, const ComponentPort *compPort);
    static Point connectorOffset(Side side);
};

#endif // INSTANCEPORTFACTORY_HPP

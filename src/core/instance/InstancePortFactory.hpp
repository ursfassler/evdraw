#ifndef INSTANCEPORTFACTORY_HPP
#define INSTANCEPORTFACTORY_HPP

#include "InstancePort.hpp"
#include "Instance.hpp"
#include "../component/Component.hpp"
#include "../component/ComponentPort.hpp"

class InstancePortFactory
{
  public:
    static InstancePort *produce(Instance *instance, ComponentPort *compPort);
    static void dispose(AbstractPort *port);

  private:
    static Point getOffset(Side side, const ComponentPort *compPort);
    static Point connectorOffset(Side side);
};

#endif // INSTANCEPORTFACTORY_HPP

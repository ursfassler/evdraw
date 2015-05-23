#ifndef INSTANCEPORTFACTORY_HPP
#define INSTANCEPORTFACTORY_HPP

#include "InstancePort.hpp"
#include "../component/Component.hpp"
#include "../component/ComponentPort.hpp"

class InstancePortFactory
{
  public:
    static InstancePort *produce(ComponentPort &compPort, Instance &instance);
    static void dispose(InstancePort *port);

};

#endif // INSTANCEPORTFACTORY_HPP

#include "InstanceFactory.hpp"

#include "InstancePortFactory.hpp"

#include "../util/contract.hpp"

Instance *InstanceFactory::produce(Component *component, const std::string &name, const Point &position)
{
  precondition(component != nullptr);

  Instance *instance = new Instance(name, position, component);

  for (ComponentPort *compPort : component->getPorts()) {
    InstancePort *instPort = InstancePortFactory::produce(instance, compPort);
    instance->addPort(instPort);
  }

  return instance;
}

void InstanceFactory::cleanup(Instance &instance)
{
  cleanupPort(instance.ports);
  postcondition(instance.ports.empty());
}

void InstanceFactory::dispose(Instance *instance)
{
  precondition(instance != nullptr);

  cleanup(*instance);
  delete instance;
}

void InstanceFactory::cleanupPort(std::vector<InstancePort *> &ports)
{
  for (InstancePort *port : ports) {
    InstancePortFactory::dispose(port);
  }
  ports.clear();
}

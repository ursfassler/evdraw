#include "InstanceFactory.hpp"

#include "InstancePortFactory.hpp"

#include "../util/contract.hpp"

Instance *InstanceFactory::produce(Component *component, const std::string &name, const Point &position)
{
  precondition(component != nullptr);

  Instance *instance = new Instance(name, position, component);

  for (ComponentPort *compPort : component->getPortLeft()) {
    //TODO use better suited produce
    InstancePort *instPort = InstancePortFactory::produce(instance, compPort);
    instance->addPort(instPort);
  }
  for (ComponentPort *compPort : component->getPortRight()) {
    //TODO use better suited produce
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

void InstanceFactory::cleanupPort(std::vector<AbstractPort *> &ports)
{
  for (AbstractPort *port : ports) {
    InstancePortFactory::dispose(port);
  }
  ports.clear();
}

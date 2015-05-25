#include "InstanceFactory.hpp"

#include "InstancePortFactory.hpp"

#include "../util/contract.hpp"

Instance *InstanceFactory::produce(Component *component, const std::string &name, const Point &position)
{
  precondition(component != nullptr);

  Instance *instance = new Instance(name, position, component);

  for (ComponentPort *compPort : component->getPortLeft()) {
    //TODO use better suited produce
    InstancePort *instPort = InstancePortFactory::produce(instance, compPort, *instance);
    instance->addInput(instPort);
  }
  for (ComponentPort *compPort : component->getPortRight()) {
    //TODO use better suited produce
    InstancePort *instPort = InstancePortFactory::produce(instance, compPort, *instance);
    instance->addOutput(instPort);
  }

  return instance;
}

void InstanceFactory::cleanup(Instance &instance)
{
  cleanupPort(instance.input);
  cleanupPort(instance.output);

  postcondition(instance.input.empty());
  postcondition(instance.output.empty());
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

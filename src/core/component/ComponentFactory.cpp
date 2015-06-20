#include "ComponentFactory.hpp"

#include "ComponentPort.hpp"
#include "../implementation/NullImplementation.hpp"
#include "../util/contract.hpp"

Component *ComponentFactory::produce(const std::string &name)
{
  return new Component(name, new NullImplementation());
}

Component *ComponentFactory::produce(const std::string &name, const std::vector<std::string> &inPort, const std::vector<std::string> &outPort)
{
  Component *comp = produce(name);

  for (const std::string &portName : inPort) {
    Slot *port = new Slot(portName);
    comp->addPortLeft(port);
  }
  for (const std::string &portName : outPort) {
    Signal *port = new Signal(portName);
    comp->addPortRight(port);
  }

  postcondition(comp != nullptr);
  postcondition(comp->getPortLeft().size() == inPort.size());
  postcondition(comp->getPortRight().size() == outPort.size());
  return comp;
}

void ComponentFactory::cleanup(Component &component)
{
  for (ComponentPort *port : component.portRight) {
    delete port;
  }
  component.portRight.clear();

  for (ComponentPort *port : component.portLeft) {
    delete port;
  }
  component.portLeft.clear();

  postcondition(component.portRight.empty());
  postcondition(component.portLeft.empty());
}

void ComponentFactory::dispose(Component *component)
{
  precondition(component != nullptr);

  cleanup(*component);
  delete component;
}

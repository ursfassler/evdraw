// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ComponentFactory.hpp"

#include "ComponentPort.hpp"
#include "../implementation/NullImplementation.hpp"
#include "../util/contract.hpp"
#include "../implementation/ImplementationFactory.hpp"

Component *ComponentFactory::produce(const std::string &name)
{
  return new Component(name, new NullImplementation());
}

static void addPorts(Component *comp, const std::vector<std::string> &names, PortType type)
{
  for (const std::string &portName : names) {
    ComponentPort *port = new ComponentPort(portName, type);
    comp->getPorts().add(port);
  }
}

Component *ComponentFactory::produce(const std::string &name, const std::vector<std::string> &inPort, const std::vector<std::string> &outPort)
{
  Component *comp = produce(name);
  addPorts(comp, inPort, PortType::Slot);
  addPorts(comp, outPort, PortType::Signal);

  postcondition(comp != nullptr);
  postcondition(comp->getPorts().size() == inPort.size() + outPort.size());
  return comp;
}

void ComponentFactory::cleanup(IComponent &icomponent)
{
  Component &component = *dynamic_cast<Component*>(&icomponent);  //TODO make it clean

  ImplementationFactory::dispose(component.implementation);
  component.implementation = nullptr;

  component.getPorts().clear();

  postcondition(component.getPorts().empty());
  postcondition(component.getImplementation() == nullptr);
}

void ComponentFactory::dispose(IComponent *component)
{
  precondition(component != nullptr);

  cleanup(*component);
  delete component;
}

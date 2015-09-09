// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "DefaultVisitor.hpp"

#include "../instance/Instance.hpp"
#include "../implementation/Composition.hpp"
#include "../component/Library.hpp"

void DefaultVisitor::visit(ComponentPort &)
{
}

void DefaultVisitor::visit(Component &component)
{
  for (ComponentPort *port : component.getPorts())
  {
    port->accept(*this);
  }
  component.getImplementation()->accept(*this);
}

void DefaultVisitor::visit(Instance &instance)
{
  for (AbstractPort *port : instance.getPorts())
  {
    port->accept(*this);
  }
}

void DefaultVisitor::visit(InstancePort &)
{
}

void DefaultVisitor::visit(Connection &)
{
}

void DefaultVisitor::visit(Composition &composition)
{
  for (Instance *instance : composition.getInstances())
  {
    instance->accept(*this);
  }
  for (Connection *connection : composition.getConnections())
  {
    connection->accept(*this);
  }
}

void DefaultVisitor::visit(NullImplementation &)
{
}

void DefaultVisitor::visit(Library &library)
{
  for (Component *component : library.getComponents())
  {
    component->accept(*this);
  }
}


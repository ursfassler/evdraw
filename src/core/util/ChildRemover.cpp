// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ChildRemover.hpp"

#include "../implementation/Composition.hpp"
#include "../instance/InstanceFactory.hpp"
#include "../connection/ConnectionFactory.hpp"

#include <set>

ChildRemover::ChildRemover(const Specification &aSpecification) :
  specification(aSpecification)
{
}

void ChildRemover::visit(Composition &composition)
{
  removeConnections(composition);
  removeInstances(composition);

  DefaultVisitor::visit(composition);
}

void ChildRemover::removeInstances(Composition &composition) const
{
  std::list<Instance*> removable = getSatisfied(composition.getInstances());
  for (Instance *instance : removable)
  {
    composition.removeInstance(instance);
    InstanceFactory::dispose(instance);
  }
}

void ChildRemover::removeConnections(Composition &composition) const
{
  std::list<Connection*> removable = getSatisfied(composition.getConnections());
  for (Connection *connection : removable)
  {
    composition.removeConnection(connection);
    ConnectionFactory::dispose(connection);
  }
}

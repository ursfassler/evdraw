// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ChildRemover.hpp"

#include "../implementation/Composition.hpp"
#include "../connection/ConnectionFactory.hpp"

#include <set>

ChildRemover::ChildRemover(const Specification &aSpecification) :
  specification(aSpecification)
{
}

void ChildRemover::visit(Composition &composition)
{
  deleteConnections(composition);
  deleteInstances(composition);

  DefaultVisitor::visit(composition);
}

void ChildRemover::deleteInstances(Composition &composition) const
{
  const auto removable = getSatisfied(composition.getInstances());
  for (auto *instance : removable)
  {
    composition.getInstances().remove(instance);
  }
}

void ChildRemover::deleteConnections(Composition &composition) const
{
  const auto removable = getSatisfied(composition.getConnections());
  for (Connection *connection : removable)
  {
    composition.getConnections().remove(connection);
  }
}

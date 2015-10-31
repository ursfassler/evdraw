// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "Composition.hpp"

#include "../connection/ConnectionFactory.hpp"
#include "../instance/InstanceFactory.hpp"
#include "../util/stdlist.hpp"
#include "../util/ChildRemover.hpp"
#include "../connection/ConnectionWithPortSpecification.hpp"
#include "../specification/OrSpecification.hpp"

#include <algorithm>
#include <cassert>

Composition::Composition(ICompositionInstance *aSelfInstance) :
  selfInstance{aSelfInstance},
  instances{InstanceFactory::dispose},
  connections{ConnectionFactory::dispose}
{
  precondition(aSelfInstance != nullptr);
  selfInstance->getPorts().registerObserver(this);
  instances.registerObserver(this);
}

Composition::~Composition()
{
  instances.unregisterObserver(this);
  precondition(connections.empty());
  precondition(connectionUnderConstruction == nullptr);
  precondition(instances.empty());
  precondition(selfInstance == nullptr);
}

ImplementationType Composition::getType() const
{
  return ImplementationType::Composition;
}

ICompositionInstance *Composition::getSelfInstance() const
{
  return selfInstance;
}

const List<IComponentInstance> &Composition::getInstances() const
{
  return instances;
}

List<IComponentInstance> &Composition::getInstances()
{
  return instances;
}

void Composition::added(IComponentInstance *instance)
{
  instance->getPorts().registerObserver(this);
}

void Composition::removed(IComponentInstance *instance)
{
  OrSpecification spec;
  for (IPort *port : instance->getPorts()) {
    spec.add(new ConnectionWithPortSpecification(port));
  }

  ChildRemover remover(spec);
  accept(remover);

  instance->getPorts().unregisterObserver(this);
}

IComponentInstance *Composition::getInstance(const std::string &name) const
{
  auto predicate = [&](const IComponentInstance *itr){
    return itr->getName() == name;
  };
  return instances.get(predicate);
}

const List<Connection> &Composition::getConnections() const
{
  return connections;
}

List<Connection> &Composition::getConnections()
{
  return connections;
}

void Composition::startConnectionConstruction(IPort *startPort, IPort *endPort)
{
  precondition(!hasConnectionUnderConstruction());
  precondition(startPort != nullptr);
  precondition(endPort != nullptr);

  connectionUnderConstruction = ConnectionFactory::produceConstruction(startPort, endPort);

  checkInvariant();
  notify(&CompositionObserver::addConnectionUnderConstruction, connectionUnderConstruction);
}

void Composition::finishConnectionConstruction(IPort *end)
{
  precondition(hasConnectionUnderConstruction());
  precondition(end != nullptr);

  connectionUnderConstruction->replaceEndPort(end);
  Connection *connection = connectionUnderConstruction;
  connectionUnderConstruction = nullptr;

  notify(&CompositionObserver::finishConnectionUnderConstruction, connection);

  connections.add(connection);

  postcondition(!hasConnectionUnderConstruction());
}

bool Composition::hasConnectionUnderConstruction() const
{
  return connectionUnderConstruction != nullptr;
}

Connection *Composition::getConnectionUnderConstruction() const
{
  return connectionUnderConstruction;
}

void Composition::removed(InstancePort *port)
{
  ConnectionWithPortSpecification spec(port);
  ChildRemover remover(spec);
  accept(remover);
}

void Composition::checkInvariant()
{
}

void Composition::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

void Composition::accept(ConstVisitor &visitor) const
{
  visitor.visit(*this);
}


CompositionObserver::~CompositionObserver()
{
}

void CompositionObserver::addConnectionUnderConstruction(Connection *)
{
}

void CompositionObserver::finishConnectionUnderConstruction(Connection *)
{
}

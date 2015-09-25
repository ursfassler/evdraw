// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "Composition.hpp"

#include "../connection/ConnectionFactory.hpp"
#include "../instance/InstanceFactory.hpp"
#include "../util/list.hpp"
#include "../util/ChildRemover.hpp"
#include "../connection/ConnectionWithPortSpecification.hpp"
#include "../specification/OrSpecification.hpp"

#include <algorithm>
#include <cassert>

Composition::Composition(ICompositionInstance *aSelfInstance) :
  selfInstance{aSelfInstance},
  instances{},
  connections{}
{
  precondition(aSelfInstance != nullptr);
}

Composition::~Composition()
{
  const std::list<Connection *> connections = getConnections();
  for (Connection *connection : connections) {
    deleteConnection(connection);
  }

  if (connectionUnderConstruction != nullptr) {
    ConnectionFactory::dispose(connectionUnderConstruction);
    connectionUnderConstruction = nullptr;
  }

  const std::list<Instance *> instances = getInstances();
  for (Instance *instance : instances) {
    deleteInstance(instance);
  }

  delete selfInstance;

  assert(getInstances().empty());
  assert(getConnections().empty());
  assert(connectionUnderConstruction == nullptr);
}

ICompositionInstance *Composition::getSelfInstance() const
{
  return selfInstance;
}

const std::list<Instance *> &Composition::getInstances() const
{
  return instances;
}

void Composition::addInstance(Instance *instance)
{
  instance->ObserverCollection<InstanceObserver>::registerObserver(this);
  instances.push_back(instance);
  notify(&CompositionObserver::instanceAdded, instance);
}

void Composition::deleteInstance(Instance *instance)
{
  OrSpecification spec;
  for (AbstractPort *port : instance->getPorts()) {
    spec.add(new ConnectionWithPortSpecification(port));
  }

  ChildRemover remover(spec);
  accept(remover);

  instances.remove(instance);
  instance->ObserverCollection<InstanceObserver>::unregisterObserver(this);
  notify(&CompositionObserver::instanceRemoved, instance);

  InstanceFactory::dispose(instance);
}

Instance *Composition::getInstance(const std::string &name) const
{
  auto predicate = [&](Instance *itr){
    return itr->getName() == name;
  };
  return listGet<Instance*>(instances.begin(), instances.end(), predicate);
}

const std::list<Connection *> &Composition::getConnections() const
{
  return connections;
}

void Composition::addConnection(Connection *connection)
{
  connections.push_back(connection);
  notify(&CompositionObserver::connectionAdded, connection);
}

void Composition::deleteConnection(Connection *connection)
{
  connections.remove(connection);
  notify(&CompositionObserver::connectionRemoved, connection);

  ConnectionFactory::dispose(connection);
}

void Composition::startConnectionConstruction(AbstractPort *startPort, AbstractPort *endPort)
{
  precondition(!hasConnectionUnderConstruction());
  precondition(startPort != nullptr);
  precondition(endPort != nullptr);

  connectionUnderConstruction = ConnectionFactory::produceConstruction(startPort, endPort);

  checkInvariant();
  notify(&CompositionObserver::addConnectionUnderConstruction, connectionUnderConstruction);
}

void Composition::finishConnectionConstruction(AbstractPort *end)
{
  precondition(hasConnectionUnderConstruction());
  precondition(end != nullptr);

  connectionUnderConstruction->replaceEndPort(end);
  Connection *connection = connectionUnderConstruction;
  connectionUnderConstruction = nullptr;

  notify(&CompositionObserver::finishConnectionUnderConstruction, connection);

  addConnection(connection);

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

void Composition::portDeleted(InstancePort *port)
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

void CompositionObserver::instanceAdded(Instance *)
{
}

void CompositionObserver::instanceRemoved(Instance *)
{
}

void CompositionObserver::connectionAdded(Connection *)
{
}

void CompositionObserver::connectionRemoved(Connection *)
{
}

void CompositionObserver::addConnectionUnderConstruction(Connection *)
{
}

void CompositionObserver::finishConnectionUnderConstruction(Connection *)
{
}

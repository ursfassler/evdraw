#include "Composition.hpp"

#include "../connection/ConnectionFactory.hpp"
#include "../instance/InstanceFactory.hpp"
#include "../util/list.hpp"

#include <algorithm>
#include <cassert>

Composition::Composition() :
  instances(),
  connections()
{
}

Composition::~Composition()
{
  for (Connection *connection : connections) {
    ConnectionFactory::dispose(connection);
  }
  connections.clear();

  if (connectionUnderConstruction != nullptr) {
    ConnectionFactory::dispose(connectionUnderConstruction);
    connectionUnderConstruction = nullptr;
  }

  for (Instance *instance : instances) {
    InstanceFactory::dispose(instance);
  }
  instances.clear();

  assert(instances.empty());
  assert(connections.empty());
  assert(connectionUnderConstruction == nullptr);
}

const std::list<Instance *> &Composition::getInstances() const
{
  return instances;
}

void Composition::addInstance(Instance *instance)
{
  instances.push_back(instance);
  notify(&CompositionObserver::instanceAdded, instance);
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

void Composition::removeConnection(Connection *connection)
{
  connections.remove(connection);
  notify(&CompositionObserver::connectionRemoved, connection);
}

void Composition::startConnectionConstruction(InstancePort *startPort, AbstractPort *endPort)
{
  precondition(!hasConnectionUnderConstruction());
  precondition(startPort != nullptr);
  precondition(endPort != nullptr);

  connectionUnderConstruction = ConnectionFactory::produceConstruction(startPort, endPort);

  checkInvariant();
  notify(&CompositionObserver::addConnectionUnderConstruction, connectionUnderConstruction);
}

void Composition::finishConnectionConstruction(InstancePort *end)
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

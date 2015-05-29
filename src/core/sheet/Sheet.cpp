#include "Sheet.hpp"

#include "../connection/ConnectionFactory.hpp"
#include "../instance/InstanceFactory.hpp"

#include <cassert>

Sheet::Sheet()
{
}

Sheet::~Sheet()
{
  for (ConnectionBase *connection : connections) {
    ConnectionFactory::dispose(connection);
  }
  connections.clear();

  for (Instance *instance : instances) {
    InstanceFactory::dispose(instance);
  }
  instances.clear();

  assert(instances.empty());
  assert(connections.empty());
}

const std::vector<Instance *> &Sheet::getInstances() const
{
  return instances;
}

void Sheet::addInstance(Instance *instance)
{
  instances.push_back(instance);
  notify(&SheetObserver::instanceAdded, instance);
}

const std::vector<Connection *> &Sheet::getConnections() const
{
  return connections;
}

void Sheet::addConnection(Connection *connection)
{
  connections.push_back(connection);
  notify(&SheetObserver::connectionAdded, connection);
}

PartialConnectionFromStart *Sheet::getConnectionUnderConstruction() const
{
  return connectionUnderConstruction;
}

void Sheet::setConnectionUnderConstruction(PartialConnectionFromStart *value)
{
  precondition(value != nullptr);

  if (connectionUnderConstruction != nullptr) {
    PartialConnectionFromStart  *old = connectionUnderConstruction;
    connectionUnderConstruction = nullptr;
    notify(&SheetObserver::abortConnectionUnderConnstruction, old);
    ConnectionFactory::dispose(old);
  }

  connectionUnderConstruction = value;
  notify(&SheetObserver::addConnectionUnderConnstruction, value);
}

#include "Sheet.hpp"

#include "../connection/ConnectionFactory.hpp"
#include "../instance/InstanceFactory.hpp"

#include <cassert>

Sheet::Sheet() :
  instances(),
  connections()
{
}

Sheet::~Sheet()
{
  for (Connection *connection : connections) {
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

bool Sheet::hasConnectionUnderConstruction() const
{
  return connectionUnderConstruction != nullptr;
}

void Sheet::removeConnectionUnderConstruction()
{
  Connection  *old = connectionUnderConstruction;
  connectionUnderConstruction = nullptr;
  rootPort = nullptr;
  notify(&SheetObserver::removeConnectionUnderConnstruction, old);

  checkInvariant();
}

Connection *Sheet::getConnectionUnderConstruction() const
{
  return connectionUnderConstruction;
}

InstancePort *Sheet::getRootPort() const
{
  return rootPort;
}

void Sheet::setConnectionUnderConstruction(Connection *value, InstancePort *rootPort)
{
  precondition(!hasConnectionUnderConstruction());
  precondition(value != nullptr);
  precondition(rootPort != nullptr);

  connectionUnderConstruction = value;
  this->rootPort = rootPort;
  notify(&SheetObserver::addConnectionUnderConnstruction, value);

  checkInvariant();
}

void Sheet::checkInvariant()
{
  invariant((rootPort == nullptr) == (connectionUnderConstruction == nullptr));
}


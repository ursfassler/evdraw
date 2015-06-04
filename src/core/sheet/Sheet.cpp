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

void Sheet::startConnectionConstruction(InstancePort *startPort, AbstractPort *endPort)
{
  precondition(!hasConnectionUnderConstruction());
  precondition(startPort != nullptr);
  precondition(endPort != nullptr);

  connectionUnderConstruction = ConnectionFactory::produceConstruction(startPort, endPort);

  checkInvariant();
  notify(&SheetObserver::addConnectionUnderConstruction, connectionUnderConstruction);
}

void Sheet::finishConnectionConstruction(InstancePort *end)
{
  precondition(hasConnectionUnderConstruction());
  precondition(end != nullptr);

  end->getConnector().addPoint(connectionUnderConstruction->getPoints().back());
  Connection *connection = connectionUnderConstruction;
  connectionUnderConstruction = nullptr;

  notify(&SheetObserver::finishConnectionUnderConstruction, connection);

  addConnection(connection);
}

bool Sheet::hasConnectionUnderConstruction() const
{
  return connectionUnderConstruction != nullptr;
}

Connection *Sheet::getConnectionUnderConstruction() const
{
  return connectionUnderConstruction;
}

void Sheet::checkInvariant()
{
}


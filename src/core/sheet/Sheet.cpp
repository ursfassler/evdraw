#include "Sheet.hpp"

#include "../connection/ConnectionFactory.hpp"

#include <cassert>

Sheet::Sheet()
{
}

Sheet::~Sheet()
{
  for (Instance *instance : instances) {
    delete instance;
  }
  instances.clear();

  for (Connection *connection : connections) {
    ConnectionFactory::dispose(connection);
  }
  connections.clear();

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
}

const std::vector<Connection *> &Sheet::getConnections() const
{
  return connections;
}

void Sheet::addConnection(Connection *connection)
{
  connections.push_back(connection);
}

#include "Sheet.hpp"

#include "../connection/ConnectionFactory.hpp"
#include "../instance/InstanceFactory.hpp"

#include <cassert>

Sheet::Sheet()
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
}

const std::vector<Connection *> &Sheet::getConnections() const
{
  return connections;
}

void Sheet::addConnection(Connection *connection)
{
  connections.push_back(connection);
}

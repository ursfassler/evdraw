#ifndef SHEET_HPP
#define SHEET_HPP

#include "../instance/Instance.hpp"
#include "../connection/Connection.hpp"

#include <vector>

class Sheet final
{
  public:
    Sheet();
    ~Sheet();

    const std::vector<Instance *> &getInstances() const;
    void addInstance(Instance *instance);

    const std::vector<Connection *> &getConnections() const;
    void addConnection(Connection *connection);

  private:
    std::vector<Instance *> instances;
    std::vector<Connection *> connections;
};

#endif // SHEET_HPP

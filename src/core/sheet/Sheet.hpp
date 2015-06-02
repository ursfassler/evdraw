#ifndef SHEET_HPP
#define SHEET_HPP

#include "../instance/Instance.hpp"
#include "../instance/InstancePort.hpp"
#include "../connection/Connection.hpp"
#include "../util/Observer.hpp"

#include <vector>

class SheetObserver
{
  public:
    virtual ~SheetObserver(){}
    virtual void instanceAdded(Instance *instance){ (void)(instance); }
    virtual void connectionAdded(Connection *connection){ (void)(connection); }
    virtual void addConnectionUnderConstruction(Connection *connection){ (void)(connection); }
    virtual void finishConnectionUnderConstruction(Connection *connection){ (void)(connection); }
};

class Sheet final : public ObserverCollection<SheetObserver>
{
  public:
    Sheet();
    ~Sheet();

    Sheet(const Sheet &) = delete;
    bool operator=(const Sheet &) = delete;

    const std::vector<Instance *> &getInstances() const;
    void addInstance(Instance *instance);

    const std::vector<Connection *> &getConnections() const;
    void addConnection(Connection *connection);

    void startConnectionConstruction(InstancePort *start);
    void finishConnectionConstruction(InstancePort *end);
    bool hasConnectionUnderConstruction() const;
    Connection *getConnectionUnderConstruction() const;

  private:
    Connection  *connectionUnderConstruction = nullptr;
    std::vector<Instance *> instances;
    std::vector<Connection *> connections;

    void checkInvariant();

};

#endif // SHEET_HPP

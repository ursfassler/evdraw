#ifndef SHEET_HPP
#define SHEET_HPP

#include "../instance/Instance.hpp"
#include "../connection/Connection.hpp"
#include "../util/Observer.hpp"

#include <vector>

class SheetObserver
{
  public:
    virtual ~SheetObserver(){}
    virtual void instanceAdded(Instance *instance){ (void)(instance); }
    virtual void connectionAdded(Connection *connection){ (void)(connection); }
    virtual void addConnectionUnderConnstruction(ConstructionConnection *connection){ (void)(connection); }
    virtual void removeConnectionUnderConnstruction(ConstructionConnection *connection){ (void)(connection); }
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

    bool hasConnectionUnderConstruction() const;
    ConstructionConnection *getConnectionUnderConstruction() const;
    InstancePort *getRootPort() const;
    void setConnectionUnderConstruction(ConstructionConnection *value, InstancePort *rootPort);
    void removeConnectionUnderConstruction();

  private:
    ConstructionConnection  *connectionUnderConstruction = nullptr;
    InstancePort *rootPort = nullptr;
    std::vector<Instance *> instances;
    std::vector<Connection *> connections;

    void checkInvariant();

};

#endif // SHEET_HPP

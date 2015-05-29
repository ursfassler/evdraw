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
    virtual void addConnectionUnderConnstruction(PartialConnectionFromStart *connection){ (void)(connection); }
    virtual void abortConnectionUnderConnstruction(PartialConnectionFromStart *connection){ (void)(connection); }
};

class Sheet final : public ObserverCollection<SheetObserver>
{
  public:
    Sheet();
    ~Sheet();

    const std::vector<Instance *> &getInstances() const;
    void addInstance(Instance *instance);

    const std::vector<Connection *> &getConnections() const;
    void addConnection(Connection *connection);

    PartialConnectionFromStart *getConnectionUnderConstruction() const;
    void setConnectionUnderConstruction(PartialConnectionFromStart *value);

  private:
    PartialConnectionFromStart  *connectionUnderConstruction = nullptr;
    std::vector<Instance *> instances;
    std::vector<Connection *> connections;
};

#endif // SHEET_HPP

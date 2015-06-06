#ifndef SHEET_HPP
#define SHEET_HPP

#include "../instance/Instance.hpp"
#include "../instance/InstancePort.hpp"
#include "../connection/Connection.hpp"
#include "../util/Observer.hpp"
#include "../visitor/Visitor.hpp"

#include <list>

class SheetObserver
{
  public:
    virtual ~SheetObserver(){}
    virtual void instanceAdded(Instance *instance){ (void)(instance); }
    virtual void connectionAdded(Connection *connection){ (void)(connection); }
    virtual void addConnectionUnderConstruction(Connection *connection){ (void)(connection); }
    virtual void finishConnectionUnderConstruction(Connection *connection){ (void)(connection); }
};

class Sheet final : public ObserverCollection<SheetObserver>, public VisitorClient
{
  public:
    Sheet();
    ~Sheet();

    Sheet(const Sheet &) = delete;
    bool operator=(const Sheet &) = delete;

    const std::list<Instance *> &getInstances() const;
    void addInstance(Instance *instance);

    const std::list<Connection *> &getConnections() const;
    void addConnection(Connection *connection);
    void removeConnection(Connection *connection);

    void startConnectionConstruction(InstancePort *startPort, AbstractPort *endPort);
    void finishConnectionConstruction(InstancePort *end);
    bool hasConnectionUnderConstruction() const;
    Connection *getConnectionUnderConstruction() const;

    void accept(Visitor &visitor) const;

  private:
    Connection  *connectionUnderConstruction = nullptr;
    std::list<Instance *> instances;
    std::list<Connection *> connections;

    void checkInvariant();

};

#endif // SHEET_HPP

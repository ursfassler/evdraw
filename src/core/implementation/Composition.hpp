#ifndef COMPOSITION_HPP
#define COMPOSITION_HPP

#include "../instance/Instance.hpp"
#include "../instance/InstancePort.hpp"
#include "../connection/Connection.hpp"
#include "../util/Observer.hpp"
#include "../visitor/ConstVisitor.hpp"
#include "../component/AbstractImplementation.hpp"

#include <list>

class CompositionObserver
{
  public:
    virtual ~CompositionObserver()
    {
    }

    virtual void instanceAdded(Instance *instance)
    {
      (void)(instance);
    }

    virtual void instanceRemoved(Instance *instance)
    {
      (void)(instance);
    }

    virtual void connectionAdded(Connection *connection)
    {
      (void)(connection);
    }

    virtual void connectionRemoved(Connection *connection)
    {
      (void)(connection);
    }

    virtual void addConnectionUnderConstruction(Connection *connection)
    {
      (void)(connection);
    }

    virtual void finishConnectionUnderConstruction(Connection *connection)
    {
      (void)(connection);
    }
};

class Composition final : public AbstractImplementation, public ObserverCollection<CompositionObserver>, public InstanceObserver
{
  public:
    Composition();
    ~Composition();

    Composition(const Composition &) = delete;
    bool operator=(const Composition &) = delete;

    const std::list<Instance *> &getInstances() const;
    void addInstance(Instance *instance);
    void removeInstance(Instance *instance);
    Instance *getInstance(const std::string &name) const;

    const std::list<Connection *> &getConnections() const;
    void addConnection(Connection *connection);
    void removeConnection(Connection *connection);

    void startConnectionConstruction(AbstractPort *startPort, AbstractPort *endPort);
    void finishConnectionConstruction(AbstractPort *end);
    bool hasConnectionUnderConstruction() const;
    Connection *getConnectionUnderConstruction() const;

    void portDeleted(AbstractPort *port);

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

  private:
    Connection  *connectionUnderConstruction = nullptr;
    std::list<Instance *> instances;
    std::list<Connection *> connections;

    void checkInvariant();

};

#endif

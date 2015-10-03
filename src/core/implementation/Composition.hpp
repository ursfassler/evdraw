// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPOSITION_HPP
#define COMPOSITION_HPP

#include "CompositionInstance.hpp"
#include "../instance/Instance.hpp"
#include "../instance/InstancePort.hpp"
#include "../connection/Connection.hpp"
#include "../util/Observer.hpp"
#include "../visitor/ConstVisitor.hpp"
#include "../component/IImplementation.hpp"

#include <list>

class CompositionObserver
{
  public:
    virtual ~CompositionObserver();
    virtual void instanceAdded(Instance *instance);
    virtual void instanceRemoved(Instance *instance);
    virtual void connectionAdded(Connection *connection);
    virtual void connectionRemoved(Connection *connection);
    virtual void addConnectionUnderConstruction(Connection *connection);
    virtual void finishConnectionUnderConstruction(Connection *connection);
};

class IComposition
{
  public:
    virtual ~IComposition(){}
};

class CompositionFactory;

class Composition final :
    public IComposition,
    public IImplementation,
    public ObserverCollection<CompositionObserver>,
    private InstanceObserver
{
  public:
    Composition(ICompositionInstance *selfInstance);
    ~Composition();

    Composition(const Composition &) = delete;
    bool operator=(const Composition &) = delete;

    ICompositionInstance *getSelfInstance() const;

    const std::list<Instance *> &getInstances() const;
    void addInstance(Instance *instance);
    void deleteInstance(Instance *instance);
    Instance *getInstance(const std::string &name) const;

    const std::list<Connection *> &getConnections() const;
    void addConnection(Connection *connection);
    void deleteConnection(Connection *connection);

    void startConnectionConstruction(IPort *startPort, IPort *endPort);
    void finishConnectionConstruction(IPort *end);
    bool hasConnectionUnderConstruction() const;
    Connection *getConnectionUnderConstruction() const;

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

  private:
    Connection  *connectionUnderConstruction = nullptr;
    ICompositionInstance *selfInstance;
    std::list<Instance *> instances;
    std::list<Connection *> connections;

    void checkInvariant();

    void portDeleted(IPort *port) override;

    friend CompositionFactory;

};

#endif

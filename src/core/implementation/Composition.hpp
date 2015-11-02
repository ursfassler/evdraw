// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPOSITION_HPP
#define COMPOSITION_HPP

#include "IComposition.hpp"
#include "CompositionInstance.hpp"
#include "../util/List.hpp"
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
    virtual void addConnectionUnderConstruction(Connection *connection);
    virtual void finishConnectionUnderConstruction(Connection *connection);
};

class CompositionFactory;

class Composition final :
    public IComposition,
    public IImplementation,
    public ObserverCollection<CompositionObserver>,
    private ListObserver<IComponentInstance>,
    private ListObserver<InstancePort>
{
  public:
    Composition(ICompositionInstance *selfInstance);
    ~Composition();

    Composition(const Composition &) = delete;
    bool operator=(const Composition &) = delete;

    ImplementationType getType() const override final;

    ICompositionInstance *getSelfInstance() const;

    const List<IComponentInstance> &getInstances() const;
    List<IComponentInstance> &getInstances();
    IComponentInstance *getInstance(const std::string &name) const;

    const List<Connection> &getConnections() const;
    List<Connection> &getConnections();

    void startConnectionConstruction(IPort *startPort, IPort *endPort);
    void finishConnectionConstruction(IPort *end);
    bool hasConnectionUnderConstruction() const;
    Connection *getConnectionUnderConstruction() const;

    void accept(Visitor &visitor) override final;
    void accept(ConstVisitor &visitor) const override final;

  private:
    Connection  *connectionUnderConstruction = nullptr;
    ICompositionInstance *selfInstance;
    List<IComponentInstance> instances;
    List<Connection> connections;

    void checkInvariant();

    void added(InstancePort *) override {}
    void removed(InstancePort *port) override;
    void added(IComponentInstance *instance) override;
    void removed(IComponentInstance* instance) override;

    friend CompositionFactory;

};

#endif

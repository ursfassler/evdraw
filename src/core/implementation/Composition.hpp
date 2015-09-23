// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

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
    virtual ~CompositionObserver();
    virtual void instanceAdded(Instance *instance);
    virtual void instanceRemoved(Instance *instance);
    virtual void connectionAdded(Connection *connection);
    virtual void connectionRemoved(Connection *connection);
    virtual void addConnectionUnderConstruction(Connection *connection);
    virtual void finishConnectionUnderConstruction(Connection *connection);
};

class Composition final :
    public AbstractImplementation,
    public ObserverCollection<CompositionObserver>,
    public InstanceObserver
{
  public:
    Composition();
    ~Composition();

    Composition(const Composition &) = delete;
    bool operator=(const Composition &) = delete;

    PaperUnit getHeight() const;
    void setHeight(PaperUnit value);
    PaperUnit getWidth() const;
    void setWidth(PaperUnit value);

    const std::list<Instance *> &getInstances() const;
    void addInstance(Instance *instance);
    void deleteInstance(Instance *instance);
    Instance *getInstance(const std::string &name) const;

    const std::list<Connection *> &getConnections() const;
    void addConnection(Connection *connection);
    void deleteConnection(Connection *connection);

    void startConnectionConstruction(AbstractPort *startPort, AbstractPort *endPort);
    void finishConnectionConstruction(AbstractPort *end);
    bool hasConnectionUnderConstruction() const;
    Connection *getConnectionUnderConstruction() const;

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

  protected:
    void portDeleted(InstancePort *port);

  private:
    PaperUnit height = 0;
    PaperUnit width = 0;
    Connection  *connectionUnderConstruction = nullptr;
    std::list<Instance *> instances;
    std::list<Connection *> connections;

    void checkInvariant();

};

#endif

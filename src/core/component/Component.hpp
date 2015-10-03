// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "ComponentPort.hpp"
#include "IImplementation.hpp"
#include "../types.hpp"
#include "../visitor/VisitorClient.hpp"
#include "../util/Observer.hpp"

#include <vector>
#include <string>

class ComponentFactory;

class ComponentObserver
{
  public:
    virtual ~ComponentObserver();

    virtual void portAdded(ComponentPort *port);
    virtual void portDeleted(ComponentPort *port);
    virtual void maxPortCountChanged();
    virtual void nameChanged(const std::string &name);
};

class IComponent:
    //TODO move ObserverCollection out of interface
    public ObserverCollection<ComponentObserver>
{
  public:
    virtual ~IComponent(){}

    virtual const std::string &getName() const = 0;

    virtual const std::vector<ComponentPort *> &getPorts() const = 0;
    virtual Side portSide(PortType type) const = 0;

};

class Component final :
    public IComponent,
    public VisitorClient,
//    public ObserverCollection<ComponentObserver>,
    private ComponentPortObserver
{
  public:
    Component(const std::string &name, IImplementation *implementation);
    ~Component();

    Component(const Component &) = delete;
    Component operator=(const Component &) = delete;

    void addPort(ComponentPort *port);
    void deletePort(ComponentPort *port);
    const std::vector<ComponentPort *> &getPorts() const override;
    ComponentPort *getPort(const std::string &name) const;

    Side portSide(PortType type) const override final;

    size_t maxPortCount() const;

    const std::string &getName() const override;
    void setName(const std::string &value);

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

    IImplementation *getImplementation() const;
    void setImplementation(IImplementation *value);

  private:
    std::string name;
    std::vector<ComponentPort *> ports;

    IImplementation *implementation;

    void updateTopIndex();

    void typeChanged(PortType);

    friend ComponentFactory;

};

#endif // COMPONENT_HPP

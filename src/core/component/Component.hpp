// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "ComponentPort.hpp"
#include "IImplementation.hpp"
#include "../types.hpp"
#include "../util/List.hpp"
#include "../visitor/VisitorClient.hpp"
#include "../util/Observer.hpp"

#include <vector>
#include <string>

class ComponentFactory;

class ComponentObserver
{
  public:
    virtual ~ComponentObserver();

    virtual void maxPortCountChanged();
    virtual void nameChanged(const std::string &name);
};

class IComponent:
    public VisitorClient,
    //TODO move ObserverCollection out of interface
    public ObserverCollection<ComponentObserver>
{
  public:
    virtual ~IComponent(){}

    virtual const std::string &getName() const = 0;
    virtual void setName(const std::string &value) = 0;

    virtual const List<ComponentPort> &getPorts() const = 0;
    virtual List<ComponentPort> &getPorts() = 0;
    virtual Side portSide(PortType type) const = 0;

    virtual size_t maxPortCount() const = 0;

    virtual IImplementation *getImplementation() const = 0;

};

class Component final :
    public IComponent,
    private ComponentPortObserver,
    private ListObserver<ComponentPort>
{
  public:
    Component(const std::string &name, IImplementation *implementation);
    ~Component();

    Component(const Component &) = delete;
    Component operator=(const Component &) = delete;

    const List<ComponentPort> &getPorts() const override final;
    List<ComponentPort> &getPorts() override final;
    ComponentPort *getPort(const std::string &name) const;

    Side portSide(PortType type) const override final;

    size_t maxPortCount() const override final;

    const std::string &getName() const override final;
    void setName(const std::string &value) override final;

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

    IImplementation *getImplementation() const override final;
    void setImplementation(IImplementation *value);

  private:
    std::string name;
    List<ComponentPort> ports;
    size_t oldCount = 0;

    IImplementation *implementation;

    void updateTopIndex();

    void typeChanged(PortType) override;

    void added(ComponentPort* port) override;
    void removed(ComponentPort* port) override;

    friend ComponentFactory;

};

#endif // COMPONENT_HPP

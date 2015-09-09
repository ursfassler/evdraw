// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "ComponentPort.hpp"
#include "AbstractImplementation.hpp"
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
    virtual void heightChanged();
    virtual void nameChanged(const std::string &name);
};

class Component final :
    public VisitorClient,
    public ObserverCollection<ComponentObserver>,
    private ComponentPortObserver
{
  public:
    Component(const std::string &name, AbstractImplementation *implementation);
    ~Component();

    Component(const Component &) = delete;
    Component operator=(const Component &) = delete;

    void addPort(ComponentPort *port);
    void deletePort(ComponentPort *port);
    const std::vector<ComponentPort *> &getPorts() const;
    ComponentPort *getPort(const std::string &name) const;

    size_t height() const;

    const std::string &getName() const;
    void setName(const std::string &value);

    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

    AbstractImplementation *getImplementation() const;
    void setImplementation(AbstractImplementation *value);

  private:
    std::string name;
    std::vector<ComponentPort *> ports;

    AbstractImplementation *implementation;

    void updateTopIndex();

    void typeChanged(PortType);

    friend ComponentFactory;

};

#endif // COMPONENT_HPP

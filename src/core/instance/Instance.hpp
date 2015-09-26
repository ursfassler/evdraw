// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include "../component/Component.hpp"
#include "../util/Observer.hpp"
#include "../Point.hpp"

#include "AbstractInstance.hpp"
#include "InstancePort.hpp"
#include "../visitor/VisitorClient.hpp"

#include <string>
#include <vector>

class InstanceFactory;

class InstanceObserver
{
  public:
    virtual ~InstanceObserver();

    virtual void portAdded(InstancePort *port);
    virtual void portDeleted(InstancePort *port);
    virtual void nameChanged(const Instance *instance);
    virtual void componentNameChanged(const Instance *instance);
    virtual void heightChanged();
};

class Instance final :
    public AbstractInstance,
    public ObserverCollection<InstanceObserver>,
    private ComponentObserver
{
  public:
    Instance(const std::string &name, const Point &aPosition, Component *aComponent);
    Instance(const Instance &copy) = delete;
    Instance & operator=(const Instance &) = delete;
    ~Instance();

    const std::string &getName() const;
    void setName(const std::string &name);
    Component *getComponent() const;

    const std::vector<InstancePort *> &getPorts() const;
    InstancePort *getPort(const std::string &name) const;

    Side portSide(PortType type) const override;
    Side connectorSide(PortType type) const override;

    void accept(Visitor &visitor) override;
    void accept(ConstVisitor &visitor) const override;

  private:
    std::string name;
    Component * const component;
    std::vector<InstancePort*> ports;

    void addPort(InstancePort *port);
    void deletePort(InstancePort *port);

    void portAdded(ComponentPort *port);
    void portDeleted(ComponentPort *port);
    void heightChanged();
    void nameChanged(const std::string &name);

    friend InstanceFactory;

};

#endif // INSTANCE_HPP

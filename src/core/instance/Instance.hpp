// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include "../component/Component.hpp"
#include "../util/Observer.hpp"
#include "../Point.hpp"

#include "IComponentInstance.hpp"
#include "InstanceObserver.h"
#include "InstancePort.hpp"
#include "../visitor/VisitorClient.hpp"

#include <string>
#include <vector>

class Instance final :
    public virtual IComponentInstance,
    private ComponentObserver,
    private ListObserver<ComponentPort>
{
  public:
    Instance(const std::string &name, const Point &aPosition, IComponent *aComponent);
    Instance(const Instance &copy) = delete;
    Instance & operator=(const Instance &) = delete;
    ~Instance();

    const std::string &getName() const override final;
    void setName(const std::string &name) override final;
    IComponent *getComponent() const override final;

    RelativePosition &getPosition() override final;
    const RelativePosition &getPosition() const;

    const List<InstancePort> &getPorts() const override final;
    List<InstancePort> &getPorts() override final;
    InstancePort *getPort(const std::string &name) const;

    Side portSide(PortType type) const override;
    Side connectorSide(PortType type) const override;

    PaperUnit getWidth() const override final;
    PaperUnit getHeight() const override final;

    void accept(Visitor &visitor) override;
    void accept(ConstVisitor &visitor) const override;

  private:
    std::string name;
    IComponent * const component;
    RelativePosition position;
    List<InstancePort> ports;

    void added(ComponentPort *port) override;
    void removed(ComponentPort *port) override;
    void maxPortCountChanged() override;
    void nameChanged(IComponent *item) override;

};

#endif // INSTANCE_HPP

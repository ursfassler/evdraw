// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPOSITIONINSTANCE_HPP
#define COMPOSITIONINSTANCE_HPP

#include "ICompositionInstance.hpp"

#include "../component/Component.hpp"
#include "../instance/InstancePort.hpp"
#include "../instance/InstanceObserver.h"

class CompositionInstance final :
    public ICompositionInstance,
    private ComponentObserver,
    private ListObserver<ComponentPort>
{
  public:
    CompositionInstance(const CompositionInstance&) = delete;
    void operator =(const CompositionInstance&) = delete;

    CompositionInstance(IComponent *component);
    ~CompositionInstance();

    IComponent *getComponent() const override final;

    PaperUnit getWidth() const override final;
    void setWidth(PaperUnit value) override final;
    PaperUnit getHeight() const override final;
    void setHeight(PaperUnit value) override final;

    const List<InstancePort> &getPorts() const override final;
    List<InstancePort> &getPorts() override final;

    Side portSide(PortType type) const override final;
    Side connectorSide(PortType type) const override final;

    void accept(Visitor &visitor) override final;
    void accept(ConstVisitor &visitor) const override final;

  private:
    IComponent * const component;
    PaperUnit width = 0;
    PaperUnit height = 0;
    List<InstancePort> ports;

    void added(ComponentPort *port) override;
    void removed(ComponentPort* value) override;
    void nameChanged(const std::string &name) override;

};

#endif // COMPOSITIONINSTANCE_HPP

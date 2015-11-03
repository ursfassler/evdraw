// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENTINSTANCEMOCK_HPP
#define COMPONENTINSTANCEMOCK_HPP

#include "InstanceMock.hpp"
#include <core/instance/IComponentInstance.hpp>

class ComponentInstanceMock :
    public IComponentInstance,
    public InstanceMock
{
  public:
    std::string name{};
    const std::string &getName() const override final;
    void setName(const std::string &value) override final;

    void notify_nameChange();
    void notify_typeChange();

    IComponent *getComponent() const override final;
    IComponent *component{};

    RelativePosition position{Point{0,0}};
    RelativePosition &getPosition() override final;

};

#endif // COMPONENTINSTANCEMOCK_HPP

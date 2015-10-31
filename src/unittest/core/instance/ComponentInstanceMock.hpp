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
    const std::string &getName() const override final;
    void setName(const std::string &value) override final;
    std::string name{};

    void notify_name_change();
    void notify_type_change();

    IComponent *getComponent() const override final;
    IComponent *component{};

};

#endif // COMPONENTINSTANCEMOCK_HPP

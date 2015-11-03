// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ComponentInstanceMock.hpp"

const std::string &ComponentInstanceMock::getName() const
{
  return name;
}

void ComponentInstanceMock::setName(const std::string &value)
{
  name = value;
}

void ComponentInstanceMock::notify_nameChange()
{
  notify<IInstance*>(&InstanceObserver::nameChanged, this);
}

void ComponentInstanceMock::notify_typeChange()
{
  notify<IInstance*>(&InstanceObserver::componentNameChanged, this);
}

IComponent *ComponentInstanceMock::getComponent() const
{
  return component;
}

RelativePosition &ComponentInstanceMock::getPosition()
{
  return position;
}


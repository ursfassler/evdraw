// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ComponentPort.hpp"

ComponentPort::ComponentPort(const std::string &aName) :
  name(aName)
{
}

const std::string &ComponentPort::getName() const
{
  return name;
}

void ComponentPort::setName(const std::string &name)
{
  if (this->name != name) {
    this->name = name;
    notify<const std::string &>(&ComponentPortObserver::nameChanged, name);
  }
}

size_t ComponentPort::getTopIndex() const
{
  return topIndex;
}

void ComponentPort::setTopIndex(size_t value)
{
  if (topIndex != value) {
    topIndex = value;
    notify(&ComponentPortObserver::topIndexChanged, topIndex);
  }
}


Signal::Signal(const std::string &name) :
  ComponentPort(name)
{
}

Side Signal::side() const
{
  return Side::Right;
}

void Signal::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

void Signal::accept(ConstVisitor &visitor) const
{
  visitor.visit(*this);
}


Slot::Slot(const std::string &name) :
  ComponentPort(name)
{
}

Side Slot::side() const
{
  return Side::Left;
}

void Slot::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

void Slot::accept(ConstVisitor &visitor) const
{
  visitor.visit(*this);
}



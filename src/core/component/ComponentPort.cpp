// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ComponentPort.hpp"

ComponentPort::ComponentPort(const std::string &aName, PortType aType) :
  name(aName),
  type(aType)
{
}

ComponentPort::~ComponentPort()
{
  precondition(!hasObserver());
}

const std::string &ComponentPort::getName() const
{
  return name;
}

void ComponentPort::setName(const std::string &name)
{
  if (this->name != name) {
    this->name = name;
    notify(&ComponentPortObserver::nameChanged, this);
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

PortType ComponentPort::getType() const
{
  return type;
}

void ComponentPort::setType(PortType value)
{
  if (type != value) {
    type = value;
    notify(&ComponentPortObserver::typeChanged, this);
  }
}

void ComponentPort::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

void ComponentPort::accept(ConstVisitor &visitor) const
{
  visitor.visit(*this);
}



#include "ComponentPort.hpp"

ComponentPort::ComponentPort(const std::string &aName) :
  name(aName)
{
}

const std::string &ComponentPort::getName() const
{
  return name;
}

size_t ComponentPort::getTopIndex() const
{
  return topIndex;
}

void ComponentPort::setTopIndex(size_t value)
{
  topIndex = value;
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



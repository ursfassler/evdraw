// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "Library.hpp"

#include "ComponentFactory.hpp"
#include "../instance/InstanceOfSpecification.hpp"
#include "../util/ChildRemover.hpp"

#include <stdexcept>

Library::Library() :
  components{ComponentFactory::dispose}
{
  components.registerObserver(this);
}

Library::~Library()
{
  components.clear();
  components.unregisterObserver(this);
  postcondition(components.empty());
}

void Library::removed(Component *component)
{
  InstanceOfSpecification spec(component);
  ChildRemover remover(spec);
  this->accept(remover);
}

const List<Component> &Library::getComponents() const
{
  return components;
}

List<Component> &Library::getComponents()
{
  return components;
}

Component *Library::getComponent(const std::string &name) const
{
  auto predicate = [&](const Component *itr){
    return itr->getName() == name;
  };
  return components.get(predicate);
}

void Library::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

void Library::accept(ConstVisitor &visitor) const
{
  visitor.visit(*this);
}


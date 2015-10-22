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

void Library::removed(IComponent *component)
{
  InstanceOfSpecification spec(component);
  ChildRemover remover(spec);
  this->accept(remover);
}

const List<IComponent> &Library::getComponents() const
{
  return components;
}

List<IComponent> &Library::getComponents()
{
  return components;
}

IComponent *Library::getComponent(const std::string &name) const
{
  auto predicate = [&](const IComponent *itr){
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


// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstanceOfSpecification.hpp"

#include "Instance.hpp"

InstanceOfSpecification::InstanceOfSpecification(const IComponent *aComponent) :
  component(aComponent)
{
}

InstanceOfSpecification::InstanceOfSpecification(const InstanceOfSpecification &copy) :
  component(copy.component)
{
}

InstanceOfSpecification &InstanceOfSpecification::operator=(const InstanceOfSpecification &right)
{
  component = right.component;
  return *this;
}

bool InstanceOfSpecification::isSatisfiedBy(const Base *candidate) const
{
  const Instance *instance = dynamic_cast<const Instance*>(candidate);
  if (instance == nullptr)
  {
    return false;
  }
  return instance->getComponent() == component;
}

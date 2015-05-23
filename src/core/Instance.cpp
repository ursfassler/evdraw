#include "Instance.hpp"

Instance::Instance(Component *aComponent) :
  component(aComponent)
{
}

Component *Instance::getComponent() const
{
  return component;
}


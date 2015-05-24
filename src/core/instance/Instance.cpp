#include "Instance.hpp"


Instance::Instance(const Point &aPosition, Component *aComponent) :
  Base(nullptr, aPosition),
  component(aComponent)
{
}

Component *Instance::getComponent() const
{
  return component;
}


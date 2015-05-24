#include "Instance.hpp"


Instance::Instance(const Point &aPosition, Component *aComponent) :
  ObserverCollection(),
  position(aPosition),
  component(aComponent)
{
}

Component *Instance::getComponent() const
{
  return component;
}

Point Instance::getPosition() const
{
  return position;
}

void Instance::setPosition(const Point &value)
{
  if (position != value) {
    position = value;
    notifyObservers(this);
  }
}



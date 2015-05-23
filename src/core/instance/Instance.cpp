#include "Instance.hpp"


InstanceListener::~InstanceListener()
{
}

void InstanceListener::positionChange(const Instance *)
{
}

Instance::Instance(const Point &aPosition, Component *aComponent) :
  Observed(this),
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
    notifyListeners<&InstanceListener::positionChange>();
  }
}



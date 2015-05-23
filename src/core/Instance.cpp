#include "Instance.hpp"

Instance::Instance(PaperUnit aX, PaperUnit aY, Component *aComponent) :
  x(aX),
  y(aY),
  component(aComponent)
{
}

Component *Instance::getComponent() const
{
  return component;
}

PaperUnit Instance::getX() const
{
    return x;
}

PaperUnit Instance::getY() const
{
  return y;
}


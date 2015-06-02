#include "Instance.hpp"


Instance::Instance(const std::string &aName, const Point &aPosition, Component *aComponent) :
  Positionable(nullptr, aPosition),
  name(aName),
  component(aComponent),
  ports()
{
}

const std::string &Instance::getName() const
{
  return name;
}

Component *Instance::getComponent() const
{
  return component;
}

void Instance::addPort(AbstractPort *port)
{
  ports.push_back(port);
}

const std::vector<AbstractPort *> &Instance::getPorts() const
{
  return ports;
}

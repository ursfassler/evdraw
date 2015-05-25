#include "Instance.hpp"


Instance::Instance(const std::string &aName, const Point &aPosition, Component *aComponent) :
  Base(nullptr, aPosition),
  name(aName),
  component(aComponent)
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

void Instance::addInput(InstancePort *port)
{
  input.push_back(port);
}

const std::vector<InstancePort *> &Instance::getInput() const
{
  return input;
}

void Instance::addOutput(InstancePort *port)
{
  output.push_back(port);
}

const std::vector<InstancePort *> &Instance::getOutput() const
{
  return output;
}


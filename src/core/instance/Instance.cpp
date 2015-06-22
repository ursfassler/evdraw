#include "Instance.hpp"
#include "../util/list.hpp"

Instance::Instance(const std::string &aName, const Point &aPosition, Component *aComponent) :
  RelativePosition(aPosition),
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

AbstractPort *Instance::getPort(const std::string &name) const
{
  auto predicate = [&](AbstractPort *itr){
    return itr->getName() == name;
  };
  return listGet<AbstractPort*>(ports.begin(), ports.end(), predicate);
}

void Instance::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

void Instance::accept(ConstVisitor &visitor) const
{
  visitor.visit(*this);
}

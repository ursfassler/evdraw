#include "Component.hpp"

#include "../util/list.hpp"
#include "../util/contract.hpp"

Component::Component(const std::string &aName) :
  name(aName),
  portLeft(),
  portRight(),
  implementation(new NullImplementation())
{
}

Component::Component(const std::string &aName, AbstractImplementation *aImplementation) :
  name(aName),
  portLeft(),
  portRight(),
  implementation(aImplementation)
{
}

Component::~Component()
{
  delete implementation;
}

void Component::addPortLeft(ComponentPort *port)
{
  portLeft.push_back(port);
  port->setTopIndex(portLeft.size()-1);
}

const std::vector<ComponentPort *> &Component::getPortLeft() const
{
  return portLeft;
}

void Component::addPortRight(ComponentPort *port)
{
  portRight.push_back(port);
  port->setTopIndex(portRight.size()-1);
}

const std::vector<ComponentPort *> &Component::getPortRight() const
{
  return portRight;
}

Side Component::sideOf(const ComponentPort *port) const
{
  const bool isLeft = contains(portLeft.begin(), portLeft.end(), port);
  const bool isRight = contains(portRight.begin(), portRight.end(), port);

  precondition(isLeft || isRight);
  precondition(!(isLeft && isRight));

  if (isLeft) {
    return Side::Left;
  } else {
    return Side::Right;
  }
}

const std::string &Component::getName() const
{
  return name;
}

void Component::accept(Visitor &visitor) const
{
  visitor.visit(*this);
}

AbstractImplementation *Component::getImplementation()
{
  return implementation;
}

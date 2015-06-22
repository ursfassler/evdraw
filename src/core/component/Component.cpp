#include "Component.hpp"

#include "../util/list.hpp"
#include "../util/contract.hpp"

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

void Component::addPortLeft(Slot *port)
{
  portLeft.push_back(port);
  port->setTopIndex(portLeft.size()-1);
}

const std::vector<Slot *> &Component::getPortLeft() const
{
  return portLeft;
}

void Component::addPortRight(Signal *port)
{
  portRight.push_back(port);
  port->setTopIndex(portRight.size()-1);
}

const std::vector<Signal *> &Component::getPortRight() const
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

void Component::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

void Component::accept(ConstVisitor &visitor) const
{
  visitor.visit(*this);
}

AbstractImplementation *Component::getImplementation() const
{
  return implementation;
}

void Component::setImplementation(AbstractImplementation *value)
{
  precondition(value != nullptr);

  delete implementation;
  implementation = value;
}

#include "Component.hpp"

#include <cassert>

Component::Component(const std::string &aName) :
  name(aName),
  portLeft(),
  portRight()
{
}

Component::~Component()
{
  assert(portLeft.empty());
  assert(portRight.empty());
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

const std::string &Component::getName() const
{
  return name;
}

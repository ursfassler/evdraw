#include "Component.hpp"

Component::Component() :
  portLeft(),
  portRight()
{
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

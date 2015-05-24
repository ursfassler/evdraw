#include "ComponentPort.hpp"

ComponentPort::ComponentPort(const std::string &aName) :
  name(aName)
{
}

const std::string &ComponentPort::getName() const
{
  return name;
}

size_t ComponentPort::getTopIndex() const
{
  return topIndex;
}

void ComponentPort::setTopIndex(size_t value)
{
  topIndex = value;
}

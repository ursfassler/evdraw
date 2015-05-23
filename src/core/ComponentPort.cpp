#include "ComponentPort.hpp"

ComponentPort::ComponentPort(const std::string &aName) :
  name(aName)
{
}

const std::string &ComponentPort::getName() const
{
  return name;
}

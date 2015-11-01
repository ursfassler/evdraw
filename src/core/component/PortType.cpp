// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "PortType.hpp"

#include <string>
#include <stdexcept>

std::string toString(PortType type)
{
  switch (type) {
  case PortType::Signal:
    return "signal";
  case PortType::Slot:
    return "slot";
  }

  throw std::invalid_argument("Unknown port type: " + std::to_string(int(type)));
}

std::ostream &operator <<(std::ostream &stream, PortType type)
{
  stream << toString(type);
  return stream;
}

std::vector<PortType> portTypeList()
{
  return {PortType::Signal, PortType::Slot};
}


PortType portTypeFromUint(uint type)
{
  const uint size = portTypeList().size();
  if (type >= size) {
    throw std::out_of_range("type has to be < " + std::to_string(size));
  }
  return portTypeList()[type];
}


PortType portTypeFromString(const std::string &value)
{
  for (PortType type : portTypeList()) {
    if (value == toString(type)) {
      return type;
    }
  }

  throw std::invalid_argument("Unknown port type: " + value);
}

uint uintFromPortType(PortType type)
{
  uint idx;
  for (idx = 0; idx < portTypeList().size(); idx++) {
    if (type == portTypeList()[idx]) {
      return idx;
    }
  }

  throw std::invalid_argument("Unknown port type: " + std::to_string(int(type)));
}

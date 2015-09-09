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

Side sideOf(PortType type)
{
    switch (type) {
    case PortType::Signal:
      return Side::Right;
    case PortType::Slot:
      return Side::Left;
    }

    throw std::invalid_argument("Unknown port type: " + std::to_string(int(type)));
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

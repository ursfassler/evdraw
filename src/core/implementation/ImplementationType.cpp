// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ImplementationType.hpp"

#include "../util/stdlist.hpp"

#include <stdexcept>

std::vector<ImplementationType> implementationTypeList()
{
  return {ImplementationType::Empty, ImplementationType::Composition};
}

std::string toString(ImplementationType type)
{
  switch (type) {
    case ImplementationType::Empty:
      return "empty";
    case ImplementationType::Composition:
      return "composition";
  }

  throw std::invalid_argument("Unknown implementation type: " + std::to_string(int(type)));
}

std::ostream &operator <<(std::ostream &stream, ImplementationType type)
{
  stream << toString(type);
  return stream;
}

ImplementationType implementationTypeFromUint(uint type)
{
  const uint size = implementationTypeList().size();
  if (type >= size) {
    throw std::out_of_range("type has to be < " + std::to_string(size));
  }
  return implementationTypeList()[type];
}


uint uintFromImplementationType(ImplementationType type)
{
  switch (type) {
    case ImplementationType::Empty:
      return 0;
    case ImplementationType::Composition:
      return 1;
  }

  throw std::invalid_argument("Unknown implementation type: " + std::to_string(int(type)));
}

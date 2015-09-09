// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef IMPLEMENTATIONTYPE_HPP
#define IMPLEMENTATIONTYPE_HPP

#include <vector>
#include <string>
#include <ostream>

enum class ImplementationType
{
  Empty,
  Composition
};

std::vector<ImplementationType> implementationTypeList();
std::string toString(ImplementationType type);
std::ostream &operator <<(std::ostream &stream, ImplementationType type);
ImplementationType implementationTypeFromUint(uint type);
uint uintFromImplementationType(ImplementationType type);

#endif // IMPLEMENTATIONTYPE_HPP

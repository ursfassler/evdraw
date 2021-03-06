// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef PORTTYPE_H
#define PORTTYPE_H

#include <string>
#include <ostream>
#include <vector>

enum class PortType
{
  Signal,
  Slot
};

std::vector<PortType> portTypeList();
PortType portTypeFromUint(uint type);
uint uintFromPortType(PortType type);
std::string toString(PortType type);
PortType portTypeFromString(const std::string &value);
std::ostream &operator <<(std::ostream &stream, PortType type);

#endif // PORTTYPE_H

// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "SimplePort.hpp"


SimplePort::SimplePort() :
  ports(),
  position(Point(0,0))
{
}

SimplePort::SimplePort(const Point &aPosition) :
  ports(),
  position(aPosition)
{
}

void SimplePort::addConnectionPoint(RelativePosition *port)
{
  ports.insert(port);
}

void SimplePort::removeConnectionPoint(RelativePosition *port)
{
  ports.erase(port);
}

std::string SimplePort::getName() const
{
  return "";
}

Point SimplePort::getPosition() const
{
  return position;
}

void SimplePort::accept(Visitor &)
{
}

void SimplePort::accept(ConstVisitor &) const
{
}

// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "DrawPort.hpp"

DrawPort::DrawPort(const Point &offset) :
  RelativePosition(offset)
{
}

void DrawPort::addConnectionPoint(RelativePosition *point)
{
  precondition(!point->hasAnchor());

  point->replaceAnchor(this);

  postcondition(point->hasAnchor());
  postcondition(point->getAnchor() == this);
}

void DrawPort::removeConnectionPoint(RelativePosition *point)
{
  precondition(point->hasAnchor());
  precondition(point->getAnchor() == this);

  point->removeAnchor();

  postcondition(!point->hasAnchor());
}

std::string DrawPort::getName() const
{
  return "";
}

Point DrawPort::getPosition() const
{
  return getAbsolutePosition();
}

void DrawPort::accept(Visitor &)
{
}

void DrawPort::accept(ConstVisitor &) const
{
}

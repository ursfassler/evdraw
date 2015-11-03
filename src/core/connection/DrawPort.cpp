// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "DrawPort.hpp"

DrawPort::DrawPort(const Point &offset) :
  position{offset}
{
}

void DrawPort::addConnectionPoint(RelativePosition *point)
{
  precondition(!point->hasAnchor());

  point->replaceAnchor(&this->getPosition());

  postcondition(point->hasAnchor());
  postcondition(point->getAnchor() == &this->getPosition());
}

void DrawPort::removeConnectionPoint(RelativePosition *point)
{
  precondition(point->hasAnchor());
  precondition(point->getAnchor() == &this->getPosition());

  point->removeAnchor();

  postcondition(!point->hasAnchor());
}

std::string DrawPort::getName() const
{
  return "";
}

RelativePosition &DrawPort::getPosition()
{
  return position;
}

void DrawPort::accept(Visitor &)
{
}

void DrawPort::accept(ConstVisitor &) const
{
}

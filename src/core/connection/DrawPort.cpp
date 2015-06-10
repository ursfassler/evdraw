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

void DrawPort::accept(Visitor &) const
{
}
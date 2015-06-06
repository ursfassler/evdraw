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

void DrawPort::accept(Visitor &) const
{
}

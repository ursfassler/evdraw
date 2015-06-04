#include "Position.hpp"

Position::Position() :
  ObserverCollection()
{
}

Position::~Position()
{
}


Point ZeroPosition::getAbsolutePosition() const
{
  return Point(0,0);
}


RelativePosition::RelativePosition(const Point &aOffset) :
  anchor(&zeroAnchor),
  offset(aOffset)
{
  anchor->registerObserver(this);
}

RelativePosition::~RelativePosition()
{
  anchor->unregisterObserver(this);
}

void RelativePosition::removeAnchor()
{
  replaceAnchor(&zeroAnchor);
}

void RelativePosition::replaceAnchor(Position *newAnchor)
{
  precondition(newAnchor != nullptr);

  anchor->unregisterObserver(this);
  anchor = newAnchor;
  anchor->registerObserver(this);
}

Position *RelativePosition::getAnchor() const
{
  return anchor;
}

bool RelativePosition::hasAnchor() const
{
  return anchor != &zeroAnchor;
}

const Point &RelativePosition::getOffset() const
{
  return offset;
}

void RelativePosition::setOffset(const Point &value)
{
  if (offset != value) {
    offset = value;
    notify(this);
  }
}

Point RelativePosition::getAbsolutePosition() const
{
  return offset + anchor->getAbsolutePosition();
}

void RelativePosition::notify(const RelativePosition *)
{
  ObserverCollection<PositionObserver>::notify(&PositionObserver::notify, static_cast<const RelativePosition*>(this));
}


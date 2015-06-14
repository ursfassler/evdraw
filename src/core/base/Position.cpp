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
  zeroAnchor(),
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

  Point oldPos = getAbsolutePosition();

  anchor->unregisterObserver(this);
  anchor = newAnchor;
  anchor->registerObserver(this);

  if (oldPos != getAbsolutePosition()) {
    ObserverCollection<PositionObserver>::notify(&PositionObserver::absolutePositionChanged, static_cast<const RelativePosition*>(this));
  }
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
    ObserverCollection<PositionObserver>::notify(&PositionObserver::offsetChanged, static_cast<const RelativePosition*>(this));
    ObserverCollection<PositionObserver>::notify(&PositionObserver::absolutePositionChanged, static_cast<const RelativePosition*>(this));
  }
}

Point RelativePosition::getAbsolutePosition() const
{
  return offset + anchor->getAbsolutePosition();
}

void RelativePosition::setAbsolutePosition(const Point &value)
{
  setOffset(value - anchor->getAbsolutePosition());
}

void RelativePosition::absolutePositionChanged(const RelativePosition *sender)
{
  if (sender == anchor) {
    ObserverCollection<PositionObserver>::notify(&PositionObserver::absolutePositionChanged, static_cast<const RelativePosition*>(this));
  }
}

void RelativePosition::offsetChanged(const RelativePosition *)
{
}


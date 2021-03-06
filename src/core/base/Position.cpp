// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "Position.hpp"

Point ZeroPosition::getAbsolutePosition() const
{
  return Point(0,0);
}

ZeroPosition *ZeroPosition::singleton()
{
  static ZeroPosition zero;
  return &zero;
}


RelativePosition::RelativePosition(const Point &aOffset) :
  anchor(ZeroPosition::singleton()),
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
  replaceAnchor(ZeroPosition::singleton());
}

void RelativePosition::replaceAnchor(IPosition *newAnchor)
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

IPosition *RelativePosition::getAnchor() const
{
  return anchor;
}

bool RelativePosition::hasAnchor() const
{
  return anchor != ZeroPosition::singleton();
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


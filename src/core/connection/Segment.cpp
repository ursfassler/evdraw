// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "Segment.hpp"

#include "../util/contract.hpp"

Segment::Segment(Endpoint *aStart, Endpoint *aEnd) :
  ObserverCollection(),
  start(aStart),
  end(aEnd)
{
  start->getPosition().registerObserver(this);
  end->getPosition().registerObserver(this);
}

Segment::~Segment()
{
  end->getPosition().unregisterObserver(this);
  start->getPosition().unregisterObserver(this);
}

Endpoint *Segment::getStart() const
{
  return start;
}

void Segment::setStart(Endpoint *point)
{
  start->getPosition().unregisterObserver(this);
  start = point;
  start->getPosition().registerObserver(this);
}

Endpoint *Segment::getEnd() const
{
  return end;
}

void Segment::setEnd(Endpoint *point)
{
  end->getPosition().unregisterObserver(this);
  end = point;
  end->getPosition().registerObserver(this);
}

bool Segment::moveable() const
{
  return start->freeMovable() && end->freeMovable();
}

void Segment::absolutePositionChanged(const RelativePosition *)
{
  ObserverCollection<SegmentObserver>::notify(&SegmentObserver::positionChanged, static_cast<const Segment *>(this));
}

void Segment::offsetChanged(const RelativePosition *)
{
}

HorizontalSegment::HorizontalSegment(Endpoint *aStart, Endpoint *aEnd) :
  Segment(aStart, aEnd)
{
}

PaperUnit HorizontalSegment::getY() const
{
  return start->getPosition().getAbsolutePosition().y;
}

void HorizontalSegment::moveToY(PaperUnit value)
{
  if (moveable()) {
    start->getPosition().setOffset(Point(start->getPosition().getOffset().x, value));
    end->getPosition().setOffset(Point(end->getPosition().getOffset().x, value));
  }
}

void HorizontalSegment::absolutePositionChanged(const RelativePosition *sender)
{
  precondition((sender == &start->getPosition()) || (sender == &end->getPosition()));

  if (sender == &start->getPosition()) {
    end->getPosition().setAbsolutePosition(Point(end->getPosition().getAbsolutePosition().x, start->getPosition().getAbsolutePosition().y));
  } else {
    start->getPosition().setAbsolutePosition(Point(start->getPosition().getAbsolutePosition().x, end->getPosition().getAbsolutePosition().y));
  }
  Segment::absolutePositionChanged(sender);
}


VerticalSegment::VerticalSegment(Endpoint *aStart, Endpoint *aEnd) :
  Segment(aStart, aEnd)
{
}

PaperUnit VerticalSegment::getX() const
{
  return start->getPosition().getAbsolutePosition().x;
}

void VerticalSegment::moveToX(PaperUnit value)
{
  if (moveable()) {
    start->getPosition().setOffset(Point(value, start->getPosition().getOffset().y));
    end->getPosition().setOffset(Point(value, end->getPosition().getOffset().y));
  }
}

void VerticalSegment::absolutePositionChanged(const RelativePosition *sender)
{
  precondition((sender == &start->getPosition()) || (sender == &end->getPosition()));

  if (sender == &start->getPosition()) {
    end->getPosition().setAbsolutePosition(Point(start->getPosition().getAbsolutePosition().x, end->getPosition().getAbsolutePosition().y));
  } else {
    start->getPosition().setAbsolutePosition(Point(end->getPosition().getAbsolutePosition().x, start->getPosition().getAbsolutePosition().y));
  }
  Segment::absolutePositionChanged(sender);
}

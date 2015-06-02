#include "Segment.hpp"

#include "../util/contract.hpp"

Segment::Segment(Endpoint *aStart, Endpoint *aEnd) :
  ObserverCollection(),
  start(aStart),
  end(aEnd)
{
  start->registerObserver(this);
  end->registerObserver(this);
}

Segment::~Segment()
{
  end->unregisterObserver(this);
  start->unregisterObserver(this);
}

Endpoint *Segment::getStart() const
{
  return start;
}

void Segment::setStart(Endpoint *point)
{
  start->unregisterObserver(this);
  start = point;
  start->registerObserver(this);
}

Endpoint *Segment::getEnd() const
{
  return end;
}

void Segment::setEnd(Endpoint *point)
{
  end->unregisterObserver(this);
  end = point;
  end->registerObserver(this);
}

bool Segment::moveable() const
{
  return start->freeMovable() && end->freeMovable();
}

void Segment::notify(const Positionable *)
{
//  notify(&SegmentObserver::positionChanged, static_cast<const Segment *>(this));
}

HorizontalSegment::HorizontalSegment(Endpoint *aStart, Endpoint *aEnd) :
  Segment(aStart, aEnd)
{
}

PaperUnit HorizontalSegment::getY() const
{
  return start->getAbsolutePosition().y;
}

void HorizontalSegment::moveToY(PaperUnit value)
{
  if (moveable()) {
    start->setOffset(Point(start->getOffset().x, value));
    end->setOffset(Point(end->getOffset().x, value));
  }
}

void HorizontalSegment::notify(const Positionable *sender)
{
  precondition((sender == start) || (sender == end));

  if (sender == start) {
    end->setOffset(Point(end->getOffset().x, start->getOffset().y));
  } else {
    start->setOffset(Point(start->getOffset().x, end->getOffset().y));
  }
  Segment::notify(sender);
}


VerticalSegment::VerticalSegment(Endpoint *aStart, Endpoint *aEnd) :
  Segment(aStart, aEnd)
{
}

PaperUnit VerticalSegment::getX() const
{
  return start->getAbsolutePosition().x;
}

void VerticalSegment::moveToX(PaperUnit value)
{
  if (moveable()) {
    start->setOffset(Point(value, start->getOffset().y));
    end->setOffset(Point(value, end->getOffset().y));
  }
}

void VerticalSegment::notify(const Positionable *sender)
{
  precondition((sender == start) || (sender == end));

  if (sender == start) {
    end->setOffset(Point(start->getOffset().x, end->getOffset().y));
  } else {
    start->setOffset(Point(end->getOffset().x, start->getOffset().y));
  }
  Segment::notify(sender);
}

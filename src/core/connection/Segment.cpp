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

void Segment::positionChanged(const Endpoint *)
{
  notify(&SegmentObserver::positionChanged, static_cast<const Segment *>(this));
}

HorizontalSegment::HorizontalSegment(Endpoint *aStart, Endpoint *aEnd) :
  Segment(aStart, aEnd)
{
}

PaperUnit HorizontalSegment::getY() const
{
  return start->getPosition().y;
}

void HorizontalSegment::moveToY(PaperUnit value)
{
  if (moveable()) {
    start->setPosition(Point(start->getPosition().x, value));
    end->setPosition(Point(end->getPosition().x, value));
  }
}

void HorizontalSegment::positionChanged(const Endpoint *sender)
{
  precondition((sender == start) || (sender == end));

  if (sender == start) {
    end->setPosition(Point(end->getPosition().x, start->getPosition().y));
  } else {
    start->setPosition(Point(start->getPosition().x, end->getPosition().y));
  }
  Segment::positionChanged(sender);
}


VerticalSegment::VerticalSegment(Endpoint *aStart, Endpoint *aEnd) :
  Segment(aStart, aEnd)
{
}

PaperUnit VerticalSegment::getX() const
{
  return start->getPosition().x;
}

void VerticalSegment::moveToX(PaperUnit value)
{
  if (moveable()) {
    start->setPosition(Point(value, start->getPosition().y));
    end->setPosition(Point(value, end->getPosition().y));
  }
}

void VerticalSegment::positionChanged(const Endpoint *sender)
{
  precondition((sender == start) || (sender == end));

  if (sender == start) {
    end->setPosition(Point(start->getPosition().x, end->getPosition().y));
  } else {
    start->setPosition(Point(end->getPosition().x, start->getPosition().y));
  }
  Segment::positionChanged(sender);
}

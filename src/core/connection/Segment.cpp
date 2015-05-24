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
  start->unregisterObserver(this);
  end->unregisterObserver(this);
}

Endpoint *Segment::getStart() const
{
  return start;
}

Endpoint *Segment::getEnd() const
{
  return end;
}

bool Segment::moveable() const
{
  return start->freeMovable() && end->freeMovable();
}

void Segment::notify(const Endpoint *)
{
  notifyObservers(this);
}

HorizontalSegment::HorizontalSegment(Endpoint *aStart, Endpoint *aEnd) :
  Segment(aStart, aEnd)
{
}

PaperUnit HorizontalSegment::getY() const
{
  return start->getY();
}

void HorizontalSegment::moveToY(PaperUnit value)
{
  start->setY(value);
  end->setY(value);
}

void HorizontalSegment::notify(const Endpoint *sender)
{
  precondition((sender == start) || (sender == end));

  if (sender == start) {
    end->setY(start->getY());
  } else {
    start->setY(end->getY());
  }
  Segment::notify(sender);
}


VerticalSegment::VerticalSegment(Endpoint *aStart, Endpoint *aEnd) :
  Segment(aStart, aEnd)
{
}

PaperUnit VerticalSegment::getX() const
{
  return start->getX();
}

void VerticalSegment::moveToX(PaperUnit value)
{
  start->setX(value);
  end->setX(value);
}

void VerticalSegment::notify(const Endpoint *sender)
{
  precondition((sender == start) || (sender == end));

  if (sender == start) {
    end->setX(start->getX());
  } else {
    start->setX(end->getX());
  }
  Segment::notify(sender);
}

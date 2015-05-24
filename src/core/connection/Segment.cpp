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
  return start->getPosition().y;
}

void HorizontalSegment::moveToY(PaperUnit value)
{
  start->setPosition(Point(start->getPosition().x, value));
  end->setPosition(Point(end->getPosition().x, value));
}

void HorizontalSegment::notify(const Endpoint *sender)
{
  precondition((sender == start) || (sender == end));

  if (sender == start) {
    end->setPosition(Point(end->getPosition().x, start->getPosition().y));
  } else {
    start->setPosition(Point(start->getPosition().x, end->getPosition().y));
  }
  Segment::notify(sender);
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
  start->setPosition(Point(value, start->getPosition().y));
  end->setPosition(Point(value, end->getPosition().y));
}

void VerticalSegment::notify(const Endpoint *sender)
{
  precondition((sender == start) || (sender == end));

  if (sender == start) {
    end->setPosition(Point(start->getPosition().x, end->getPosition().y));
  } else {
    start->setPosition(Point(end->getPosition().x, start->getPosition().y));
  }
  Segment::notify(sender);
}

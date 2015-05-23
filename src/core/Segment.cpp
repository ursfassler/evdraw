#include "Segment.hpp"

#include <cassert>

Segment::Segment(Endpoint *aStart, Endpoint *aEnd) :
  Observed(this),
  start(aStart),
  end(aEnd)
{
  start->addListener(this);
  end->addListener(this);
}

Segment::~Segment()
{
  start->removeListener(this);
  end->removeListener(this);
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

void Segment::changeX(const Endpoint *)
{
  notifyListeners<&SegmentListener::positionChange>();
}

void Segment::changeY(const Endpoint *)
{
  notifyListeners<&SegmentListener::positionChange>();
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

void HorizontalSegment::changeY(const Endpoint *sender)
{
  if (sender == start) {
    end->setY(start->getY());
  } else {
    assert(sender == end);
    start->setY(end->getY());
  }
  Segment::changeY(sender);
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

void VerticalSegment::changeX(const Endpoint *sender)
{
  if (sender == start) {
    end->setX(start->getX());
  } else {
    assert(sender == end);
    start->setX(end->getX());
  }
  Segment::changeX(sender);
}


SegmentListener::~SegmentListener()
{
}

void SegmentListener::positionChange(const Segment *)
{
}

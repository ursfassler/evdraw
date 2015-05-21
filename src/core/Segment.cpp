#include "Segment.hpp"

Segment::Segment(Endpoint &aStart, Endpoint &aEnd) :
  start(aStart),
  end(aEnd)
{
  start.addListener(this);
  end.addListener(this);
}

Segment::~Segment()
{
  start.removeListener(this);
  end.removeListener(this);
}

const Endpoint &Segment::getStart() const
{
  return start;
}

const Endpoint &Segment::getEnd() const
{
  return end;
}

bool Segment::moveable() const
{
  return start.freeMovable() && end.freeMovable();
}

HorizontalSegment::HorizontalSegment(Endpoint &aStart, Endpoint &aEnd) :
  Segment(aStart, aEnd)
{
}

PaperUnit HorizontalSegment::getY() const
{
  return getStart().getY();
}

void HorizontalSegment::moveToY(PaperUnit value)
{
  start.setY(value);
  end.setY(value);
}

void HorizontalSegment::changeY(Endpoint *sender, PaperUnit value)
{
  start.setY(value);
  end.setY(value);
}


VerticalSegment::VerticalSegment(Endpoint &aStart, Endpoint &aEnd) :
  Segment(aStart, aEnd)
{
}

PaperUnit VerticalSegment::getX() const
{
  return getStart().getX();
}

void VerticalSegment::moveToX(PaperUnit value)
{
  start.setX(value);
  end.setX(value);
}

void VerticalSegment::changeX(Endpoint *sender, PaperUnit value)
{
  start.setX(value);
  end.setX(value);
}

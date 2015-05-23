#include "Connection.hpp"

#include <cassert>

Connection::Connection() :
  start(0,0), //TODO use factory
  end(0,0),
  intermediatePoints(),
  horizontalSegments(),
  verticalSegments()
{
}

Connection::~Connection()
{
  assert(horizontalSegments.empty());
  assert(verticalSegments.empty());
  assert(intermediatePoints.empty());
}

PortPoint &Connection::getStart()
{
    return start;
}

PortPoint &Connection::getEnd()
{
  return end;
}

const std::vector<HorizontalSegment*> Connection::getHorizontalSegment() const
{
  return horizontalSegments;
}

const std::vector<VerticalSegment *> Connection::getVerticalSegment() const
{
  return verticalSegments;
}

const std::vector<IntermediatePoint *> &Connection::getIntermediatePoints() const
{
  return intermediatePoints;
}

void Connection::checkInvariants() const
{
  assert(intermediatePoints.size() >= 2);
  assert(intermediatePoints.size() % 2 == 0);
  assert(horizontalSegments.size() >= 2);
  assert(verticalSegments.size() >= 1);
  assert(horizontalSegments.size() == verticalSegments.size()+1);
  assert(intermediatePoints.size() == verticalSegments.size()*2);
}


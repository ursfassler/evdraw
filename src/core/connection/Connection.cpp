#include "Connection.hpp"

#include "../util/contract.hpp"
#include <cassert>

Connection::Connection() :
  start(Point(0,0)), //TODO use factory
  end(Point(0,0)),
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

void Connection::addHorizontalSegment(HorizontalSegment *segment)
{
  horizontalSegments.push_back(segment);
}

const std::vector<VerticalSegment *> Connection::getVerticalSegment() const
{
  return verticalSegments;
}

void Connection::addVerticalSegment(VerticalSegment *segment)
{
  verticalSegments.push_back(segment);
}

const std::vector<IntermediatePoint *> &Connection::getIntermediatePoints() const
{
  return intermediatePoints;
}

void Connection::addIntermediatePoint(IntermediatePoint *point)
{
  intermediatePoints.push_back(point);
}

void Connection::checkInvariants() const
{
  invariant(intermediatePoints.size() >= 2);
  invariant(intermediatePoints.size() % 2 == 0);
  invariant(horizontalSegments.size() >= 2);
  invariant(verticalSegments.size() >= 1);
  invariant(horizontalSegments.size() == verticalSegments.size()+1);
  invariant(intermediatePoints.size() == verticalSegments.size()*2);
}


#include "Connection.hpp"

Connection::Connection() :
  start(0,0), //TODO use factory
  end(0,0)
{
}

const PortPoint &Connection::getStart() const
{
    return start;
}

const PortPoint &Connection::getEnd() const
{
  return end;
}

const std::vector<HorizontalSegment> Connection::getHorizontalSegment() const
{
  return horizontalSegments;
}

const std::vector<VerticalSegment> Connection::getVerticalSegment() const
{
  return verticalSegments;
}

const std::vector<IntermediatePoint> &Connection::getIntermediatePoints() const
{
  return intermediatePoints;
}


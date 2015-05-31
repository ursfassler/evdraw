#include "Connection.hpp"

#include "../util/contract.hpp"
#include <cassert>

ConnectionBase::ConnectionBase() :
  points(),
  horizontalSegments(),
  verticalSegments()
{
}

ConnectionBase::~ConnectionBase()
{
  assert(horizontalSegments.empty());
  assert(verticalSegments.empty());
  assert(points.empty());
}

void ConnectionBase::checkInvariants() const
{
  invariant(points.size() == 1+horizontalSegments.size()+verticalSegments.size());

  for (size_t i = 0; i < points.size()-1; i++) {
    Segment *seg = getSegment(i);
    invariant(points[i] == seg->getStart());
    invariant(points[i+1] == seg->getEnd());
  }
}

Segment *ConnectionBase::getSegment(size_t index) const
{
  const bool isHorizontal = (index % 2) == 0;
  const size_t segIndex = index / 2;

  if (isHorizontal) {
    return horizontalSegments[segIndex];
  } else {
    return verticalSegments[segIndex];
  }
}

const std::vector<HorizontalSegment *> &ConnectionBase::getHorizontalSegment() const
{
  return horizontalSegments;
}

void ConnectionBase::addHorizontalSegment(HorizontalSegment *segment)
{
  horizontalSegments.push_back(segment);
  notify(&ConnectionObserver::addHorizontalSegment, static_cast<const ConnectionBase *>(this), segment);
}

const std::vector<VerticalSegment *> &ConnectionBase::getVerticalSegment() const
{
  return verticalSegments;
}

void ConnectionBase::addVerticalSegment(VerticalSegment *segment)
{
  verticalSegments.push_back(segment);
  notify(&ConnectionObserver::addVerticalSegment, static_cast<const ConnectionBase *>(this), segment);
}

const std::vector<Endpoint *> &ConnectionBase::getPoints() const
{
  return points;
}

void ConnectionBase::addPoint(Endpoint *point)
{
  points.push_back(point);
}





Endpoint *Connection::getStart()
{
  return points.front();
}

Endpoint *Connection::getEnd()
{
  return points.back();
}

void Connection::checkInvariants() const
{
  ConnectionBase::checkInvariants();
  invariant(getPoints().size() >= 4);
  invariant(getPoints().size() % 2 == 0);
  invariant(getHorizontalSegment().size() >= 2);
  invariant(getVerticalSegment().size() >= 1);
  invariant(getHorizontalSegment().size() == getVerticalSegment().size()+1);
  invariant(getPoints().size() == getHorizontalSegment().size()*2);
}



Endpoint *ConstructionConnection::getStart()
{
  precondition(!points.empty());
  return points.front();
}

Endpoint *ConstructionConnection::getEnd()
{
  precondition(!points.empty());
  return points.back();
}

const Endpoint *ConstructionConnection::getStart() const
{
  precondition(!points.empty());
  return points.front();
}

const Endpoint *ConstructionConnection::getEnd() const
{
  precondition(!points.empty());
  return points.back();
}

void ConstructionConnection::insertSegmentAtEnd()
{
  if (getPoints().size() % 2 == 0) {
    insertVerticalSegment();
  } else {
    insertHorizontalSegment();
  }
}

void ConstructionConnection::checkInvariants() const
{
  ConnectionBase::checkInvariants();
  invariant(getPoints().size() >= 3);
  invariant(getHorizontalSegment().size() >= 1);
  invariant(getVerticalSegment().size() >= 1);
  invariant(getHorizontalSegment().size() >= getVerticalSegment().size());
}

void ConstructionConnection::insertHorizontalSegment()
{
  precondition(getHorizontalSegment().size() == getVerticalSegment().size());

  IntermediatePoint *ip = new IntermediatePoint(getEnd()->getPosition());
  HorizontalSegment *hs = new HorizontalSegment(ip, getEnd());
  points.insert(points.end()-1, ip);
  getVerticalSegment().back()->setEnd(ip);
  ConnectionBase::addHorizontalSegment(hs);

  postcondition(getHorizontalSegment().size() == getVerticalSegment().size()+1);
  checkInvariants();
}

void ConstructionConnection::insertVerticalSegment()
{
  precondition(getHorizontalSegment().size() == getVerticalSegment().size()+1);

  IntermediatePoint *ip = new IntermediatePoint(getEnd()->getPosition());
  VerticalSegment *vs = new VerticalSegment(ip, getEnd());
  points.insert(points.end()-1, ip);
  getHorizontalSegment().back()->setEnd(ip);
  ConnectionBase::addVerticalSegment(vs);

  postcondition(getHorizontalSegment().size() == getVerticalSegment().size());
  checkInvariants();
}

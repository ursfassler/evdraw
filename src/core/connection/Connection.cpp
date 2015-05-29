#include "Connection.hpp"

#include "../util/contract.hpp"
#include <cassert>

ConnectionBase::ConnectionBase() :
  start(Point(0,0)), //TODO use factory
  end(Point(0,0)),
  intermediatePoints(),
  horizontalSegments(),
  verticalSegments()
{
}

ConnectionBase::~ConnectionBase()
{
  assert(horizontalSegments.empty());
  assert(verticalSegments.empty());
  assert(intermediatePoints.empty());
}

void ConnectionBase::checkInvariants() const
{
  //TODO check order of point and segment
}

PortPoint &ConnectionBase::getStart()
{
    return start;
}

PortPoint &ConnectionBase::getEnd()
{
  return end;
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

const std::vector<IntermediatePoint *> &ConnectionBase::getIntermediatePoints() const
{
  return intermediatePoints;
}

void ConnectionBase::addIntermediatePoint(IntermediatePoint *point)
{
  intermediatePoints.push_back(point);
}





void Connection::checkInvariants() const
{
  ConnectionBase::checkInvariants();
  invariant(getIntermediatePoints().size() >= 2);
  invariant(getIntermediatePoints().size() % 2 == 0);
  invariant(getHorizontalSegment().size() >= 2);
  invariant(getVerticalSegment().size() >= 1);
  invariant(getHorizontalSegment().size() == getVerticalSegment().size()+1);
  invariant(getIntermediatePoints().size() == getVerticalSegment().size()*2);
}



void PartialConnectionFromStart::addSegment()
{
  if (getIntermediatePoints().size() % 2 == 0) {
    insertVerticalSegment();
  } else {
    insertHorizontalSegment();
  }
}

void PartialConnectionFromStart::buildFinished()
{
  if (getIntermediatePoints().size() % 2 != 0) {
    insertHorizontalSegment();
  }
}

void PartialConnectionFromStart::insertHorizontalSegment()
{
  precondition(getHorizontalSegment().size() == getVerticalSegment().size());

  IntermediatePoint *ip = new IntermediatePoint(getEnd().getPosition());
  addIntermediatePoint(ip);
  getVerticalSegment().back()->setEnd(ip);
  HorizontalSegment *hs = new HorizontalSegment(ip, &getEnd());
  ConnectionBase::addHorizontalSegment(hs);

  postcondition(getHorizontalSegment().size() == getVerticalSegment().size()+1);
}

void PartialConnectionFromStart::insertVerticalSegment()
{
  precondition(getHorizontalSegment().size() == getVerticalSegment().size()+1);

  IntermediatePoint *ip = new IntermediatePoint(getEnd().getPosition());
  addIntermediatePoint(ip);
  getHorizontalSegment().back()->setEnd(ip);
  VerticalSegment *vs = new VerticalSegment(ip, &getEnd());
  ConnectionBase::addVerticalSegment(vs);

  postcondition(getHorizontalSegment().size() == getVerticalSegment().size());
}

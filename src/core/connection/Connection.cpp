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
  //TODO check order of point and segment
  invariant(points.size() == 1+horizontalSegments.size()+verticalSegments.size());
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



Endpoint *ConstructionConnection::getRoot()
{
  precondition(!points.empty());
  return points.front();
}

Endpoint *ConstructionConnection::getLeaf()
{
  precondition(!points.empty());
  return points.back();
}

const Endpoint *ConstructionConnection::getRoot() const
{
  precondition(!points.empty());
  return points.front();
}

const Endpoint *ConstructionConnection::getLeaf() const
{
  precondition(!points.empty());
  return points.back();
}

void ConstructionConnection::addSegment()
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

  IntermediatePoint *ip = new IntermediatePoint(getLeaf()->getPosition());
  HorizontalSegment *hs = new HorizontalSegment(getLeaf(), ip);
  addPoint(ip);
  ConnectionBase::addHorizontalSegment(hs);

  postcondition(getHorizontalSegment().size() == getVerticalSegment().size()+1);
}

void ConstructionConnection::insertVerticalSegment()
{
  precondition(getHorizontalSegment().size() == getVerticalSegment().size()+1);

  IntermediatePoint *ip = new IntermediatePoint(getLeaf()->getPosition());
  VerticalSegment *vs = new VerticalSegment(getLeaf(), ip);
  addPoint(ip);
  ConnectionBase::addVerticalSegment(vs);

  postcondition(getHorizontalSegment().size() == getVerticalSegment().size());
}

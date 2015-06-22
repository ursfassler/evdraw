#include "Connection.hpp"

#include "../util/contract.hpp"
#include <cassert>

Connection::Connection(AbstractPort *aStartPort, AbstractPort *aEndPort) :
  points(),
  horizontalSegments(),
  verticalSegments(),
  startPort(aStartPort),
  endPort(aEndPort)
{
}

Connection::~Connection()
{
  assert(horizontalSegments.empty());
  assert(verticalSegments.empty());
  assert(points.empty());
}

AbstractPort *Connection::getStartPort() const
{
  return startPort;
}

void Connection::replaceStartPort(AbstractPort *port)
{
  startPort->removeConnectionPoint(points.front());
  startPort = port;
  startPort->addConnectionPoint(points.front());
}

AbstractPort *Connection::getEndPort() const
{
  return endPort;
}

void Connection::replaceEndPort(AbstractPort *port)
{
  endPort->removeConnectionPoint(points.back());
  endPort = port;
  endPort->addConnectionPoint(points.back());
}

void Connection::checkInvariants() const
{
  invariant(getPoints().size() >= 3);
  invariant(getHorizontalSegment().size() >= 1);
  invariant(getVerticalSegment().size() >= 1);
  invariant(points.size() == 1+horizontalSegments.size()+verticalSegments.size());

  for (size_t i = 0; i < points.size()-1; i++) {
    Segment *seg = getSegment(i);
    invariant(points[i] == seg->getStart());
    invariant(points[i+1] == seg->getEnd());
  }
}

std::vector<PaperUnit> Connection::getPath() const
{
  std::vector<PaperUnit> path;

  for (size_t i = 1; i < horizontalSegments.size()+verticalSegments.size()-1; i++) {
    const bool isHorizontal = (i % 2) == 0;
    const size_t segIndex = i / 2;

    PaperUnit pos;
    if (isHorizontal) {
      pos = horizontalSegments[segIndex]->getY();
    } else {
      pos = verticalSegments[segIndex]->getX();
    }
    path.push_back(pos);
  }

  return path;
}

Segment *Connection::getSegment(size_t index) const
{
  const bool isHorizontal = (index % 2) == 0;
  const size_t segIndex = index / 2;

  if (isHorizontal) {
    return horizontalSegments[segIndex];
  } else {
    return verticalSegments[segIndex];
  }
}

const std::vector<HorizontalSegment *> &Connection::getHorizontalSegment() const
{
  return horizontalSegments;
}

void Connection::addHorizontalSegment(HorizontalSegment *segment)
{
  horizontalSegments.push_back(segment);
  notify(&ConnectionObserver::addHorizontalSegment, static_cast<const Connection *>(this), segment);
}

const std::vector<VerticalSegment *> &Connection::getVerticalSegment() const
{
  return verticalSegments;
}

void Connection::addVerticalSegment(VerticalSegment *segment)
{
  verticalSegments.push_back(segment);
  notify(&ConnectionObserver::addVerticalSegment, static_cast<const Connection *>(this), segment);
}

const std::vector<Endpoint *> &Connection::getPoints() const
{
  return points;
}

void Connection::addPoint(Endpoint *point)
{
  points.push_back(point);
}

void Connection::insertSegmentAtEnd()
{
  if (getPoints().size() % 2 == 0) {
    insertVerticalSegment();
  } else {
    insertHorizontalSegment();
  }
}

void Connection::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

void Connection::accept(ConstVisitor &visitor) const
{
  visitor.visit(*this);
}

void Connection::insertHorizontalSegment()
{
  precondition(getHorizontalSegment().size() == getVerticalSegment().size());

  Endpoint *ip = new Endpoint(points.back()->getAbsolutePosition());
  HorizontalSegment *hs = new HorizontalSegment(ip, points.back());
  points.insert(points.end()-1, ip);
  getVerticalSegment().back()->setEnd(ip);
  Connection::addHorizontalSegment(hs);

  postcondition(getHorizontalSegment().size() == getVerticalSegment().size()+1);
  checkInvariants();
}

void Connection::insertVerticalSegment()
{
  precondition(getHorizontalSegment().size() == getVerticalSegment().size()+1);

  Endpoint *ip = new Endpoint(points.back()->getAbsolutePosition());
  VerticalSegment *vs = new VerticalSegment(ip, points.back());
  points.insert(points.end()-1, ip);
  getHorizontalSegment().back()->setEnd(ip);
  Connection::addVerticalSegment(vs);

  postcondition(getHorizontalSegment().size() == getVerticalSegment().size());
  checkInvariants();
}

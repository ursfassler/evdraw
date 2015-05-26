#include "Connection.hpp"

#include "../util/contract.hpp"
#include <cassert>

Connection::Connection(Mode aMode) :
  mode(aMode),
  start(Point(0,0)), //TODO use factory
  end(Point(0,0)),
  intermediatePoints(),
  horizontalSegments(),
  verticalSegments()
{
  switch (mode) {
    case Mode::Build:
      break;
    case Mode::BuildToEnd:
      initBuildToEnd();
      break;
    case Mode::Finished:
      break;
  }
}

Connection::~Connection()
{
  assert(horizontalSegments.empty());
  assert(verticalSegments.empty());
  assert(intermediatePoints.empty());
}

void Connection::checkInvariants() const
{
  //TODO when constructing a connection interactively, some of those invariants are violated
  //TODO remove those
  invariant(intermediatePoints.size() >= 2);
  invariant(intermediatePoints.size() % 2 == 0);
  invariant(horizontalSegments.size() >= 2);
  invariant(verticalSegments.size() >= 1);
  invariant(horizontalSegments.size() == verticalSegments.size()+1);
  invariant(intermediatePoints.size() == verticalSegments.size()*2);
}

Connection::Mode Connection::getMode() const
{
  return mode;
}

void Connection::buildFinished()
{
  switch (mode) {
    case Mode::Build:
      mode = Mode::Finished;
      break;
    case Mode::BuildToEnd:
      finishBuildToEnd();
      mode = Mode::Finished;
      break;
    case Mode::Finished:
      break;
  }
  checkInvariants();
}

void Connection::addSegment()
{
  precondition(mode == Mode::BuildToEnd);

  if (intermediatePoints.size() % 2 == 0) {
    addVerticalSegment();
  } else {
    addHorizontalSegment();
  }
}

void Connection::addHorizontalSegment()
{
  precondition(horizontalSegments.size() == verticalSegments.size());

  IntermediatePoint *ip = new IntermediatePoint(end.getPosition());
  addIntermediatePoint(ip);
  verticalSegments.back()->setEnd(ip);
  HorizontalSegment *hs = new HorizontalSegment(ip, &end);
  addHorizontalSegment(hs);

  postcondition(horizontalSegments.size() == verticalSegments.size()+1);
}

void Connection::addVerticalSegment()
{
  precondition(horizontalSegments.size() == verticalSegments.size()+1);

  IntermediatePoint *ip = new IntermediatePoint(end.getPosition());
  addIntermediatePoint(ip);
  horizontalSegments.back()->setEnd(ip);
  VerticalSegment *vs = new VerticalSegment(ip, &end);
  addVerticalSegment(vs);

  postcondition(horizontalSegments.size() == verticalSegments.size());
}

PortPoint &Connection::getStart()
{
    return start;
}

PortPoint &Connection::getEnd()
{
  return end;
}

const std::vector<HorizontalSegment *> &Connection::getHorizontalSegment() const
{
  return horizontalSegments;
}

void Connection::addHorizontalSegment(HorizontalSegment *segment)
{
  horizontalSegments.push_back(segment);
}

const std::vector<VerticalSegment *> &Connection::getVerticalSegment() const
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

void Connection::initBuildToEnd()
{
  precondition(verticalSegments.empty());
  precondition(horizontalSegments.empty());
  precondition(intermediatePoints.empty());

  IntermediatePoint *ip = new IntermediatePoint(Point(0,0));
  HorizontalSegment *hs = new HorizontalSegment(&start, ip);
  VerticalSegment *vs = new VerticalSegment(ip, &end);

  addIntermediatePoint(ip);
  addHorizontalSegment(hs);
  addVerticalSegment(vs);
}

void Connection::finishBuildToEnd()
{
  precondition(mode == Mode::BuildToEnd);

  if (intermediatePoints.size() % 2 != 0) {
    addHorizontalSegment();
  }
}




std::ostream &operator<<(std::ostream &stream, Connection::Mode mode)
{
  switch (mode) {
    case Connection::Mode::Build:
      stream << "build";
      break;
    case Connection::Mode::BuildToEnd:
      stream << "buildToEnd";
      break;
    case Connection::Mode::Finished:
      stream << "finished";
      break;
  }
  return stream;
}

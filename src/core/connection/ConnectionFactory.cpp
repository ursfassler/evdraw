#include "ConnectionFactory.hpp"

#include "../util/contract.hpp"
#include <iterator>

Connection *ConnectionFactory::produce(PaperUnit startX, PaperUnit startY, PaperUnit endX, PaperUnit endY)
{
  std::vector<PaperUnit> path;
  path.push_back(startX);
  path.push_back(startY);
  path.push_back((startX+endX) / 2);
  path.push_back(endY);
  path.push_back(endX);

  return produce(path);
}

Connection *ConnectionFactory::produce(const std::vector<PaperUnit> &path)
{
  precondition(path.size() >= 5);
  precondition((path.size() % 2) == 1);

  Connection *con = new Connection();

  addPoints(con, path);
  addSegments(con);

  con->checkInvariants();

  return con;
}

PartialConnectionFromStart *ConnectionFactory::producePartialFromStart()
{
  PartialConnectionFromStart *con = new PartialConnectionFromStart();

  IntermediatePoint *ip = new IntermediatePoint(Point(0,0));
  HorizontalSegment *hs = new HorizontalSegment(&con->start, ip);
  VerticalSegment *vs = new VerticalSegment(ip, &con->end);

  con->addIntermediatePoint(ip);
  con->addHorizontalSegment(hs);
  con->addVerticalSegment(vs);

  con->checkInvariants();

  return con;
}

void ConnectionFactory::cleanup(ConnectionBase &connection)
{
  for (HorizontalSegment *seg : connection.horizontalSegments) {
    delete seg;
  }
  connection.horizontalSegments.clear();

  for (VerticalSegment *seg : connection.verticalSegments) {
    delete seg;
  }
  connection.verticalSegments.clear();

  for (IntermediatePoint *seg : connection.intermediatePoints) {
    delete seg;
  }
  connection.intermediatePoints.clear();

  postcondition(connection.horizontalSegments.empty());
  postcondition(connection.verticalSegments.empty());
  postcondition(connection.intermediatePoints.empty());
}

void ConnectionFactory::dispose(ConnectionBase *connection)
{
  precondition(connection != nullptr);

  cleanup(*connection);
  delete connection;
}

void ConnectionFactory::addPoints(ConnectionBase *con, const std::vector<PaperUnit> &path)
{
  const size_t LAST_IDX = path.size()-1;

  con->start.setPosition(Point(path[0], path[1]));
  con->end.setPosition(Point(path[LAST_IDX],path[LAST_IDX-1]));

  for (size_t i = 1; i < path.size()-2; i += 2) {
    const PaperUnit x1 = path[i+1];
    const PaperUnit y1 = path[i];
    const PaperUnit x2 = x1;
    const PaperUnit y2 = path[i+2];

    con->intermediatePoints.push_back(new IntermediatePoint(Point(x1, y1)));
    con->intermediatePoints.push_back(new IntermediatePoint(Point(x2, y2)));
  }
}

void ConnectionFactory::addSegments(ConnectionBase *con)
{
  precondition(con->intermediatePoints.size() >= 2);

  con->horizontalSegments.push_back(new HorizontalSegment(&con->start, con->intermediatePoints.front()));

  con->verticalSegments.push_back(new VerticalSegment(con->intermediatePoints[0], con->intermediatePoints[1]));
  for (size_t i = 1; i < con->intermediatePoints.size()-1; i += 2) {
    IntermediatePoint *start  = con->intermediatePoints[i];
    IntermediatePoint *middle = con->intermediatePoints[i+1];
    IntermediatePoint *end    = con->intermediatePoints[i+2];
    con->horizontalSegments.push_back(new HorizontalSegment(start, middle));
    con->verticalSegments.push_back(new VerticalSegment(middle, end));
  }

  con->horizontalSegments.push_back(new HorizontalSegment(con->intermediatePoints.back(), &con->end));
}


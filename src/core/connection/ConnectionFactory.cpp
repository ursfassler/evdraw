#include "ConnectionFactory.hpp"

#include "../util/contract.hpp"
#include "Connection.hpp"
#include <iterator>
#include <map>

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

  return produce(createPointList(path));
}

Connection *ConnectionFactory::produce(const std::vector<Endpoint *> &points)
{
  precondition(points.size() >= 4);
  precondition((points.size() % 2) == 0);

  Connection *con = new Connection();

  con->points.assign(points.begin(), points.end());
  addSegments(con);

  con->checkInvariants();

  return con;
}


Connection *ConnectionFactory::produce(const ConstructionConnection &prototype)
{
  return produce(createPointList(prototype));
}

std::vector<Endpoint *> ConnectionFactory::createPointList(const ConstructionConnection &prototype)
{
  std::vector<Endpoint *> list;

  list.push_back(new PortPoint(prototype.getRoot()->getPosition()));
  for (size_t i = 1; i < prototype.getPoints().size()-1; i++) {
    Endpoint *pp = prototype.getPoints()[i];
    list.push_back(new IntermediatePoint(pp->getPosition()));
  }
  if (prototype.getPoints().size() % 2 != 0) {
    list.push_back(new IntermediatePoint(prototype.getLeaf()->getPosition()));
  }
  list.push_back(new PortPoint(prototype.getLeaf()->getPosition()));

  return list;
}



ConstructionConnection *ConnectionFactory::produceConstructionConnection()
{
  ConstructionConnection *con = new ConstructionConnection();

  IntermediatePoint *start = new IntermediatePoint(Point(0,0));
  IntermediatePoint *middle = new IntermediatePoint(Point(0,0));
  IntermediatePoint *end = new IntermediatePoint(Point(0,0));
  HorizontalSegment *hs = new HorizontalSegment(start, middle);
  VerticalSegment *vs = new VerticalSegment(middle, end);

  con->addPoint(start);
  con->addPoint(middle);
  con->addPoint(end);
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

  for (Endpoint *point : connection.points) {
    delete point;
  }
  connection.points.clear();

  postcondition(connection.horizontalSegments.empty());
  postcondition(connection.verticalSegments.empty());
  postcondition(connection.points.empty());
}

void ConnectionFactory::dispose(ConnectionBase *connection)
{
  precondition(connection != nullptr);

  cleanup(*connection);
  delete connection;
}

std::vector<Endpoint *> ConnectionFactory::createPointList(const std::vector<PaperUnit> &path)
{
  std::vector<Endpoint *> list;

  const size_t LAST_IDX = path.size()-1;

  list.push_back(new PortPoint(Point(path[0], path[1])));

  for (size_t i = 1; i < path.size()-2; i += 2) {
    const PaperUnit x1 = path[i+1];
    const PaperUnit y1 = path[i];
    const PaperUnit x2 = x1;
    const PaperUnit y2 = path[i+2];

    list.push_back(new IntermediatePoint(Point(x1, y1)));
    list.push_back(new IntermediatePoint(Point(x2, y2)));
  }

  list.push_back(new PortPoint(Point(path[LAST_IDX],path[LAST_IDX-1])));

  return list;
}

void ConnectionFactory::addSegments(ConnectionBase *con)
{
  precondition(con->points.size() >= 2);

  for (size_t i = 0; i < con->points.size()-1; i++) {
    bool isHorizontal = (i % 2) == 0;
    Endpoint *start  = con->points[i];
    Endpoint *end    = con->points[i+1];
    if (isHorizontal) {
      con->horizontalSegments.push_back(new HorizontalSegment(start, end));
    } else {
      con->verticalSegments.push_back(new VerticalSegment(start, end));
    }
  }
}

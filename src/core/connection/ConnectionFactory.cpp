#include "ConnectionFactory.hpp"

#include "../util/contract.hpp"
#include "Connection.hpp"
#include <iterator>
#include <map>

Connection *ConnectionFactory::produce(AbstractPort *startPort, AbstractPort *endPort)
{
  std::vector<PaperUnit> path;
  path.push_back(0);
  path.push_back(0);
  path.push_back(0);
  path.push_back(0);
  path.push_back(0);

  return produce(startPort, endPort, path);
}

Connection *ConnectionFactory::produceConstruction(AbstractPort *startPort, AbstractPort *endPort)
{
  std::vector<PaperUnit> path;
  path.push_back(0);
  path.push_back(0);
  path.push_back(0);
  path.push_back(0);

  return produce(startPort, endPort, path);
}

Connection *ConnectionFactory::produce(AbstractPort *startPort, AbstractPort *endPort, const std::vector<PaperUnit> &path)
{
  precondition(path.size() >= 4);

  return produce(startPort, endPort, createPointList(path));
}

Connection *ConnectionFactory::produce(AbstractPort *startPort, AbstractPort *endPort, const std::vector<Endpoint *> &points)
{
  precondition(points.size() >= 3);

  Connection *con = new Connection(startPort, endPort);

  con->points.assign(points.begin(), points.end());
  addSegments(con);

  con->checkInvariants();

  return con;
}

void ConnectionFactory::cleanup(Connection &connection)
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

void ConnectionFactory::dispose(Connection *connection)
{
  precondition(connection != nullptr);

  cleanup(*connection);
  delete connection;
}

std::vector<Endpoint *> ConnectionFactory::createPointList(const std::vector<PaperUnit> &path)
{
  precondition(path.size() >= 2);

  std::vector<Endpoint *> list;

  for (size_t i = 1; i < path.size(); i++) {
    const bool swap = (i % 2) == 1;
    const PaperUnit x = swap ? path[i-1] : path[i];
    const PaperUnit y = swap ? path[i] : path[i-1];
    list.push_back(new IntermediatePoint(Point(x, y)));
  }

  return list;
}

void ConnectionFactory::addSegments(Connection *con)
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

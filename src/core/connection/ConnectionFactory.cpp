// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ConnectionFactory.hpp"

#include "../util/contract.hpp"
#include "Connection.hpp"
#include <iterator>
#include <map>

Connection *ConnectionFactory::produce(AbstractPort *startPort, AbstractPort *endPort)
{
  const PaperUnit center = (startPort->getPosition().x + endPort->getPosition().x) / 2;

  std::vector<PaperUnit> path;
  path.push_back(center);

  return produce(startPort, endPort, path);
}

Connection *ConnectionFactory::produceConstruction(AbstractPort *startPort, AbstractPort *endPort)
{
  const Point start = startPort->getPosition();
  const Point end = endPort->getPosition();
  const Point middle = Point(end.x, start.y);

  std::vector<Endpoint *> pointlist;
  pointlist.push_back(new Endpoint(Point(0,0)));
  pointlist.push_back(new Endpoint(middle));
  pointlist.push_back(new Endpoint(Point(0,0)));

  return produce(startPort, endPort, pointlist);
}

Connection *ConnectionFactory::produce(AbstractPort *startPort, AbstractPort *endPort, const std::vector<PaperUnit> &path)
{
  precondition(path.size() >= 1);

  std::vector<PaperUnit> fullpath;
  fullpath.push_back(startPort->getPosition().x);
  fullpath.push_back(startPort->getPosition().y);
  fullpath.insert(fullpath.end(), path.begin(), path.end());
  fullpath.push_back(endPort->getPosition().y);
  fullpath.push_back(endPort->getPosition().x);

  return produce(startPort, endPort, createPointList(fullpath));
}

Connection *ConnectionFactory::produce(AbstractPort *startPort, AbstractPort *endPort, const std::vector<Endpoint *> &points)
{
  precondition(points.size() >= 3);

  Connection *con = new Connection(startPort, endPort);

  con->points.assign(points.begin(), points.end());
  addSegments(con);

  con->getStartPort()->addConnectionPoint(con->points.front());
  con->getEndPort()->addConnectionPoint(con->points.back());

  con->checkInvariants();

  return con;
}

void ConnectionFactory::cleanup(Connection &connection)
{
  if (!connection.getPoints().empty()) {
    connection.getStartPort()->removeConnectionPoint(connection.getPoints().front());
    connection.getEndPort()->removeConnectionPoint(connection.getPoints().back());
  }

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
    list.push_back(new Endpoint(Point(x, y)));
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

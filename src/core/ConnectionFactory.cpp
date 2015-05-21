#include "ConnectionFactory.hpp"

#include <stdexcept>
#include <iterator>
#include <assert.h>

Connection *ConnectionFactory::create(PaperUnit startX, PaperUnit startY, PaperUnit endX, PaperUnit endY)
{
  std::vector<PaperUnit> path;
  path.push_back(startX);
  path.push_back(startY);
  path.push_back((startX+endX) / 2);
  path.push_back(endY);
  path.push_back(endX);

  return create(path);
}

Connection *ConnectionFactory::create(const std::vector<PaperUnit> &path)
{
  if( path.size() < 5 ) {
    throw std::invalid_argument("need at least 5 elements in path");
  }
  if( (path.size() % 2) != 1 ) {
    throw std::invalid_argument("need an uneven number of elements in path");
  }

  Connection *con = new Connection();

  addPoints(con, path);
  addSegments(con);

  return con;
}

void ConnectionFactory::addPoints(Connection *con, const std::vector<PaperUnit> &path)
{
  const size_t LAST_IDX = path.size()-1;

  con->start.setX(path[0]);
  con->start.setY(path[1]);
  con->end.setX(path[LAST_IDX]);
  con->end.setY(path[LAST_IDX-1]);

  for (size_t i = 1; i < path.size()-2; i += 2) {
    const PaperUnit x1 = path[i+1];
    const PaperUnit y1 = path[i];
    const PaperUnit x2 = x1;
    const PaperUnit y2 = path[i+2];

    con->intermediatePoints.emplace_back(x1, y1);
    con->intermediatePoints.emplace_back(x2, y2);
  }
}

void ConnectionFactory::addSegments(Connection *con)
{
  assert(con->intermediatePoints.size() >= 2);

  con->horizontalSegments.emplace_back(con->start, con->intermediatePoints.front());

  con->verticalSegments.emplace_back(con->intermediatePoints[0], con->intermediatePoints[1]);
  for (size_t i = 1; i < con->intermediatePoints.size()-1; i += 2) {
    IntermediatePoint &start  = con->intermediatePoints[i];
    IntermediatePoint &middle = con->intermediatePoints[i+1];
    IntermediatePoint &end    = con->intermediatePoints[i+2];
    con->horizontalSegments.emplace_back(start, middle);
    con->verticalSegments.emplace_back(middle, end);
  }

  con->horizontalSegments.emplace_back(con->intermediatePoints.back(), con->end);
}


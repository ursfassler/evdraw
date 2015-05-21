#include "ConnectionFactory.hpp"

#include <stdexcept>
#include <iterator>

Connection *ConnectionFactory::create(const std::vector<PaperUnit> &path)
{
  if( path.size() < 3 ) {
    throw std::invalid_argument("need at least 3 elements in path");
  }
  if( (path.size() % 2) != 1 ) {
    throw std::invalid_argument("need an uneven number of elements in path");
  }

  Connection *con = new Connection();

  std::vector<Endpoint *> endpoints = addPoints(con, path);
  addSegments(con, endpoints);

  return con;
}

std::vector<Endpoint *> ConnectionFactory::addPoints(Connection *con, const std::vector<PaperUnit> &path)
{
  const size_t LAST_IDX = path.size()-1;

  con->start.setX(path[0]);
  con->start.setY(path[1]);
  con->end.setX(path[LAST_IDX]);
  con->end.setY(path[LAST_IDX-1]);

  for (size_t x = 2; x < path.size()-2; x += 2) {
    const size_t y = x - 1;
    const PaperUnit xPos = path[x];
    const PaperUnit yPos = path[y];
    con->intermediatePoints.emplace_back(xPos, yPos);
  }

  return getAllEndpoints(con);
}

void ConnectionFactory::addSegments(Connection *con, const std::vector<Endpoint *> &endpoints)
{
  std::vector<Endpoint *>::const_iterator start = endpoints.begin();
  std::vector<Endpoint *>::const_iterator end = start+1;

  con->horizontalSegments.emplace_back(*start, *end);

  start++;
  end++;

  while (end != endpoints.end()) {
    con->verticalSegments.emplace_back(*start, *end);
    start++;
    end++;
    con->horizontalSegments.emplace_back(*start, *end);
    start++;
    end++;
  }
}

std::vector<Endpoint *> ConnectionFactory::getAllEndpoints(Connection *con)
{
  std::vector<Endpoint *> result;

  result.push_back(&con->start);
  for (IntermediatePoint &itr : con->intermediatePoints) {
    result.push_back(&itr);
  }
  result.push_back(&con->end);

  return result;
}

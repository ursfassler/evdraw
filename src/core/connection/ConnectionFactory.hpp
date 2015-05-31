#ifndef CONNECTIONFACTORY_HPP
#define CONNECTIONFACTORY_HPP

#include "Connection.hpp"

class ConnectionFactory
{
  public:
    static Connection *produce(PaperUnit startX, PaperUnit startY, PaperUnit endX, PaperUnit endY);
    static Connection *produce(const std::vector<PaperUnit> &path);
    static Connection *produceConstructionConnection();
    static void cleanup(Connection &connection);
    static void dispose(Connection *connection);

  private:
    static void addSegments(Connection *con);
    static Connection *produce(const std::vector<Endpoint *> &points);
    static std::vector<Endpoint *> createPointList(const std::vector<PaperUnit> &path);
};

#endif // CONNECTIONFACTORY_HPP

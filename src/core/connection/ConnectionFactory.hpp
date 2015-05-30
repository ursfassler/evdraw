#ifndef CONNECTIONFACTORY_HPP
#define CONNECTIONFACTORY_HPP

#include "Connection.hpp"

class ConnectionFactory
{
  public:
    static Connection *produce(PaperUnit startX, PaperUnit startY, PaperUnit endX, PaperUnit endY);
    static Connection *produce(const std::vector<PaperUnit> &path);
    static Connection *produce(const ConstructionConnection &prototype);
    static ConstructionConnection *produceConstructionConnection();
    static void cleanup(ConnectionBase &connection);
    static void dispose(ConnectionBase *connection);

  private:
    static void addSegments(ConnectionBase *con);
    static Connection *produce(const std::vector<Endpoint *> &points);
    static std::vector<Endpoint *> createPointList(const std::vector<PaperUnit> &path);
    static std::vector<Endpoint *> createPointList(const ConstructionConnection &prototype);
};

#endif // CONNECTIONFACTORY_HPP

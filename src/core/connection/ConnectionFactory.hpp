#ifndef CONNECTIONFACTORY_HPP
#define CONNECTIONFACTORY_HPP

#include "Connection.hpp"

class ConnectionFactory
{
  public:
    static Connection *produce(PaperUnit startX, PaperUnit startY, PaperUnit endX, PaperUnit endY);
    static Connection *produce(const std::vector<PaperUnit> &path);
    static PartialConnectionFromStart *producePartialFromStart();
    static void cleanup(ConnectionBase &connection);
    static void dispose(ConnectionBase *connection);

  private:
    static void addPoints(ConnectionBase *con, const std::vector<PaperUnit> &path);
    static void addSegments(ConnectionBase *con);
};

#endif // CONNECTIONFACTORY_HPP

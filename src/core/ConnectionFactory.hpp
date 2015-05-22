#ifndef CONNECTIONFACTORY_HPP
#define CONNECTIONFACTORY_HPP

#include "Connection.hpp"

class ConnectionFactory
{
  public:
    static Connection *produce(PaperUnit startX, PaperUnit startY, PaperUnit endX, PaperUnit endY);
    static Connection *produce(const std::vector<PaperUnit> &path);
    static void dispose(Connection *connection);

  private:
    static void addPoints(Connection *con, const std::vector<PaperUnit> &path);
    static void addSegments(Connection *con);
};

#endif // CONNECTIONFACTORY_HPP

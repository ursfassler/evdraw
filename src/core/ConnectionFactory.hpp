#ifndef CONNECTIONFACTORY_HPP
#define CONNECTIONFACTORY_HPP

#include "Connection.hpp"

class ConnectionFactory
{
  public:
    static Connection *create(PaperUnit startX, PaperUnit startY, PaperUnit endX, PaperUnit endY);
    static Connection *create(const std::vector<PaperUnit> &path);

  private:
    static void addPoints(Connection *con, const std::vector<PaperUnit> &path);
    static void addSegments(Connection *con);
};

#endif // CONNECTIONFACTORY_HPP

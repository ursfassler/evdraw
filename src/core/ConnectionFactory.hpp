#ifndef CONNECTIONFACTORY_HPP
#define CONNECTIONFACTORY_HPP

#include "Connection.hpp"

class ConnectionFactory
{
  public:
    static Connection *create(const std::vector<PaperUnit> &path);

  private:
    static std::vector<Endpoint *> addPoints(Connection *con, const std::vector<PaperUnit> &path);
    static void addSegments(Connection *con, const std::vector<Endpoint *> &endpoints);
    static std::vector<Endpoint *> getAllEndpoints(Connection *con);
};

#endif // CONNECTIONFACTORY_HPP

#ifndef CONNECTIONFACTORY_HPP
#define CONNECTIONFACTORY_HPP

#include "Connection.hpp"
#include "../types.hpp"

class ConnectionFactoryTest;

class ConnectionFactory
{
  public:
    static Connection *produce(AbstractPort *startPort, AbstractPort *endPort);
    static Connection *produce(AbstractPort *startPort, AbstractPort *endPort, const std::vector<PaperUnit> &path);
    static Connection *produceConstruction(AbstractPort *startPort, AbstractPort *endPort);
    static void cleanup(Connection &connection);
    static void dispose(Connection *connection);

  private:
    static void addSegments(Connection *con);
    static Connection *produce(AbstractPort *startPort, AbstractPort *endPort, const std::vector<Endpoint *> &points);
    static std::vector<Endpoint *> createPointList(const std::vector<PaperUnit> &path);

    friend ConnectionFactoryTest;
};

#endif // CONNECTIONFACTORY_HPP

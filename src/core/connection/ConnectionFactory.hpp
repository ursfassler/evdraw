// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef CONNECTIONFACTORY_HPP
#define CONNECTIONFACTORY_HPP

#include "Connection.hpp"
#include "../types.hpp"

class ConnectionFactoryTest;

class ConnectionFactory
{
  public:
    static Connection *produce(IPort *startPort, IPort *endPort);
    static Connection *produce(IPort *startPort, IPort *endPort, const std::vector<PaperUnit> &path);
    static Connection *produceConstruction(IPort *startPort, IPort *endPort);
    static void cleanup(Connection &connection);
    static void dispose(Connection *connection);

  private:
    static void addSegments(Connection *con);
    static Connection *produce(IPort *startPort, IPort *endPort, const std::vector<Endpoint *> &points);
    static std::vector<Endpoint *> createPointList(const std::vector<PaperUnit> &path);

    friend ConnectionFactoryTest;
};

#endif // CONNECTIONFACTORY_HPP

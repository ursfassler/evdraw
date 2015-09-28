// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ConnectionWithPortSpecification.hpp"

#include "Connection.hpp"

ConnectionWithPortSpecification::ConnectionWithPortSpecification(const IPort *aPort) :
  port(aPort)
{
}

ConnectionWithPortSpecification::ConnectionWithPortSpecification(const ConnectionWithPortSpecification &copy) :
  port(copy.port)
{
}

bool ConnectionWithPortSpecification::isSatisfiedBy(const Base *candidate) const
{
  const Connection *connection = dynamic_cast<const Connection*>(candidate);
  if (connection != nullptr)
  {
    return (connection->getStartPort() == port) ||
        (connection->getEndPort() == port);
  }

  return false;
}


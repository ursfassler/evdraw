#include "ConnectionWithPortSpecification.hpp"

#include "Connection.hpp"

ConnectionWithPortSpecification::ConnectionWithPortSpecification(const AbstractPort *aPort) :
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


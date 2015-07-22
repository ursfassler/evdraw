#ifndef CONNECTIONWITHPORTSPECIFICATION_HPP
#define CONNECTIONWITHPORTSPECIFICATION_HPP

#include "../util/DefaultSpecification.hpp"
#include "AbstractPort.hpp"

class ConnectionWithPortSpecification : public DefaultSpecification
{
  public:
    ConnectionWithPortSpecification(const AbstractPort *port);
    ConnectionWithPortSpecification(const ConnectionWithPortSpecification &copy);
    void operator=(const ConnectionWithPortSpecification &spec) = delete;

    bool isSatisfiedBy(const Base *candidate) const;

  private:
    const AbstractPort * const port;

};

#endif // CONNECTIONWITHPORTSPECIFICATION_HPP

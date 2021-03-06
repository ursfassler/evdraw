// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef CONNECTIONWITHPORTSPECIFICATION_HPP
#define CONNECTIONWITHPORTSPECIFICATION_HPP

#include "../specification/DefaultSpecification.hpp"
#include "IPort.hpp"

class ConnectionWithPortSpecification : public DefaultSpecification
{
  public:
    ConnectionWithPortSpecification(const IPort *port);
    ConnectionWithPortSpecification(const ConnectionWithPortSpecification &copy);
    void operator=(const ConnectionWithPortSpecification &spec) = delete;

    bool isSatisfiedBy(const Base *candidate) const;

  private:
    const IPort * const port;

};

#endif // CONNECTIONWITHPORTSPECIFICATION_HPP

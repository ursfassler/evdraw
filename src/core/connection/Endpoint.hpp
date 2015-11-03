// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef ENDPOINT_HPP
#define ENDPOINT_HPP

#include <list>
#include <ostream>

#include "../util/Observer.hpp"
#include "../Point.hpp"
#include "../base/Position.hpp"

class Endpoint final
{
  public:
    Endpoint(const Point &position);

    bool freeMovable() const;

    RelativePosition &getPosition();
    const RelativePosition &getPosition() const;

  private:
    RelativePosition  position;

};

std::ostream &operator<<(std::ostream &stream, const Endpoint &endpoint);


#endif

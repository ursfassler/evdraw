// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef SIMPLEPORT_HPP
#define SIMPLEPORT_HPP

#include "IPort.hpp"
#include "../base/Position.hpp"

#include <set>

class SimplePort : public IPort
{
  public:
    SimplePort();
    SimplePort(const Point &position);

    virtual void addConnectionPoint(RelativePosition *port);
    virtual void removeConnectionPoint(RelativePosition *port);
    virtual std::string getName() const;
    Point getPosition() const;
    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;

    std::set<RelativePosition*> ports;

  private:
    const Point position;
};


#endif // SIMPLEPORT_HPP

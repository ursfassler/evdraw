// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef DRAWPORT_HPP
#define DRAWPORT_HPP

#include "AbstractPort.hpp"
#include "../base/Position.hpp"

class DrawPort : public AbstractPort, public RelativePosition
{
  public:
    DrawPort(const Point &offset);
    void addConnectionPoint(RelativePosition *point);
    void removeConnectionPoint(RelativePosition *point);
    std::string getName() const;
    Point getPosition() const;
    void accept(Visitor &visitor);
    void accept(ConstVisitor &visitor) const;
};

#endif // DRAWPORT_HPP

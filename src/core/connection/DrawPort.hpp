// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef DRAWPORT_HPP
#define DRAWPORT_HPP

#include "IPort.hpp"
#include "../base/Position.hpp"

class DrawPort final :
    public IPort
{
  public:
    DrawPort(const Point &offset);
    void addConnectionPoint(RelativePosition *point) override;
    void removeConnectionPoint(RelativePosition *point) override;
    std::string getName() const override;
    RelativePosition &getPosition() override;
    void accept(Visitor &visitor) override;
    void accept(ConstVisitor &visitor) const override;

  private:
    RelativePosition position;
};

#endif // DRAWPORT_HPP

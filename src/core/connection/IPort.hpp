// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef IPORT_HPP
#define IPORT_HPP

#include "../base/Position.hpp"
#include "../visitor/VisitorClient.hpp"

class IPort :
    public VisitorClient
{
  public:
    virtual ~IPort(){}
    virtual void addConnectionPoint(RelativePosition *point) = 0;
    virtual void removeConnectionPoint(RelativePosition *point) = 0;
    virtual std::string getName() const = 0;
    virtual Point getPosition() const = 0;
};


#endif

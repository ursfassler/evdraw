// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef ABSTRACTINSTANCE_HPP
#define ABSTRACTINSTANCE_HPP

#include <string>
#include "../base/Position.hpp"
#include "../visitor/VisitorClient.hpp"
#include "../types.hpp"
#include "../component/PortType.hpp"

class IInstance :
    public VisitorClient
{
  public:
    virtual ~IInstance(){}

    virtual const std::string &getName() const = 0;
    virtual Side portSide(PortType type) const = 0;
    virtual Side connectorSide(PortType type) const = 0;
    virtual PaperUnit getWidth() const = 0;
    virtual PaperUnit getHeight() const = 0;
    virtual const std::vector<InstancePort *> &getPorts() const = 0;

};

class AbstractInstance :
    public virtual IInstance,
    public RelativePosition
{
  public:
    AbstractInstance(const Point &offset) :
      RelativePosition(offset)
    {
    }

    virtual ~AbstractInstance()
    {
    }

};

#endif // ABSTRACTINSTANCE_HPP

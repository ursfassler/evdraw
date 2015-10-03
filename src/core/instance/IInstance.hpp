// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef IINSTANCE_HPP
#define IINSTANCE_HPP

#include "InstanceObserver.h"

#include "../base/Position.hpp"
#include "../visitor/VisitorClient.hpp"
#include "../types.hpp"
#include "../component/PortType.hpp"

#include <string>

class IInstance :
    public VisitorClient,
    public ObserverCollection<InstanceObserver>
{
  public:
    virtual ~IInstance(){}

    virtual Side portSide(PortType type) const = 0;
    virtual Side connectorSide(PortType type) const = 0;
    virtual PaperUnit getWidth() const = 0;
    virtual PaperUnit getHeight() const = 0;
    virtual const std::vector<InstancePort *> &getPorts() const = 0;

};

#endif

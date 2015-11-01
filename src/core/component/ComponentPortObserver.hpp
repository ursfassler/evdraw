// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENTPORTOBSERVER_HPP
#define COMPONENTPORTOBSERVER_HPP

#include "PortType.hpp"

#include <string>

class ComponentPort;

class ComponentPortObserver
{
  public:
    virtual ~ComponentPortObserver();

    virtual void topIndexChanged(size_t index);
    virtual void nameChanged(ComponentPort *port);
    virtual void typeChanged(ComponentPort *port);

};

#endif // COMPONENTPORTOBSERVER_HPP

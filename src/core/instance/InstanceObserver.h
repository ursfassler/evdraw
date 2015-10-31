// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCEOBSERVER_H
#define INSTANCEOBSERVER_H

#include "../connection/IPort.hpp"

class IInstance;

class InstanceObserver
{
  public:
    virtual ~InstanceObserver();

    virtual void nameChanged(IInstance *instance);
    virtual void componentNameChanged(IInstance *instance);
    virtual void widthChanged();
    virtual void heightChanged();
};

#endif // INSTANCEOBSERVER_H

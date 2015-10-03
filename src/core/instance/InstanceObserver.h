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

    virtual void portAdded(IPort *port);
    virtual void portDeleted(IPort *port);
    virtual void nameChanged(const IInstance *instance);
    virtual void componentNameChanged(const IInstance *instance);
    virtual void widthChanged();
    virtual void heightChanged();
};

#endif // INSTANCEOBSERVER_H

// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstanceObserver.h"

InstanceObserver::~InstanceObserver()
{
}

void InstanceObserver::portAdded(IPort *)
{
}

void InstanceObserver::portDeleted(IPort *)
{
}

void InstanceObserver::nameChanged(const IInstance *)
{
}

void InstanceObserver::componentNameChanged(const IInstance *)
{
}

void InstanceObserver::widthChanged()
{
}

void InstanceObserver::heightChanged()
{
}

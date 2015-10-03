// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstanceObserverMock.h"



InstanceObserverMock::InstanceObserverMock(bool *aDestroyed) :
  addedPorts{},
  deletedPorts{},
  nameChanged_instance{},
  componentNameChanged_instance{},
  destroyed{aDestroyed}
{
}

InstanceObserverMock::~InstanceObserverMock()
{
  if (destroyed != nullptr) {
    *destroyed = true;
  }
}

void InstanceObserverMock::portAdded(IPort *port)
{
  addedPorts.push_back(port);
}

void InstanceObserverMock::portDeleted(IPort *port)
{
  deletedPorts.push_back(port);
}

void InstanceObserverMock::widthChanged()
{
  changedWidth++;
}

void InstanceObserverMock::heightChanged()
{
  changedHeight++;
}

void InstanceObserverMock::nameChanged(const IInstance *instance)
{
  nameChanged_instance.push_back(instance);
}

void InstanceObserverMock::componentNameChanged(const IInstance *instance)
{
  componentNameChanged_instance.push_back(instance);
}

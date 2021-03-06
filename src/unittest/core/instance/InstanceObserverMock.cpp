// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "InstanceObserverMock.h"



InstanceObserverMock::InstanceObserverMock(bool *aDestroyed) :
  destroyed(aDestroyed)
{
}

InstanceObserverMock::~InstanceObserverMock()
{
  if (destroyed != nullptr) {
    *destroyed = true;
  }
}

void InstanceObserverMock::widthChanged()
{
  changedWidth++;
}

void InstanceObserverMock::heightChanged()
{
  changedHeight++;
}

void InstanceObserverMock::nameChanged(IInstance *instance)
{
  nameChanged_instance.push_back(instance);
}

void InstanceObserverMock::componentNameChanged(IInstance *instance)
{
  componentNameChanged_instance.push_back(instance);
}

// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "CompositionObserverMock.h"



void CompositionObserverMock::finishConnectionUnderConstruction(Connection *connection)
{
  lastFinishConnectionUnderConstruction = connection;
}

void CompositionObserverMock::addConnectionUnderConstruction(Connection *connection)
{
  lastAddConnectionUnderConstruction = connection;
}

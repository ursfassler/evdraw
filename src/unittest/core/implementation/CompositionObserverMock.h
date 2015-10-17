// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPOSITIONOBSERVERMOCK_H
#define COMPOSITIONOBSERVERMOCK_H

#include <core/implementation/Composition.hpp>

class CompositionObserverMock : public CompositionObserver
{
  public:
    virtual void finishConnectionUnderConstruction(Connection *connection) override;
    virtual void addConnectionUnderConstruction(Connection *connection) override;

    Connection *lastFinishConnectionUnderConstruction = nullptr;
    Connection *lastAddConnectionUnderConstruction = nullptr;
};

#endif // COMPOSITIONOBSERVERMOCK_H

// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPOSITIONMOCK
#define COMPOSITIONMOCK

#include <core/implementation/Composition.hpp>

class CompositionMock :
    public IComposition
{
  public:
    CompositionMock(const CompositionMock&) = delete;
    CompositionMock &operator=(const CompositionMock&) = delete;

    CompositionMock(bool *destroyed = nullptr);
    ~CompositionMock();

  private:
    bool *destroyed;
};

#endif // COMPOSITIONMOCK


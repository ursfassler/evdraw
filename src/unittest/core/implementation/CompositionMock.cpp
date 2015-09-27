// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "CompositionMock.hpp"


CompositionMock::CompositionMock(bool *aDestroyed) :
  destroyed{aDestroyed}
{
}

CompositionMock::~CompositionMock()
{
  if (destroyed != nullptr) {
    *destroyed = true;
  }
}

// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPOSITIONFACTORY_HPP
#define COMPOSITIONFACTORY_HPP

#include "Composition.hpp"

class CompositionFactory
{
  public:
    static void cleanup(Composition &composition);
    static void dispose(Composition *composition);
};

#endif // COMPOSITIONFACTORY_HPP

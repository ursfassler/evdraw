// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef IMPLEMENTATIONFACTORY_HPP
#define IMPLEMENTATIONFACTORY_HPP

#include "../component/IImplementation.hpp"

class ImplementationFactory
{
  public:
    static void dispose(IImplementation *implementation);
};

#endif // IMPLEMENTATIONFACTORY_HPP

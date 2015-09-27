// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "CompositionFactoryTest.hpp"

#include "CompositionInstanceMock.hpp"

#include <core/implementation/CompositionFactory.hpp>
#include <core/implementation/Composition.hpp>


void CompositionFactoryTest::cleanup()
{
  CompositionInstanceMock *instance = new CompositionInstanceMock();
  Composition composition{instance};

  CompositionFactory::cleanup(composition);
}

void CompositionFactoryTest::dispose()
{
  CompositionInstanceMock *instance = new CompositionInstanceMock();
  Composition *composition = new Composition(instance);

  CompositionFactory::dispose(composition);
}

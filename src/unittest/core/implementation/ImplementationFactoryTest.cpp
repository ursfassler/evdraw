// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ImplementationFactoryTest.hpp"

#include "CompositionInstanceMock.hpp"

#include <core/implementation/ImplementationFactory.hpp>
#include <core/implementation/Composition.hpp>
#include <core/implementation/NullImplementation.hpp>

void ImplementationFactoryTest::destroys_composition()
{
  CompositionInstanceMock *instance = new CompositionInstanceMock();
  Composition *composition = new Composition(instance);

  ImplementationFactory::dispose(composition);
}

void ImplementationFactoryTest::destroys_null()
{
  NullImplementation *implementation = new NullImplementation();

  ImplementationFactory::dispose(implementation);

}

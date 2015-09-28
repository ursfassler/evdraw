// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "NullImplementationTest.hpp"

#include <core/implementation/NullImplementation.hpp>


void NullImplementationTest::construct()
{
  NullImplementation  implementation;
  (void)(implementation);
}

void NullImplementationTest::inheritsAbstractImplementation()
{
  NullImplementation  implementation;
  CPPUNIT_ASSERT(dynamic_cast<IImplementation*>(&implementation) != nullptr);
}

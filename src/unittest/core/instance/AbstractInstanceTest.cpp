// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "AbstractInstanceTest.hpp"
#include "InstanceMock.hpp"

#include <core/instance/AbstractInstance.hpp>
#include <core/base/Base.hpp>
#include <core/base/Position.hpp>

void AbstractInstanceTest::setUp()
{
  instance = new InstanceMock();
}

void AbstractInstanceTest::tearDown()
{
  delete instance;
  instance = nullptr;
}

void AbstractInstanceTest::destructorIsVirtual()
{
  bool destroyed = false;
  AbstractInstance *instance = new InstanceMock(&destroyed);
  delete instance;
  CPPUNIT_ASSERT(destroyed);
}

void AbstractInstanceTest::inheritsPosition()
{
  CPPUNIT_ASSERT(dynamic_cast<Position*>(instance) != nullptr);
}

void AbstractInstanceTest::hasGetName()
{
  CPPUNIT_ASSERT_EQUAL(std::string("test"), instance->getName());
}

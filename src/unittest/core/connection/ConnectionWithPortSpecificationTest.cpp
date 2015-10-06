// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ConnectionWithPortSpecificationTest.hpp"

#include "PortMock.hpp"

#include <core/connection/ConnectionWithPortSpecification.hpp>
#include <core/specification/Specification.hpp>
#include <core/connection/ConnectionFactory.hpp>

void ConnectionWithPortSpecificationTest::inheritsSpecification()
{
  ConnectionWithPortSpecification spec(nullptr);
  CPPUNIT_ASSERT(dynamic_cast<Specification*>(&spec) != nullptr);
}

void ConnectionWithPortSpecificationTest::satisfiedWithStartPort()
{
  PortMock start;
  PortMock end;
  Connection *connection = ConnectionFactory::produce(&start, &end);

  ConnectionWithPortSpecification spec(&start);

  CPPUNIT_ASSERT(spec.isSatisfiedBy(connection));

  ConnectionFactory::dispose(connection);
}

void ConnectionWithPortSpecificationTest::satisfiedWithEndPort()
{
  PortMock start;
  PortMock end;
  Connection *connection = ConnectionFactory::produce(&start, &end);

  ConnectionWithPortSpecification spec(&end);

  CPPUNIT_ASSERT(spec.isSatisfiedBy(connection));

  ConnectionFactory::dispose(connection);
}

void ConnectionWithPortSpecificationTest::notSatisfiedWithOtherPort()
{
  PortMock start;
  PortMock end;
  Connection *connection = ConnectionFactory::produce(&start, &end);

  PortMock other;
  ConnectionWithPortSpecification spec(&other);

  CPPUNIT_ASSERT(!spec.isSatisfiedBy(connection));

  ConnectionFactory::dispose(connection);
}

// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "contractTest.hpp"

#include <core/util/contract.hpp>

void contractTest::throwPrecondition()
{
  CPPUNIT_ASSERT_THROW(precondition(1==2), PreconditionError);
}

void contractTest::noThrowPrecondition()
{
  CPPUNIT_ASSERT_NO_THROW(precondition(1==1));
}

void contractTest::throwPostcondition()
{
  CPPUNIT_ASSERT_THROW(postcondition(1==2), PostconditionError);
}

void contractTest::noThrowPostcondition()
{
  CPPUNIT_ASSERT_NO_THROW(postcondition(1==1));
}

void contractTest::throwInvariant()
{
  CPPUNIT_ASSERT_THROW(invariant(1==2), InvariantError);
}

void contractTest::noThrowInvariant()
{
  CPPUNIT_ASSERT_NO_THROW(invariant(1==1));
}

// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "contractTest.hpp"

#include <core/util/contract.hpp>

void contractTest::throw_precondition()
{
  CPPUNIT_ASSERT_THROW(precondition(1==2), PreconditionError);
}

void contractTest::no_throw_precondition()
{
  CPPUNIT_ASSERT_NO_THROW(precondition(1==1));
}

void contractTest::precondition_message()
{
  std::string msg;
  try {
    precondition(1==2);
  } catch (PreconditionError e) {
    msg = e.what();
  }

  CPPUNIT_ASSERT_MESSAGE(msg, msg.find("precondition does not hold: 1==2 (precondition_message)") != std::string::npos);
}

void contractTest::throw_postcondition()
{
  CPPUNIT_ASSERT_THROW(postcondition(1==2), PostconditionError);
}

void contractTest::no_throw_postcondition()
{
  CPPUNIT_ASSERT_NO_THROW(postcondition(1==1));
}

void contractTest::postcondition_message()
{
  std::string msg;
  try {
    postcondition(1==2);
  } catch (PostconditionError e) {
    msg = e.what();
  }

  CPPUNIT_ASSERT_MESSAGE(msg, msg.find("postcondition does not hold: 1==2 (postcondition_message)") != std::string::npos);
}

void contractTest::throw_invariant()
{
  CPPUNIT_ASSERT_THROW(invariant(1==2), InvariantError);
}

void contractTest::no_throw_invariant()
{
  CPPUNIT_ASSERT_NO_THROW(invariant(1==1));
}

void contractTest::invariant_message()
{
  std::string msg;
  try {
    invariant(1==2);
  } catch (InvariantError e) {
    msg = e.what();
  }

  CPPUNIT_ASSERT_MESSAGE(msg, msg.find("invariant does not hold: 1==2 (invariant_message)") != std::string::npos);
}



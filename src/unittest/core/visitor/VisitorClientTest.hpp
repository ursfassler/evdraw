// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef VISITORCLIENTTEST_HPP
#define VISITORCLIENTTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class VisitorClientTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( VisitorClientTest );

    CPPUNIT_TEST(inheritsBase);
    CPPUNIT_TEST(acceptsVisitor);
    CPPUNIT_TEST(acceptsConstVisitor);

    CPPUNIT_TEST_SUITE_END();

  public:
    void inheritsBase();
    void acceptsVisitor();
    void acceptsConstVisitor();

};

CPPUNIT_TEST_SUITE_REGISTRATION( VisitorClientTest );

#endif

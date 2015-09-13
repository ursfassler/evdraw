// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef CONNECTORFACTORYTEST_HPP
#define CONNECTORFACTORYTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ConnectorFactoryTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ConnectorFactoryTest );

    CPPUNIT_TEST(cleanup_removes_points);
    CPPUNIT_TEST(dispose_removes_points);

    CPPUNIT_TEST_SUITE_END();

  public:
    void cleanup_removes_points();
    void dispose_removes_points();

};

CPPUNIT_TEST_SUITE_REGISTRATION( ConnectorFactoryTest );

#endif // CONNECTORFACTORYTEST_HPP

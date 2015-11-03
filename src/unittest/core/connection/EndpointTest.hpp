// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef POINTTEST_HPP
#define POINTTEST_HPP

#include <core/connection/Endpoint.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class EndpointTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( EndpointTest );

    CPPUNIT_TEST(has_position);
    CPPUNIT_TEST(is_movable_when_not_have_anchor);
    CPPUNIT_TEST(is_not_movable_when_have_anchor);

    CPPUNIT_TEST_SUITE_END();

  public:
    void has_position();
    void is_movable_when_not_have_anchor();
    void is_not_movable_when_have_anchor();

};

CPPUNIT_TEST_SUITE_REGISTRATION( EndpointTest );

#endif // POINTTEST_HPP

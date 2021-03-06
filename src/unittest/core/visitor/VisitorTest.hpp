// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef VISITORTEST_HPP
#define VISITORTEST_HPP

#include "../../testtypes.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class VisitorTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( VisitorTest );

    CPPUNIT_TEST(componentPort);
    CPPUNIT_TEST(component);

    CPPUNIT_TEST(instance);
    CPPUNIT_TEST(instancePort);

    CPPUNIT_TEST(connection);

    CPPUNIT_TEST(composition);
    CPPUNIT_TEST(compositionInstance);
    CPPUNIT_TEST(nullImplementation);

    CPPUNIT_TEST(library);

    CPPUNIT_TEST_SUITE_END();

  public:
    void componentPort();
    void component();
    void componentWithPorts();

    void instance();
    void instancePort();

    void connection();

    void composition();
    void compositionInstance();
    void nullImplementation();

    void library();
};

CPPUNIT_TEST_SUITE_REGISTRATION( VisitorTest );

#endif // VISITORTEST_HPP

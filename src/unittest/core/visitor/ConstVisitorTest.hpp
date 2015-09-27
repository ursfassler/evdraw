// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef CONSTVISITORTEST_HPP
#define CONSTVISITORTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ConstVisitorTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ConstVisitorTest );

    CPPUNIT_TEST(componentPort);
    CPPUNIT_TEST(component);
    CPPUNIT_TEST(componentWithPorts);

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

CPPUNIT_TEST_SUITE_REGISTRATION( ConstVisitorTest );

#endif // VISITORTEST_HPP

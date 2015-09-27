// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef IMPLEMENTATIONFACTORYTEST_HPP
#define IMPLEMENTATIONFACTORYTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class ImplementationFactoryTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ImplementationFactoryTest );

    CPPUNIT_TEST(destroys_composition);
    CPPUNIT_TEST(destroys_null);

    CPPUNIT_TEST_SUITE_END();

  public:
    void destroys_composition();
    void destroys_null();

};

CPPUNIT_TEST_SUITE_REGISTRATION( ImplementationFactoryTest );

#endif

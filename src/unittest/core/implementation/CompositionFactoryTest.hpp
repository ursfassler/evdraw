// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPOSITIONFACTORYTEST_HPP
#define COMPOSITIONFACTORYTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CompositionFactoryTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( CompositionFactoryTest );

    CPPUNIT_TEST(cleanup);
    CPPUNIT_TEST(dispose);

    CPPUNIT_TEST_SUITE_END();

  public:
    void cleanup();
    void dispose();

};

CPPUNIT_TEST_SUITE_REGISTRATION( CompositionFactoryTest );

#endif // COMPOSITIONFACTORYTEST_HPP

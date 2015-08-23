// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef SPECIFICATIONTEST_HPP
#define SPECIFICATIONTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class SpecificationTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( SpecificationTest );

    CPPUNIT_TEST(destructorIsVirtual);
    CPPUNIT_TEST(hasVirtualIsSatisfiedBy);
    CPPUNIT_TEST(hasVirtualOr);

    CPPUNIT_TEST_SUITE_END();

  public:
    void destructorIsVirtual();
    void hasVirtualIsSatisfiedBy();
    void hasVirtualOr();

};

CPPUNIT_TEST_SUITE_REGISTRATION( SpecificationTest );

#endif // SPECIFICATIONTEST_HPP

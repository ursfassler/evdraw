// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef IMPLEMENTATIONTYPETEST_H
#define IMPLEMENTATIONTYPETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ImplementationTypeTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ImplementationTypeTest );

    CPPUNIT_TEST(implementationTypeList_contains_empty);
    CPPUNIT_TEST(implementationTypeList_contains_composition);

    CPPUNIT_TEST(empty_toString);
    CPPUNIT_TEST(composition_toString);
    CPPUNIT_TEST(toString_is_defined_for_all);
    CPPUNIT_TEST(undefined_toString_throws_exception);

    CPPUNIT_TEST(to_ostream_is_same_as_toString);
    CPPUNIT_TEST(undefined_to_ostream_throws_exception);

    CPPUNIT_TEST(implementationTypeFromUint_matches_implementationTypeList_index);
    CPPUNIT_TEST(undefined_implementationTypeFromUint_throws_exception);

    CPPUNIT_TEST(uintFromImplementationType_matches_implementationTypeList_index);
    CPPUNIT_TEST(undefined_uintFromImplementationType_throws_exception);

    CPPUNIT_TEST_SUITE_END();

  public:
    void implementationTypeList_contains_empty();
    void implementationTypeList_contains_composition();

    void empty_toString();
    void composition_toString();
    void toString_is_defined_for_all();
    void undefined_toString_throws_exception();

    void to_ostream_is_same_as_toString();
    void undefined_to_ostream_throws_exception();

    void implementationTypeFromUint_matches_implementationTypeList_index();
    void undefined_implementationTypeFromUint_throws_exception();

    void uintFromImplementationType_matches_implementationTypeList_index();
    void undefined_uintFromImplementationType_throws_exception();

};

CPPUNIT_TEST_SUITE_REGISTRATION( ImplementationTypeTest );

#endif // IMPLEMENTATIONTYPETEST_H

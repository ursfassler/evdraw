#ifndef ALWAYSSATISFIEDSPECIFICATIONTEST_HPP
#define ALWAYSSATISFIEDSPECIFICATIONTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class AlwaysSatisfiedSpecificationTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( AlwaysSatisfiedSpecificationTest );

    CPPUNIT_TEST(inheritsSpecification);
    CPPUNIT_TEST(satisfiedOnNullptr);

    CPPUNIT_TEST_SUITE_END();

  public:
    void inheritsSpecification();
    void satisfiedOnNullptr();


};

CPPUNIT_TEST_SUITE_REGISTRATION( AlwaysSatisfiedSpecificationTest );

#endif

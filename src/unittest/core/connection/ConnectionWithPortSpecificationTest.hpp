#ifndef CONNECTIONWITHPORTSPECIFICATIONTEST_HPP
#define CONNECTIONWITHPORTSPECIFICATIONTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ConnectionWithPortSpecificationTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ConnectionWithPortSpecificationTest );

    CPPUNIT_TEST(inheritsSpecification);
    CPPUNIT_TEST(satisfiedWithStartPort);
    CPPUNIT_TEST(satisfiedWithEndPort);
    CPPUNIT_TEST(notSatisfiedWithOtherPort);

    CPPUNIT_TEST_SUITE_END();

  public:
    void inheritsSpecification();
    void satisfiedWithStartPort();
    void satisfiedWithEndPort();
    void notSatisfiedWithOtherPort();

};

CPPUNIT_TEST_SUITE_REGISTRATION( ConnectionWithPortSpecificationTest );

#endif

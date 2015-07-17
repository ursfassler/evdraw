#ifndef NULLVISITORTEST_HPP
#define NULLVISITORTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class NullVisitorTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( NullVisitorTest );

    CPPUNIT_TEST(implementsVisitor);
    CPPUNIT_TEST(implementsAllVisitMethods);

    CPPUNIT_TEST_SUITE_END();

  public:
    void implementsVisitor();
    void implementsAllVisitMethods();
};

CPPUNIT_TEST_SUITE_REGISTRATION( NullVisitorTest );

#endif

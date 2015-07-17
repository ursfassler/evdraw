#ifndef NULLCONSTVISITORTEST_HPP
#define NULLCONSTVISITORTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class NullConstVisitorTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( NullConstVisitorTest );

    CPPUNIT_TEST(implementsVisitor);
    CPPUNIT_TEST(implementsAllVisitMethods);

    CPPUNIT_TEST_SUITE_END();

  public:
    void implementsVisitor();
    void implementsAllVisitMethods();
};

CPPUNIT_TEST_SUITE_REGISTRATION( NullConstVisitorTest );

#endif

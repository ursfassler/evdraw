#ifndef DEFAULTCONSTVISITORTEST_HPP
#define DEFAULTCONSTVISITORTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class DefaultConstVisitorTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( DefaultConstVisitorTest );

    CPPUNIT_TEST(implementsVisitor);
    CPPUNIT_TEST(implementsAllVisitMethods);

    CPPUNIT_TEST_SUITE_END();

  public:
    void implementsVisitor();
    void implementsAllVisitMethods();
};

CPPUNIT_TEST_SUITE_REGISTRATION( DefaultConstVisitorTest );

#endif

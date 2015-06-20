#ifndef DEFAULTVISITORTEST_HPP
#define DEFAULTVISITORTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class DefaultVisitorTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( DefaultVisitorTest );

    CPPUNIT_TEST(implementsVisitor);
    CPPUNIT_TEST(implementsAllVisitMethods);

    CPPUNIT_TEST_SUITE_END();

  public:
    void implementsVisitor();
    void implementsAllVisitMethods();
};

CPPUNIT_TEST_SUITE_REGISTRATION( DefaultVisitorTest );

#endif // DEFAULTVISITORTEST_HPP

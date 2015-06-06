#ifndef VISITORTEST_HPP
#define VISITORTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class VisitorTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( VisitorTest );

    CPPUNIT_TEST(componentPort);
    CPPUNIT_TEST(component);
    CPPUNIT_TEST(componentWithPorts);

    CPPUNIT_TEST(instance);
    CPPUNIT_TEST(instancePort);

    CPPUNIT_TEST(connection);

    CPPUNIT_TEST(sheet);

    CPPUNIT_TEST_SUITE_END();

  public:
    void componentPort();
    void component();
    void componentWithPorts();

    void instance();
    void instancePort();

    void connection();

    void sheet();
};

CPPUNIT_TEST_SUITE_REGISTRATION( VisitorTest );

#endif // VISITORTEST_HPP

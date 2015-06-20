#ifndef VISITORTEST_HPP
#define VISITORTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class VisitorTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( VisitorTest );

    CPPUNIT_TEST(slot);
    CPPUNIT_TEST(signal);
    CPPUNIT_TEST(component);
    CPPUNIT_TEST(componentWithPorts);

    CPPUNIT_TEST(instance);
    CPPUNIT_TEST(instancePort);

    CPPUNIT_TEST(connection);

    CPPUNIT_TEST(composition);
    CPPUNIT_TEST(nullImplementation);

    CPPUNIT_TEST(library);

    CPPUNIT_TEST_SUITE_END();

  public:
    void slot();
    void signal();
    void component();
    void componentWithPorts();

    void instance();
    void instancePort();

    void connection();

    void composition();
    void nullImplementation();

    void library();
};

CPPUNIT_TEST_SUITE_REGISTRATION( VisitorTest );

#endif // VISITORTEST_HPP

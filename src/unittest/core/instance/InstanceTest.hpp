#ifndef INSTANCETEST_HPP
#define INSTANCETEST_HPP

#include <core/component/Component.hpp>
#include <core/instance/Instance.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class InstanceTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( InstanceTest );

    CPPUNIT_TEST(produce);
    CPPUNIT_TEST(setPosition);
    CPPUNIT_TEST(inheritsPosition);
    CPPUNIT_TEST(inheritsBase);

    CPPUNIT_TEST(addPort);
    CPPUNIT_TEST(delPort);

    CPPUNIT_TEST(getPortWithExisting);

    CPPUNIT_TEST(deletePortWhenComponentPortIsRemoved);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void produce();
    void setPosition();
    void inheritsPosition();
    void inheritsBase();

    void addPort();
    void delPort();

    void getPortWithExisting();

    void deletePortWhenComponentPortIsRemoved();

  private:
    Component *component = nullptr;
    Instance *instance = nullptr;

};

CPPUNIT_TEST_SUITE_REGISTRATION( InstanceTest );

#endif // INSTANCETEST_HPP

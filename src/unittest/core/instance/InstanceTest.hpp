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
    CPPUNIT_TEST(updatePositionOnIndexChange);
    CPPUNIT_TEST(inheritsPosition);
    CPPUNIT_TEST(inheritsBase);

    CPPUNIT_TEST(getPortWithExisting);
    CPPUNIT_TEST(getPortForNonExistingThrowsError);

    CPPUNIT_TEST(addPortWhenComponentPortIsAdded);
    CPPUNIT_TEST(deletePortWhenComponentPortIsDeleted);

    CPPUNIT_TEST(updatePortPositionsOnPortDelete);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void produce();
    void setPosition();
    void updatePositionOnIndexChange();
    void inheritsPosition();
    void inheritsBase();

    void getPortWithExisting();
    void getPortForNonExistingThrowsError();

    void addPortWhenComponentPortIsAdded();
    void deletePortWhenComponentPortIsDeleted();

    void updatePortPositionsOnPortDelete();

  private:
    Component *component = nullptr;
    Instance *instance = nullptr;

};

CPPUNIT_TEST_SUITE_REGISTRATION( InstanceTest );

#endif // INSTANCETEST_HPP

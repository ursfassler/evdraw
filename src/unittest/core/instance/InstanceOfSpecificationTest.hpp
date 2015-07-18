#ifndef INSTANCEOFSPECIFICATIONTEST_HPP
#define INSTANCEOFSPECIFICATIONTEST_HPP

#include <core/instance/Instance.hpp>
#include <core/component/Component.hpp>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class InstanceOfSpecificationTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( InstanceOfSpecificationTest );

    CPPUNIT_TEST(inheritsSpecification);
    CPPUNIT_TEST(copyConstructor);
    CPPUNIT_TEST(assignOperator);

    CPPUNIT_TEST(satisfied);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void inheritsSpecification();
    void copyConstructor();
    void assignOperator();

    void satisfied();

  private:
    Component *component = nullptr;
    Instance *instance = nullptr;
};

CPPUNIT_TEST_SUITE_REGISTRATION( InstanceOfSpecificationTest );

#endif

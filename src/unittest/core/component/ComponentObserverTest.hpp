#ifndef COMPONENTOBSERVERTEST_HPP
#define COMPONENTOBSERVERTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ComponentObserverTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ComponentObserverTest );

    CPPUNIT_TEST(destructorIsVirtual);
    CPPUNIT_TEST(inheritsObserverCollection);

    CPPUNIT_TEST(getInformedOnAdd);
    CPPUNIT_TEST(getInformedOnDelete);

    CPPUNIT_TEST_SUITE_END();

  public:
    void destructorIsVirtual();
    void inheritsObserverCollection();

    void getInformedOnAdd();
    void getInformedOnDelete();

};

CPPUNIT_TEST_SUITE_REGISTRATION( ComponentObserverTest );

#endif // COMPONENTOBSERVERTEST_H

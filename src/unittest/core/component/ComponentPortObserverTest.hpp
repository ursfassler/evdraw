#ifndef COMPONENTPORTOBSERVERTEST_HPP
#define COMPONENTPORTOBSERVERTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ComponentPortObserverTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ComponentPortObserverTest );

    CPPUNIT_TEST(destructorIsVirtual);
    CPPUNIT_TEST(inheritsObserverCollection);

    CPPUNIT_TEST(getInformedOnTopIndexChange);
    CPPUNIT_TEST(doNotInformIfTopIndexIsTheSame);

    CPPUNIT_TEST_SUITE_END();

  public:
    void destructorIsVirtual();
    void inheritsObserverCollection();

    void getInformedOnTopIndexChange();
    void doNotInformIfTopIndexIsTheSame();

};

CPPUNIT_TEST_SUITE_REGISTRATION( ComponentPortObserverTest );

#endif // COMPONENTPORTOBSERVERTEST_HPP

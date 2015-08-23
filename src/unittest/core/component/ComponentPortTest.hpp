#ifndef COMPONENTPORTTEST_HPP
#define COMPONENTPORTTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ComponentPortTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ComponentPortTest );

    CPPUNIT_TEST(destructor_is_virtual);
    CPPUNIT_TEST(name);
    CPPUNIT_TEST(setTopIndex);

    CPPUNIT_TEST(setName);

    CPPUNIT_TEST_SUITE_END();

  public:
    void destructor_is_virtual();
    void name();
    void setTopIndex();

    void setName();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ComponentPortTest );

class SignalTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( SignalTest );

    CPPUNIT_TEST(produce);
    CPPUNIT_TEST(portIsRight);

    CPPUNIT_TEST_SUITE_END();

  public:
    void produce();
    void portIsRight();

};

CPPUNIT_TEST_SUITE_REGISTRATION( SignalTest );

class SlotTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( SlotTest );

    CPPUNIT_TEST(produce);
    CPPUNIT_TEST(portIsLeft);

    CPPUNIT_TEST_SUITE_END();

  public:
    void produce();
    void portIsLeft();
};

CPPUNIT_TEST_SUITE_REGISTRATION( SlotTest );

#endif // COMPONENTPORTTEST_HPP

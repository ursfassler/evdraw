#ifndef COMPONENTPORTTEST_HPP
#define COMPONENTPORTTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ComponentPortTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ComponentPortTest );

    CPPUNIT_TEST(setTopIndex);

    CPPUNIT_TEST_SUITE_END();

  public:
    void setTopIndex();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ComponentPortTest );

class SignalTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( SignalTest );

    CPPUNIT_TEST(produce);

    CPPUNIT_TEST_SUITE_END();

  public:
    void produce();
};

CPPUNIT_TEST_SUITE_REGISTRATION( SignalTest );

class SlotTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( SlotTest );

    CPPUNIT_TEST(produce);

    CPPUNIT_TEST_SUITE_END();

  public:
    void produce();
};

CPPUNIT_TEST_SUITE_REGISTRATION( SlotTest );

#endif // COMPONENTPORTTEST_HPP

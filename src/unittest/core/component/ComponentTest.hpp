#ifndef COMPONENTTEST_HPP
#define COMPONENTTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ComponentTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ComponentTest );

    CPPUNIT_TEST(produce);

    CPPUNIT_TEST(addSlot);
    CPPUNIT_TEST(addSignal);
    CPPUNIT_TEST(delPort);
    CPPUNIT_TEST(signalSlotCanBeInterleaved);
    CPPUNIT_TEST(rightPortIndexUpdatedOnAdd);
    CPPUNIT_TEST(leftPortIndexUpdatedOnAdd);
    CPPUNIT_TEST(portIndexUpdatedOnDel);

    CPPUNIT_TEST(portIsLeft);
    CPPUNIT_TEST(portIsRight);

    CPPUNIT_TEST(constructWithOwnImplementation);
    CPPUNIT_TEST(componentDeletesImplementationWhenDeleted);
    CPPUNIT_TEST(setImplementation);
    CPPUNIT_TEST(setImplementationDeletesOldOne);

    CPPUNIT_TEST(heightOfEmptyComponent);
    CPPUNIT_TEST(heightOf2Slots);
    CPPUNIT_TEST(heightOf2Signals);
    CPPUNIT_TEST(heightOf2SlotsAnd3Signals);
    CPPUNIT_TEST(heightOf2SignalsAnd3Slots);

    CPPUNIT_TEST_SUITE_END();

  public:
    void produce();

    void addSlot();
    void addSignal();
    void delPort();
    void signalSlotCanBeInterleaved();

    void rightPortIndexUpdatedOnAdd();
    void leftPortIndexUpdatedOnAdd();
    void portIndexUpdatedOnDel();

    void portIsLeft();
    void portIsRight();

    void constructWithOwnImplementation();
    void componentDeletesImplementationWhenDeleted();
    void setImplementation();
    void setImplementationDeletesOldOne();

    void heightOfEmptyComponent();
    void heightOf2Slots();
    void heightOf2Signals();
    void heightOf2SlotsAnd3Signals();
    void heightOf2SignalsAnd3Slots();

};

CPPUNIT_TEST_SUITE_REGISTRATION( ComponentTest );

#endif // COMPONENTTEST_HPP

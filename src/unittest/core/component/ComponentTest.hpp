#ifndef COMPONENTTEST_HPP
#define COMPONENTTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ComponentTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ComponentTest );

    CPPUNIT_TEST(produce);

    CPPUNIT_TEST(addPortLeft);
    CPPUNIT_TEST(addPortRight);
    CPPUNIT_TEST(rightPortIndexUpdatedOnAdd);
    CPPUNIT_TEST(leftPortIndexUpdatedOnAdd);

    CPPUNIT_TEST(portIsLeft);
    CPPUNIT_TEST(portIsRight);

    CPPUNIT_TEST(defaultImplementationIsNullImplementation);
    CPPUNIT_TEST(constructWithOwnImplementation);
    CPPUNIT_TEST(componentDeletesImplementationWhenDeleted);
    CPPUNIT_TEST(setImplementation);
    CPPUNIT_TEST(setImplementationDeletesOldOne);

    CPPUNIT_TEST_SUITE_END();

  public:
    void produce();

    void addPortLeft();
    void addPortRight();

    void rightPortIndexUpdatedOnAdd();
    void leftPortIndexUpdatedOnAdd();

    void portIsLeft();
    void portIsRight();

    void defaultImplementationIsNullImplementation();
    void constructWithOwnImplementation();
    void componentDeletesImplementationWhenDeleted();
    void setImplementation();
    void setImplementationDeletesOldOne();

};

CPPUNIT_TEST_SUITE_REGISTRATION( ComponentTest );

#endif // COMPONENTTEST_HPP

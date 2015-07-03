#ifndef COMPOSITIONTEST_HPP
#define COMPOSITIONTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CompositionTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( CompositionTest );

    CPPUNIT_TEST(create);
    CPPUNIT_TEST(addInstance);
    CPPUNIT_TEST(addConnection);
    CPPUNIT_TEST(inheritsImplementation);

    CPPUNIT_TEST(getInstance);

    CPPUNIT_TEST(removeConnection);

    CPPUNIT_TEST(notifyWhenAddInstance);
    CPPUNIT_TEST(notifyWhenAddConnection);
    CPPUNIT_TEST(notifyWhenRemoveConnection);
    CPPUNIT_TEST(addConnectionUnderConstructionNotifiesObserver);
    CPPUNIT_TEST(canNotOverwriteConnectionUnderConstructio);

    CPPUNIT_TEST(finishConnectionCreation);

    CPPUNIT_TEST_SUITE_END();

  public:
    void create();
    void addInstance();
    void addConnection();
    void inheritsImplementation();

    void getInstance();

    void removeConnection();

    void notifyWhenAddInstance();
    void notifyWhenAddConnection();
    void notifyWhenRemoveConnection();
    void addConnectionUnderConstructionNotifiesObserver();
    void canNotOverwriteConnectionUnderConstructio();

    void finishConnectionCreation();

};

CPPUNIT_TEST_SUITE_REGISTRATION( CompositionTest );


#endif

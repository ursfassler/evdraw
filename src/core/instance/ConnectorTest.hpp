#ifndef CONNECTORTEST_HPP
#define CONNECTORTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ConnectorTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ConnectorTest );

    CPPUNIT_TEST(create);
    CPPUNIT_TEST(addPortPoint);
    CPPUNIT_TEST(addPortPointUpdatesPosition);
    CPPUNIT_TEST(positionOfPortIsWithinHeight);

    CPPUNIT_TEST(setNewOffset);
    CPPUNIT_TEST(setOffsetUpdatesPortPoint);
    CPPUNIT_TEST(notificationUpdatesPortPoint);

    CPPUNIT_TEST(addConnectionStart);
    CPPUNIT_TEST(addConnectionEnd);

    CPPUNIT_TEST_SUITE_END();

  public:
    void create();
    void addPortPoint();
    void addPortPointUpdatesPosition();
    void positionOfPortIsWithinHeight();

    void setNewOffset();
    void setOffsetUpdatesPortPoint();
    void notificationUpdatesPortPoint();

    void addConnectionStart();
    void addConnectionEnd();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ConnectorTest );


#endif // CONNECTORTEST_HPP

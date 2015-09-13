// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

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
    CPPUNIT_TEST(removePortPoint);
    CPPUNIT_TEST(removePortPointUpdatesPosition);

    CPPUNIT_TEST(setNewOffset);
    CPPUNIT_TEST(setOffsetUpdatesPortPoint);
    CPPUNIT_TEST(notificationUpdatesPortPoint);

    CPPUNIT_TEST_SUITE_END();

  public:
    void create();

    void addPortPoint();
    void addPortPointUpdatesPosition();
    void positionOfPortIsWithinHeight();
    void removePortPoint();
    void removePortPointUpdatesPosition();

    void setNewOffset();
    void setOffsetUpdatesPortPoint();
    void notificationUpdatesPortPoint();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ConnectorTest );


#endif // CONNECTORTEST_HPP

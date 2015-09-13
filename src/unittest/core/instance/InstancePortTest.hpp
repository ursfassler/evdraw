// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCEPORTTEST_HPP
#define INSTANCEPORTTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class InstancePortTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( InstancePortTest );

    CPPUNIT_TEST(createPort);
    CPPUNIT_TEST(offset);
    CPPUNIT_TEST(absolutePosition);
    CPPUNIT_TEST(position_change_notification_notifies_connector);
    CPPUNIT_TEST(port_is_Slot);
    CPPUNIT_TEST(port_is_Signal);

    CPPUNIT_TEST(type_change_changes_position);
    CPPUNIT_TEST(type_change_notifies_connector);

    CPPUNIT_TEST(addConnectionPoint_sets_position);
    CPPUNIT_TEST(removeConnectionPoint_changes_position_of_others);

    CPPUNIT_TEST_SUITE_END();

  public:
    void createPort();
    void offset();
    void absolutePosition();
    void position_change_notification_notifies_connector();
    void port_is_Slot();
    void port_is_Signal();
    void setName();

    void type_change_changes_position();
    void type_change_notifies_connector();

    void addConnectionPoint_sets_position();
    void removeConnectionPoint_changes_position_of_others();

};

CPPUNIT_TEST_SUITE_REGISTRATION( InstancePortTest );

#endif // INSTANCEPORTTEST_HPP

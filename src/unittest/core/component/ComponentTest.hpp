// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef COMPONENTTEST_HPP
#define COMPONENTTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ComponentTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ComponentTest );

    CPPUNIT_TEST(produce);

    CPPUNIT_TEST(setName);

    CPPUNIT_TEST(addSlot);
    CPPUNIT_TEST(addSignal);
    CPPUNIT_TEST(delPort);
    CPPUNIT_TEST(signalSlotCanBeInterleaved);
    CPPUNIT_TEST(rightPortIndexUpdatedOnAdd);
    CPPUNIT_TEST(leftPortIndexUpdatedOnAdd);
    CPPUNIT_TEST(portIndexUpdatedOnDel);
    CPPUNIT_TEST(port_index_update_on_type_change);
    CPPUNIT_TEST(port_index_update_on_type_change_with_signals_and_slots);

    CPPUNIT_TEST(getPort);
    CPPUNIT_TEST(getPortForNonExistingThrowsError);

    CPPUNIT_TEST(constructWithOwnImplementation);
    CPPUNIT_TEST(componentDeletesImplementationWhenDeleted);
    CPPUNIT_TEST(setImplementation);
    CPPUNIT_TEST(setImplementationDeletesOldOne);

    CPPUNIT_TEST(port_side_of_slot_is_left);
    CPPUNIT_TEST(port_side_of_signal_is_right);

    CPPUNIT_TEST(empty_component_has_0_ports);
    CPPUNIT_TEST(two_slots_result_in_2_max_port_count);
    CPPUNIT_TEST(two_signals_result_in_2_max_port_count);
    CPPUNIT_TEST(two_slots_and_three_signals_result_in_3_max_port_count);
    CPPUNIT_TEST(thre_slots_and_two_signals_result_in_3_max_port_count);

    CPPUNIT_TEST_SUITE_END();

  public:
    void produce();

    void setName();

    void addSlot();
    void addSignal();
    void delPort();
    void signalSlotCanBeInterleaved();

    void rightPortIndexUpdatedOnAdd();
    void leftPortIndexUpdatedOnAdd();
    void portIndexUpdatedOnDel();
    void port_index_update_on_type_change();
    void port_index_update_on_type_change_with_signals_and_slots();

    void getPort();
    void getPortForNonExistingThrowsError();

    void constructWithOwnImplementation();
    void componentDeletesImplementationWhenDeleted();
    void setImplementation();
    void setImplementationDeletesOldOne();

    void port_side_of_slot_is_left();
    void port_side_of_signal_is_right();

    void empty_component_has_0_ports();
    void two_slots_result_in_2_max_port_count();
    void two_signals_result_in_2_max_port_count();
    void two_slots_and_three_signals_result_in_3_max_port_count();
    void thre_slots_and_two_signals_result_in_3_max_port_count();

};

CPPUNIT_TEST_SUITE_REGISTRATION( ComponentTest );

#endif // COMPONENTTEST_HPP

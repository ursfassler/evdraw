// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef LISTTEST_H
#define LISTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ListTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ListTest );

    CPPUNIT_TEST(new_list_is_empty);
    CPPUNIT_TEST(can_create_list_with_initializer_list);
    CPPUNIT_TEST(not_allowed_to_create_with_same_item_multiple_times);

    CPPUNIT_TEST(can_access_by_index);
    CPPUNIT_TEST(can_ask_if_a_value_is_in_list);
    CPPUNIT_TEST(can_return_all_values_by_predicate);
    CPPUNIT_TEST(can_return_value_by_predicate);
    CPPUNIT_TEST(throw_error_if_value_is_not_found);
    CPPUNIT_TEST(can_retrieve_first_element);
    CPPUNIT_TEST(can_retrieve_last_element);
    CPPUNIT_TEST(can_ask_for_index_of_item);
    CPPUNIT_TEST(can_loop_over_list);

    CPPUNIT_TEST(add_entry_to_list_increases_size);
    CPPUNIT_TEST(can_not_add_item_multiple_times);
    CPPUNIT_TEST(remove_entry);
    CPPUNIT_TEST(can_remove_all_at_once);
    CPPUNIT_TEST(call_disposer_when_removing_item);
    CPPUNIT_TEST(call_disposer_when_delete_list);

    CPPUNIT_TEST(get_notified_when_a_new_element_is_added);
    CPPUNIT_TEST(get_notified_when_a_element_is_removed);
    CPPUNIT_TEST(get_notified_when_all_elements_are_removed);

    CPPUNIT_TEST_SUITE_END();

  public:
    void new_list_is_empty();
    void can_create_list_with_initializer_list();
    void not_allowed_to_create_with_same_item_multiple_times();

    void can_access_by_index();
    void can_ask_if_a_value_is_in_list();
    void can_return_all_values_by_predicate();
    void can_return_value_by_predicate();
    void throw_error_if_value_is_not_found();
    void can_retrieve_first_element();
    void can_retrieve_last_element();
    void can_ask_for_index_of_item();
    void can_loop_over_list();

    void add_entry_to_list_increases_size();
    void can_not_add_item_multiple_times();
    void remove_entry();
    void can_remove_all_at_once();
    void call_disposer_when_removing_item();
    void call_disposer_when_delete_list();

    void get_notified_when_a_new_element_is_added();
    void get_notified_when_a_element_is_removed();
    void get_notified_when_all_elements_are_removed();

  private:
    int *num(int value) const;

};

CPPUNIT_TEST_SUITE_REGISTRATION( ListTest );

#endif // LISTTEST_H

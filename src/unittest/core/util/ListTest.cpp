// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ListTest.h"

#include "ListObserverMock.h"
#include "DestructorCallCheck.h"

#include <core/util/List.hpp>
#include <core/util/stdlist.hpp>

void ListTest::new_list_is_empty()
{
  const List<int> list{};

  CPPUNIT_ASSERT_EQUAL(size_t(0), list.size());
  CPPUNIT_ASSERT(list.empty());
}

void ListTest::can_create_list_with_initializer_list()
{
  const List<int> list{num(10), num(2), num(-4), num(11), num(10)};

  CPPUNIT_ASSERT_EQUAL(size_t(5), list.size());
  CPPUNIT_ASSERT(!list.empty());
}

void ListTest::not_allowed_to_create_with_same_item_multiple_times()
{
  int num = 42;

  CPPUNIT_ASSERT_THROW(new List<int>({&num, &num}), std::invalid_argument);
  CPPUNIT_ASSERT_THROW(new List<int>([](int*){}, {&num, &num}), std::invalid_argument);
}

void ListTest::can_access_by_index()
{
  int *num0 = num(10);
  int *num1 = num( 2);
  int *num2 = num(-4);
  int *num3 = num(11);
  int *num4 = num(10);
  const List<int> testee{num0, num1, num2, num3, num4};

  CPPUNIT_ASSERT_EQUAL(num0, testee[0]);
  CPPUNIT_ASSERT_EQUAL(num1, testee[1]);
  CPPUNIT_ASSERT_EQUAL(num2, testee[2]);
  CPPUNIT_ASSERT_EQUAL(num3, testee[3]);
  CPPUNIT_ASSERT_EQUAL(num4, testee[4]);
}

void ListTest::add_entry_to_list_increases_size()
{
  List<int> list{};

  list.add(num(10));

  CPPUNIT_ASSERT_EQUAL(size_t(1), list.size());
}

void ListTest::can_not_add_item_multiple_times()
{
  int *item = num(10);
  List<int> testee{item};

  CPPUNIT_ASSERT_THROW(testee.add(item), std::invalid_argument);
}

void ListTest::remove_entry()
{
  bool destructorCalledFor0 = false;
  DestructorCallCheck *num0 = new DestructorCallCheck(&destructorCalledFor0);
  bool destructorCalledFor1 = false;
  DestructorCallCheck *num1 = new DestructorCallCheck(&destructorCalledFor1);
  bool destructorCalledFor2 = false;
  DestructorCallCheck *num2 = new DestructorCallCheck(&destructorCalledFor2);
  List<DestructorCallCheck> testee{num0, num1, num2};

  testee.remove(num1);

  CPPUNIT_ASSERT_EQUAL(size_t(2), testee.size());

  CPPUNIT_ASSERT_EQUAL(false, destructorCalledFor0);
  CPPUNIT_ASSERT_EQUAL(true,  destructorCalledFor1);
  CPPUNIT_ASSERT_EQUAL(false, destructorCalledFor2);
}

void ListTest::can_ask_if_a_value_is_in_list()
{
  int *num0 = num(10);
  int *num1 = num( 2);
  int *num2 = num(-4);
  int num3 = 11;
  int num4 = 10;
  const List<int> testee{num0, num1, num2};

  CPPUNIT_ASSERT_EQUAL(true, testee.contains(num0));
  CPPUNIT_ASSERT_EQUAL(true, testee.contains(num1));
  CPPUNIT_ASSERT_EQUAL(true, testee.contains(num2));

  CPPUNIT_ASSERT_EQUAL(false, testee.contains(&num3));
  CPPUNIT_ASSERT_EQUAL(false, testee.contains(&num4));
  CPPUNIT_ASSERT_EQUAL(false, testee.contains(nullptr));
}

void ListTest::can_return_all_values_by_predicate()
{
  int *num0 = num(10);
  int *num1 = num( 2);
  int *num2 = num(-4);
  int *num3 = num(11);
  int *num4 = num(10);
  const List<int> testee{num0, num1, num2, num3, num4};
  const auto predicate = [](const int *value) ->bool {
    return *value == 10;
  };

  const auto list = testee.getAll(predicate);

  CPPUNIT_ASSERT_EQUAL(size_t(2), list.size());
  CPPUNIT_ASSERT_EQUAL(num0, list[0]);
  CPPUNIT_ASSERT_EQUAL(num4, list[1]);
}

void ListTest::can_return_value_by_predicate()
{
  int *num0 = num(10);
  int *num1 = num( 2);
  int *num2 = num(-4);
  int *num3 = num(11);
  int *num4 = num(10);
  const List<int> testee{num0, num1, num2, num3, num4};
  const auto predicate = [](const int *value) ->bool {
    return *value == 11;
  };

  CPPUNIT_ASSERT_EQUAL(num3, testee.get(predicate));
}

void ListTest::throw_error_if_value_is_not_found()
{
  const List<int> list{};
  const auto predicate = [](const int*) ->bool {
    return false;
  };

  CPPUNIT_ASSERT_THROW(list.get(predicate), std::invalid_argument);
}

void ListTest::can_retrieve_first_element()
{
  int *num0 = num(10);
  int *num1 = num( 2);
  int *num2 = num(-4);
  int *num3 = num(11);
  int *num4 = num(10);
  const List<int> testee{num0, num1, num2, num3, num4};

  CPPUNIT_ASSERT_EQUAL(num0, testee.front());
}

void ListTest::can_retrieve_last_element()
{
  int *num0 = num(10);
  int *num1 = num( 2);
  int *num2 = num(-4);
  int *num3 = num(11);
  int *num4 = num(10);
  const List<int> testee{num0, num1, num2, num3, num4};

  CPPUNIT_ASSERT_EQUAL(num4, testee.back());
}

void ListTest::can_remove_all_at_once()
{
  List<int> testee{num(10), num(2), num(-4), num(11), num(10)};

  testee.clear();

  CPPUNIT_ASSERT_EQUAL(size_t(0), testee.size());
}

void ListTest::call_disposer_when_removing_item()
{
  size_t destroyed = 0;
  auto disposer = [&destroyed](int* disposal) {
    delete disposal;
    destroyed++;
  };

  int *num0 = num(10);
  int *num1 = num( 2);
  int *num2 = num(-4);
  int *num3 = num(11);
  int *num4 = num(10);
  List<int> testee{disposer, {num0, num1, num2, num3, num4}};

  testee.remove(num1);
  testee.remove(num4);

  CPPUNIT_ASSERT_EQUAL(size_t(2), destroyed);
}

void ListTest::call_disposer_when_delete_list()
{
  size_t destroyed = 0;
  auto disposer = [&destroyed](int* disposal) {
    delete disposal;
    destroyed++;
  };
  List<int> *testee = new List<int>{disposer, {num(10), num( 2), num(-4), num(11), num(10)}};

  delete testee;

  CPPUNIT_ASSERT_EQUAL(size_t(5), destroyed);
}

void ListTest::can_ask_for_index_of_item()
{
  int *num0 = num(10);
  int *num1 = num( 2);
  int *num2 = num(-4);
  int *num3 = num(11);
  int *num4 = num(10);
  const List<int> testee{num0, num1, num2, num3, num4};

  CPPUNIT_ASSERT_EQUAL(size_t(0), testee.indexOf(num0));
  CPPUNIT_ASSERT_EQUAL(size_t(1), testee.indexOf(num1));
  CPPUNIT_ASSERT_EQUAL(size_t(2), testee.indexOf(num2));
  CPPUNIT_ASSERT_EQUAL(size_t(3), testee.indexOf(num3));
  CPPUNIT_ASSERT_EQUAL(size_t(4), testee.indexOf(num4));
  CPPUNIT_ASSERT_THROW(testee.indexOf(nullptr), std::invalid_argument);
}

void ListTest::can_loop_over_list()
{
  const List<int> testee{num(10), num(2), num(-4), num(11), num(10)};

  int sum = 0;
  for (const int *itr : testee) {
    sum += *itr;
  }

  CPPUNIT_ASSERT_EQUAL(29, sum);
}

void ListTest::get_notified_when_a_new_element_is_added()
{
    List<int> testee{};
    ListObserverMock<int> observer;
    testee.registerObserver(&observer);

    int *item = num(10);
    testee.add(item);

    CPPUNIT_ASSERT_EQUAL(size_t(1), observer.addedValue.size());
    CPPUNIT_ASSERT_EQUAL(item, observer.addedValue[0]);

    testee.unregisterObserver(&observer);
}

void ListTest::get_notified_when_a_element_is_removed()
{
  int *item = num(10);
  List<int> testee{item};
  ListObserverMock<int> observer;
  testee.registerObserver(&observer);

  testee.remove(item);

  CPPUNIT_ASSERT_EQUAL(size_t(1), observer.removedValue.size());
  CPPUNIT_ASSERT_EQUAL(item, observer.removedValue[0]);

  testee.unregisterObserver(&observer);
}

void ListTest::get_notified_when_all_elements_are_removed()
{
  int *item0 = num(10);
  int *item1 = num( 2);
  int *item2 = num(-4);
  List<int> testee{item0, item1, item2};
  ListObserverMock<int> observer;
  testee.registerObserver(&observer);

  testee.clear();

  const auto &removed = observer.removedValue;
  CPPUNIT_ASSERT(contains(removed.begin(), removed.end(), item0));
  CPPUNIT_ASSERT(contains(removed.begin(), removed.end(), item1));
  CPPUNIT_ASSERT(contains(removed.begin(), removed.end(), item2));

  testee.unregisterObserver(&observer);
}

int *ListTest::num(int value) const
{
  int *ptr = new int;
  *ptr = value;
  return ptr;
}

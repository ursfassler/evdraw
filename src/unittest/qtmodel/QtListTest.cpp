// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "QtListTest.hpp"

#include <QSignalSpy>

void QtListTest::setUp()
{
  list = new List<int>();
  item = new QtItemIntMock();
  testee = new QtList<int>(*list, item);
}

void QtListTest::tearDown()
{
  delete testee;
  delete list;
}


void QtListTest::inherits_QAbstractListModel()
{
  CPPUNIT_ASSERT(dynamic_cast<QAbstractListModel*>(testee) != nullptr);
}

void QtListTest::registers_existing_items_from_list()
{
  List<int> list{new int, new int};
  QtItemIntMock *item = new QtItemIntMock();

  QtList<int> testee{list, item};

  CPPUNIT_ASSERT_EQUAL(size_t(2), item->added_item.size());
}

void QtListTest::can_get_itemModel()
{
  CPPUNIT_ASSERT(testee->getItemModel() != nullptr);
}

void QtListTest::get_rowCount_from_list()
{
  list->add(new int);
  list->add(new int);
  list->add(new int);

  CPPUNIT_ASSERT_EQUAL(3, testee->rowCount());
}

void QtListTest::get_columnCount_from_item()
{
  item->columnCount_return = 42;

  CPPUNIT_ASSERT_EQUAL(42, testee->columnCount());
  CPPUNIT_ASSERT_EQUAL(unsigned(1), item->columnCount_called);
}

void QtListTest::can_get_index_by_item()
{
  item->columnCount_return = 1;

  int *a = new int();
  int *b = new int();
  int *c = new int();

  list->add(a);
  list->add(b);
  list->add(c);

  CPPUNIT_ASSERT_EQUAL(0, testee->getIndex(a).row());
  CPPUNIT_ASSERT_EQUAL(1, testee->getIndex(b).row());
  CPPUNIT_ASSERT_EQUAL(2, testee->getIndex(c).row());
}

void QtListTest::sets_editable_flags()
{
  list->add(new int);
  list->add(new int);
  list->add(new int);
  item->columnCount_return = 42;

  item->editable_return = true;
  CPPUNIT_ASSERT_EQUAL(int(Qt::EditRole), Qt::EditRole & testee->flags(testee->index(0, 10)));
  CPPUNIT_ASSERT_EQUAL(10, item->editable_column);

  item->editable_return = false;
  CPPUNIT_ASSERT_EQUAL(0, Qt::EditRole & testee->flags(testee->index(0, 15)));
  CPPUNIT_ASSERT_EQUAL(15, item->editable_column);
}

void QtListTest::get_headerData_from_item()
{
  testee->headerData(0, Qt::Horizontal, 0);

  CPPUNIT_ASSERT_EQUAL(unsigned(1), item->headerData_called);
}

void QtListTest::get_data_from_item()
{
  item->columnCount_return = 10;
  list->add(new int);

  testee->data(testee->index(0, 9));

  CPPUNIT_ASSERT_EQUAL(unsigned(1), item->data_called);
}

void QtListTest::set_data_to_item()
{
  item->columnCount_return = 10;
  list->add(new int);

  testee->setData(testee->index(0, 8), 42);

  CPPUNIT_ASSERT_EQUAL(unsigned(1), item->setData_called);
}

void QtListTest::reacts_on_added_items()
{
  QSignalSpy spy{testee, SIGNAL(layoutChanged())};
  int *a = new int;

  list->add(a);

  CPPUNIT_ASSERT_EQUAL(1, spy.count());
  CPPUNIT_ASSERT_EQUAL(size_t(1), item->added_item.size());
  CPPUNIT_ASSERT_EQUAL(a, item->added_item[0]);
}

void QtListTest::reacts_on_removed_items()
{
  int* a = new int;
  list->add(a);

  QSignalSpy spy{testee, SIGNAL(layoutChanged())};

  list->remove(a);

  CPPUNIT_ASSERT_EQUAL(1, spy.count());
  CPPUNIT_ASSERT_EQUAL(size_t(1), item->removed_item.size());
  CPPUNIT_ASSERT_EQUAL(a, item->removed_item[0]);
}

void QtListTest::get_notified_on_column_change()
{
  QSignalSpy spy{testee, SIGNAL(dataChanged(QModelIndex,QModelIndex))};

  int *a = new int();
  int *b = new int();
  int *c = new int();
  list->add(a);
  list->add(b);
  list->add(c);

  item->columnCount_return = 10;

  item->change(b, 5);

  CPPUNIT_ASSERT_EQUAL(1, spy.count());
  const auto args = spy[0];
  CPPUNIT_ASSERT_EQUAL(2, args.size());
  CPPUNIT_ASSERT(args[0].canConvert<QModelIndex>());
  CPPUNIT_ASSERT(args[1].canConvert<QModelIndex>());
  const QModelIndex topLeft = args[0].toModelIndex();
  const QModelIndex bottomRight = args[1].toModelIndex();
  CPPUNIT_ASSERT_EQUAL(1, topLeft.row());
  CPPUNIT_ASSERT_EQUAL(5, topLeft.column());
  CPPUNIT_ASSERT_EQUAL(static_cast<const QAbstractItemModel*>(testee), topLeft.model());
  CPPUNIT_ASSERT(topLeft == bottomRight);
}

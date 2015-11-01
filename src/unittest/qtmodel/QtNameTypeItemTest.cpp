// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "QtNameTypeItemTest.hpp"

#include "NameTypeItemMock.hpp"
#include "../qthelper.hpp"

#include <qtmodel/QtNameTypeItem.hpp>
#include <qtmodel/IQtItem.hpp>

#include <QStringListModel>

void QtNameTypeItemTest::setUp()
{
  typeModel = new QStringListModel({"one", "two", "three"});
  item = new NameTypeItemMock<int>();
  item->typeModel = typeModel;
  testee = new QtNameTypeItem<int>(item);
}

void QtNameTypeItemTest::tearDown()
{
  delete testee;
  delete typeModel;
}


void QtNameTypeItemTest::inherits_IQtItem()
{
  CPPUNIT_ASSERT(dynamic_cast<IQtItem<int>*>(testee) != nullptr);
}

void QtNameTypeItemTest::forwards_list_change_events()
{
  int a;

  testee->added(&a);
  CPPUNIT_ASSERT_EQUAL(size_t(1), item->added_item.size());
  CPPUNIT_ASSERT_EQUAL(&a, item->added_item[0]);

  testee->removed(&a);
  CPPUNIT_ASSERT_EQUAL(size_t(1), item->removed_item.size());
  CPPUNIT_ASSERT_EQUAL(&a, item->removed_item[0]);
}

void QtNameTypeItemTest::has_two_columns()
{
  CPPUNIT_ASSERT_EQUAL(2, testee->columnCount());
}

void QtNameTypeItemTest::header_caption_is_name_and_type()
{
  CPPUNIT_ASSERT_EQUAL(std::string("name"), testee->headerData(0, Qt::Horizontal, Qt::DisplayRole).toString().toStdString());
  CPPUNIT_ASSERT_EQUAL(std::string("type"), testee->headerData(1, Qt::Horizontal, Qt::DisplayRole).toString().toStdString());
}

void QtNameTypeItemTest::return_sane_data_for_undefined_header_requests()
{
  CPPUNIT_ASSERT(QVariant{} == testee->headerData(0, Qt::Horizontal, Qt::EditRole));
  CPPUNIT_ASSERT(QVariant{} == testee->headerData(57, Qt::Horizontal, Qt::DisplayRole));
}


void QtNameTypeItemTest::may_be_editable()
{
  item->nameEditable = true;
  item->typeEditable = true;
  CPPUNIT_ASSERT_EQUAL(true, testee->editable(0));
  CPPUNIT_ASSERT_EQUAL(true, testee->editable(1));

  item->nameEditable = false;
  item->typeEditable = false;
  CPPUNIT_ASSERT_EQUAL(false, testee->editable(0));
  CPPUNIT_ASSERT_EQUAL(false, testee->editable(1));
}

void QtNameTypeItemTest::undefined_is_not_editable()
{
  CPPUNIT_ASSERT_EQUAL(false, testee->editable(-10));
  CPPUNIT_ASSERT_EQUAL(false, testee->editable(125));
}

void QtNameTypeItemTest::get_display_data()
{
  item->name = "the name";
  item->type = 1;

  CPPUNIT_ASSERT_EQUAL(item->name, testee->data(nullptr, 0, Qt::DisplayRole).toString().toStdString());
  CPPUNIT_ASSERT_EQUAL(std::string("two"), testee->data(nullptr, 1, Qt::DisplayRole).toString().toStdString());
}

void QtNameTypeItemTest::get_edit_data()
{
  item->name = "the name";
  item->type = 1;

  CPPUNIT_ASSERT_EQUAL(item->name, testee->data(nullptr, 0, Qt::EditRole).toString().toStdString());
  CPPUNIT_ASSERT_EQUAL(std::string("two"), testee->data(nullptr, 1, Qt::EditRole).toString().toStdString());
}

void QtNameTypeItemTest::return_sane_data_for_undefined_data_requests()
{
  CPPUNIT_ASSERT(QVariant{} == testee->data(nullptr, 55, Qt::EditRole));
  CPPUNIT_ASSERT(QVariant{} == testee->data(nullptr, 0, Qt::BackgroundRole));
}

void QtNameTypeItemTest::need_string_for_new_name()
{
  CPPUNIT_ASSERT_EQUAL(false, testee->setData(nullptr, 0, QVariant(42)));
  CPPUNIT_ASSERT_EQUAL(false, testee->setData(nullptr, 0, QVariant(false)));
  CPPUNIT_ASSERT_EQUAL(false, testee->setData(nullptr, 0, QVariant(34.12)));
  CPPUNIT_ASSERT_EQUAL(true, testee->setData(nullptr, 0, QVariant("hello")));
}

void QtNameTypeItemTest::change_name()
{
  item->name = "";

  CPPUNIT_ASSERT_EQUAL(true, testee->setData(nullptr, 0, "new name"));
  CPPUNIT_ASSERT_EQUAL(std::string("new name"), item->name);
}

void QtNameTypeItemTest::need_number_for_new_type()
{
  CPPUNIT_ASSERT_EQUAL(false, testee->setData(nullptr, 1, QVariant(false)));
  CPPUNIT_ASSERT_EQUAL(false, testee->setData(nullptr, 1, QVariant(34.12)));
  CPPUNIT_ASSERT_EQUAL(false, testee->setData(nullptr, 1, QVariant("hello")));
  CPPUNIT_ASSERT_EQUAL(false, testee->setData(nullptr, 1, QVariant(-42)));
  CPPUNIT_ASSERT_EQUAL(true, testee->setData(nullptr, 1, QVariant(42)));
}

void QtNameTypeItemTest::change_type()
{
  item->type = 123456789;

  CPPUNIT_ASSERT_EQUAL(true, testee->setData(nullptr, 1, 42));
  CPPUNIT_ASSERT_EQUAL(unsigned(42), item->type);
}

void QtNameTypeItemTest::notify_about_name_change()
{
  int *calledItem{nullptr};
  int calledColumn{-1};
  const auto listener = [&calledItem, &calledColumn](int *item, int column)
  {
    calledItem = item;
    calledColumn = column;
  };
  testee->addListener(listener);
  int content{};

  item->nameChanged(&content);

  CPPUNIT_ASSERT_EQUAL(&content, calledItem);
  CPPUNIT_ASSERT_EQUAL(0, calledColumn);
}

void QtNameTypeItemTest::notify_about_type_change()
{
  int *calledItem{nullptr};
  int calledColumn{-1};
  const auto listener = [&calledItem, &calledColumn](int *item, int column)
  {
    calledItem = item;
    calledColumn = column;
  };
  testee->addListener(listener);
  int content{};

  item->typeChanged(&content);

  CPPUNIT_ASSERT_EQUAL(&content, calledItem);
  CPPUNIT_ASSERT_EQUAL(1, calledColumn);
}

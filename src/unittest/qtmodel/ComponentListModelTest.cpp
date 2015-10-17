// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ComponentListModelTest.h"


void ComponentListModelTest::setUp()
{
  list = new List<Component>();
  testee = new ComponentListModel(*list);
}

void ComponentListModelTest::tearDown()
{
  delete testee;
  delete list;
  testee = nullptr;
  list = nullptr;
}

void ComponentListModelTest::inherits_QAbstractListModel()
{
  CPPUNIT_ASSERT(dynamic_cast<QAbstractListModel*>(testee) != nullptr);
}

void ComponentListModelTest::has_two_columns()
{
  CPPUNIT_ASSERT_EQUAL(2, testee->columnCount(QModelIndex()));
}

void ComponentListModelTest::header_caption_is_name_and_type()
{
  CPPUNIT_ASSERT_EQUAL(std::string("name"), testee->headerData(0, Qt::Horizontal, Qt::DisplayRole).toString().toStdString());
  CPPUNIT_ASSERT_EQUAL(std::string("type"), testee->headerData(1, Qt::Horizontal, Qt::DisplayRole).toString().toStdString());
}

void ComponentListModelTest::rowCount_matches_number_of_components()
{
  //TODO implement
//  CPPUNIT_ASSERT(false);
}

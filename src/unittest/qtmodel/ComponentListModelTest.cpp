// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ComponentListModelTest.h"


void ComponentListModelTest::setUp()
{
  library = new Library();
  testee = new ComponentListModel(library);
}

void ComponentListModelTest::tearDown()
{
  delete testee;
  testee = nullptr;
  library = nullptr;
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
  CPPUNIT_ASSERT(false);
}

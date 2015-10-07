// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ImplementationTypeModelTest.h"

#include <qtmodel/ImplementationTypeModel.hpp>
#include <core/implementation/ImplementationType.hpp>

void ImplementationTypeModelTest::inherits_QAbstractListModel()
{
  ImplementationTypeModel testee;
  CPPUNIT_ASSERT(dynamic_cast<QAbstractListModel*>(&testee) != nullptr);
}

void ImplementationTypeModelTest::has_all_types_as_row()
{
  ImplementationTypeModel testee;
  CPPUNIT_ASSERT_EQUAL(int(implementationTypeList().size()), testee.rowCount());
}

void ImplementationTypeModelTest::display_role_matches_name()
{
  ImplementationTypeModel testee;
  for (int i = 0; i < testee.rowCount(); i++) {
    const QVariant data = testee.data(testee.index(i), Qt::DisplayRole);
    const auto expected = toString(implementationTypeList()[i]);
    CPPUNIT_ASSERT(data.isValid());
    CPPUNIT_ASSERT_EQUAL(expected, data.toString().toStdString());
  }
}

void ImplementationTypeModelTest::edit_role_matches_list_index()
{
  ImplementationTypeModel testee;
  for (int i = 0; i < testee.rowCount(); i++) {
    const QVariant data = testee.data(testee.index(i), Qt::EditRole);
    CPPUNIT_ASSERT(data.isValid());
    CPPUNIT_ASSERT_EQUAL(i, data.toInt());
  }
}

void ImplementationTypeModelTest::typeIndex_returns_row_from_type()
{
  ImplementationTypeModel testee;
  for (int i = 0; i < testee.rowCount(); i++) {
    const QModelIndex index = testee.typeIndex(implementationTypeFromUint(i));
    CPPUNIT_ASSERT_EQUAL(i, index.row());
  }
}

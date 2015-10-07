// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "PortTypeModelTest.hpp"

#include <qtmodel/PortTypeModel.hpp>
#include <core/component/PortType.hpp>

void PortTypeModelTest::inherits_QAbstractListModel()
{
  PortTypeModel testee;
  CPPUNIT_ASSERT(dynamic_cast<QAbstractListModel*>(&testee) != nullptr);
}

void PortTypeModelTest::has_all_types_as_row()
{
  PortTypeModel testee;
  CPPUNIT_ASSERT_EQUAL(int(portTypeList().size()), testee.rowCount());
}

void PortTypeModelTest::display_role_matches_name()
{
  PortTypeModel testee;
  for (int i = 0; i < testee.rowCount(); i++) {
    const QVariant data = testee.data(testee.index(i), Qt::DisplayRole);
    const auto expected = toString(portTypeList()[i]);
    CPPUNIT_ASSERT(data.isValid());
    CPPUNIT_ASSERT_EQUAL(expected, data.toString().toStdString());
  }
}

void PortTypeModelTest::edit_role_matches_list_index()
{
  PortTypeModel testee;
  for (int i = 0; i < testee.rowCount(); i++) {
    const QVariant data = testee.data(testee.index(i), Qt::EditRole);
    CPPUNIT_ASSERT(data.isValid());
    CPPUNIT_ASSERT_EQUAL(i, data.toInt());
  }
}

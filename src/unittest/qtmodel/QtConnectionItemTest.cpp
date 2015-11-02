// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "QtConnectionItemTest.hpp"
#include "../core/implementation/CompositionInstanceMock.hpp"
#include "../core/connection/PortMock.hpp"
#include "../core/component/ComponentMock.hpp"

#include <qtmodel/QtConnectionItem.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/instance/InstanceFactory.hpp>

void QtConnectionItemTest::inherits_IQtItem()
{
  QtConnectionItem testee;

  CPPUNIT_ASSERT(dynamic_cast<IQtItem<Connection>*>(&testee) != nullptr);
}

void QtConnectionItemTest::has_four_columns()
{
  const QtConnectionItem testee{};

  CPPUNIT_ASSERT_EQUAL(4, testee.columnCount());
}

void QtConnectionItemTest::column_header_are_srcInst_srcPort_dstInst_dstPort()
{
  const QtConnectionItem testee{};

  CPPUNIT_ASSERT_EQUAL(std::string("src inst"), testee.headerData(0, Qt::Horizontal, Qt::DisplayRole).toString().toStdString());
  CPPUNIT_ASSERT_EQUAL(std::string("src port"), testee.headerData(1, Qt::Horizontal, Qt::DisplayRole).toString().toStdString());
  CPPUNIT_ASSERT_EQUAL(std::string("dst inst"), testee.headerData(2, Qt::Horizontal, Qt::DisplayRole).toString().toStdString());
  CPPUNIT_ASSERT_EQUAL(std::string("dst port"), testee.headerData(3, Qt::Horizontal, Qt::DisplayRole).toString().toStdString());
}

void QtConnectionItemTest::is_not_editable()
{
  const QtConnectionItem testee{};

  CPPUNIT_ASSERT_EQUAL(false, testee.editable(0));
  CPPUNIT_ASSERT_EQUAL(false, testee.editable(1));
  CPPUNIT_ASSERT_EQUAL(false, testee.editable(2));
  CPPUNIT_ASSERT_EQUAL(false, testee.editable(3));
}

void QtConnectionItemTest::return_sane_data_for_undefined_header_requests()
{
  const QtConnectionItem testee{};

  CPPUNIT_ASSERT(QVariant{} == testee.headerData(0, Qt::Horizontal, Qt::EditRole));
  CPPUNIT_ASSERT(QVariant{} == testee.headerData(57, Qt::Horizontal, Qt::DisplayRole));
}

void QtConnectionItemTest::data_returns_correct_port_names()
{
  PortMock a{"a"};
  PortMock b{"b"};
  const Connection connection{&a, &b};
  const QtConnectionItem testee{};

  CPPUNIT_ASSERT_EQUAL(std::string("a"), testee.data(&connection, 1, Qt::DisplayRole).toString().toStdString());
  CPPUNIT_ASSERT_EQUAL(std::string("b"), testee.data(&connection, 3, Qt::DisplayRole).toString().toStdString());
}

void QtConnectionItemTest::data_returns_self_for_CompositionInstance()
{
  ComponentMock component;
  CompositionInstance instance{&component};
  ComponentPort port{"", PortType::Slot};
  InstancePort a{&instance, &port};
  InstancePort b{&instance, &port};
  const Connection connection{&a, &b};
  const QtConnectionItem testee{};

  CPPUNIT_ASSERT_EQUAL(std::string("self"), testee.data(&connection, 0, Qt::DisplayRole).toString().toStdString());
  CPPUNIT_ASSERT_EQUAL(std::string("self"), testee.data(&connection, 2, Qt::DisplayRole).toString().toStdString());
}

void QtConnectionItemTest::data_returns_name_of_instance()
{
  Component *component = ComponentFactory::produce("", {"a"}, {"b"});
  Instance *instance = InstanceFactory::produce(component, "inst", Point(0,0));
  InstancePort *a = instance->getPort("a");
  InstancePort *b = instance->getPort("b");
  const Connection connection{a, b};
  const QtConnectionItem testee{};

  CPPUNIT_ASSERT_EQUAL(std::string("inst"), testee.data(&connection, 0, Qt::DisplayRole).toString().toStdString());
  CPPUNIT_ASSERT_EQUAL(std::string("inst"), testee.data(&connection, 2, Qt::DisplayRole).toString().toStdString());

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

void QtConnectionItemTest::return_sane_data_for_undefined_data_requests()
{
  Component *component = ComponentFactory::produce("", {"a"}, {"b"});
  Instance *instance = InstanceFactory::produce(component, "inst", Point(0,0));
  InstancePort *a = instance->getPort("a");
  InstancePort *b = instance->getPort("b");
  const Connection connection{a, b};
  const QtConnectionItem testee{};

  CPPUNIT_ASSERT(QVariant{} == testee.data(&connection, 0, Qt::EditRole));
  CPPUNIT_ASSERT(QVariant{} == testee.data(&connection, 56, Qt::DisplayRole));

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

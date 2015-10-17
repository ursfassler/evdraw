// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ConnectionListModelTest.h"
#include "../core/implementation/CompositionInstanceMock.hpp"
#include "../core/connection/PortMock.hpp"
#include "../core/component/ComponentMock.hpp"

#include <qtmodel/ConnectionListModel.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/instance/InstanceFactory.hpp>

#include <QSignalSpy>

void ConnectionListModelTest::setUp()
{
  list = new List<Connection>();
  testee = new ConnectionListModel(*list);
}

void ConnectionListModelTest::tearDown()
{
  delete testee;
  delete list;
}


void ConnectionListModelTest::inherits_QAbstractListModel()
{
  CPPUNIT_ASSERT(dynamic_cast<QAbstractListModel*>(testee) != nullptr);
}

void ConnectionListModelTest::has_four_columns()
{
  CPPUNIT_ASSERT_EQUAL(4, testee->columnCount(QModelIndex()));
}

void ConnectionListModelTest::column_header_are_srcInst_srcPort_dstInst_dstPort()
{
  CPPUNIT_ASSERT_EQUAL(std::string("src inst"), testee->headerData(0, Qt::Horizontal, Qt::DisplayRole).toString().toStdString());
  CPPUNIT_ASSERT_EQUAL(std::string("src port"), testee->headerData(1, Qt::Horizontal, Qt::DisplayRole).toString().toStdString());
  CPPUNIT_ASSERT_EQUAL(std::string("dst inst"), testee->headerData(2, Qt::Horizontal, Qt::DisplayRole).toString().toStdString());
  CPPUNIT_ASSERT_EQUAL(std::string("dst port"), testee->headerData(3, Qt::Horizontal, Qt::DisplayRole).toString().toStdString());
}

void ConnectionListModelTest::rowCount_matches_number_of_connections()
{
  PortMock a;
  PortMock b;
  list->add(new Connection{&a, &b});
  list->add(new Connection{&a, &b});
  list->add(new Connection{&a, &b});

  CPPUNIT_ASSERT_EQUAL(3, testee->rowCount());
}

void ConnectionListModelTest::data_returns_correct_port_names()
{
  PortMock a{"a"};
  PortMock b{"b"};
  list->add(new Connection{&a, &b});

  CPPUNIT_ASSERT_EQUAL(std::string("a"), testee->data(testee->index(0, 1)).toString().toStdString());
  CPPUNIT_ASSERT_EQUAL(std::string("b"), testee->data(testee->index(0, 3)).toString().toStdString());
}

void ConnectionListModelTest::data_returns_self_for_CompositionInstance()
{
  ComponentMock component;
  CompositionInstance instance{&component};
  ComponentPort port{"", PortType::Slot};
  InstancePort a{&instance, &port};
  InstancePort b{&instance, &port};
  list->add(new Connection{&a, &b});

  CPPUNIT_ASSERT_EQUAL(std::string("self"), testee->data(testee->index(0, 0)).toString().toStdString());
  CPPUNIT_ASSERT_EQUAL(std::string("self"), testee->data(testee->index(0, 2)).toString().toStdString());
}

void ConnectionListModelTest::data_returns_name_of_instance()
{
  Component *component = ComponentFactory::produce("", {"a"}, {"b"});
  Instance *instance = InstanceFactory::produce(component, "inst", Point(0,0));
  InstancePort *a = instance->getPort("a");
  InstancePort *b = instance->getPort("b");
  list->add(new Connection{a, b});

  CPPUNIT_ASSERT_EQUAL(std::string("inst"), testee->data(testee->index(0, 0)).toString().toStdString());
  CPPUNIT_ASSERT_EQUAL(std::string("inst"), testee->data(testee->index(0, 2)).toString().toStdString());

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

void ConnectionListModelTest::reacts_on_added_connections()
{
  Component *component = ComponentFactory::produce("", {"a"}, {"b"});
  Instance *instance = InstanceFactory::produce(component, "inst", Point(0,0));
  InstancePort *a = instance->getPort("a");
  InstancePort *b = instance->getPort("b");

  QSignalSpy spy{testee, SIGNAL(layoutChanged())};

  list->add(new Connection{a, b});

  CPPUNIT_ASSERT_EQUAL(1, spy.count());

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

void ConnectionListModelTest::reacts_on_removed_connections()
{
  Component *component = ComponentFactory::produce("", {"a"}, {"b"});
  Instance *instance = InstanceFactory::produce(component, "inst", Point(0,0));
  InstancePort *a = instance->getPort("a");
  InstancePort *b = instance->getPort("b");
  Connection *connection = new Connection{a, b};
  list->add(connection);

  QSignalSpy spy{testee, SIGNAL(layoutChanged())};

  list->remove(connection);

  CPPUNIT_ASSERT_EQUAL(1, spy.count());

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

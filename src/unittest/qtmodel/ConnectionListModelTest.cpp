// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ConnectionListModelTest.h"
#include "../core/implementation/CompositionInstanceMock.hpp"
#include "../core/connection/PortMock.hpp"
#include "../core/component/ComponentMock.hpp"

#include <qtmodel/ConnectionListModel.hpp>
#include <core/implementation/CompositionFactory.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/instance/InstanceFactory.hpp>

#include <QSignalSpy>

void ConnectionListModelTest::setUp()
{
  composition = new Composition(new CompositionInstanceMock());
  testee = new ConnectionListModel(*composition);
}

void ConnectionListModelTest::tearDown()
{
  delete testee;
  CompositionFactory::dispose(composition);
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
  Connection *con1 = new Connection(&a, &b);
  Connection *con2 = new Connection(&a, &b);
  Connection *con3 = new Connection(&a, &b);
  composition->addConnection(con1);
  composition->addConnection(con2);
  composition->addConnection(con3);

  CPPUNIT_ASSERT_EQUAL(3, testee->rowCount());

  composition->deleteConnection(con1);
  composition->deleteConnection(con2);
  composition->deleteConnection(con3);
}

void ConnectionListModelTest::data_returns_correct_port_names()
{
  PortMock a{"a"};
  PortMock b{"b"};
  Connection *con1 = new Connection(&a, &b);
  composition->addConnection(con1);

  CPPUNIT_ASSERT_EQUAL(std::string("a"), testee->data(testee->index(0, 1)).toString().toStdString());
  CPPUNIT_ASSERT_EQUAL(std::string("b"), testee->data(testee->index(0, 3)).toString().toStdString());

  composition->deleteConnection(con1);
}

void ConnectionListModelTest::data_returns_self_for_CompositionInstance()
{
  ComponentMock component;
  CompositionInstance instance{&component};
  ComponentPort port{"", PortType::Slot};
  InstancePort a{&instance, &port};
  InstancePort b{&instance, &port};
  Connection *con1 = new Connection(&a, &b);
  composition->addConnection(con1);

  CPPUNIT_ASSERT_EQUAL(std::string("self"), testee->data(testee->index(0, 0)).toString().toStdString());
  CPPUNIT_ASSERT_EQUAL(std::string("self"), testee->data(testee->index(0, 2)).toString().toStdString());

  composition->deleteConnection(con1);
}

void ConnectionListModelTest::data_returns_name_of_instance()
{
  Component *component = ComponentFactory::produce("", {"a"}, {"b"});
  Instance *instance = InstanceFactory::produce(component, "inst", Point(0,0));
  InstancePort *a = instance->getPort("a");
  InstancePort *b = instance->getPort("b");
  Connection *con1 = new Connection(a, b);
  composition->addConnection(con1);

  CPPUNIT_ASSERT_EQUAL(std::string("inst"), testee->data(testee->index(0, 0)).toString().toStdString());
  CPPUNIT_ASSERT_EQUAL(std::string("inst"), testee->data(testee->index(0, 2)).toString().toStdString());

  composition->deleteConnection(con1);
  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

void ConnectionListModelTest::reacts_on_added_connections()
{
  Component *component = ComponentFactory::produce("", {"a"}, {"b"});
  Instance *instance = InstanceFactory::produce(component, "inst", Point(0,0));
  InstancePort *a = instance->getPort("a");
  InstancePort *b = instance->getPort("b");
  Connection *con1 = new Connection(a, b);

  QSignalSpy spy{testee, SIGNAL(layoutChanged())};

  composition->addConnection(con1);

  CPPUNIT_ASSERT_EQUAL(1, spy.count());

  composition->deleteConnection(con1);
  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

void ConnectionListModelTest::reacts_on_removed_connections()
{
  Component *component = ComponentFactory::produce("", {"a"}, {"b"});
  Instance *instance = InstanceFactory::produce(component, "inst", Point(0,0));
  InstancePort *a = instance->getPort("a");
  InstancePort *b = instance->getPort("b");
  Connection *con1 = new Connection(a, b);
  composition->addConnection(con1);

  QSignalSpy spy{testee, SIGNAL(layoutChanged())};

  composition->deleteConnection(con1);

  CPPUNIT_ASSERT_EQUAL(1, spy.count());

  InstanceFactory::dispose(instance);
  ComponentFactory::dispose(component);
}

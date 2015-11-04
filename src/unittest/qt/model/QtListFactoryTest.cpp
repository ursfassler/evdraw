// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "QtListFactoryTest.hpp"

#include <qt/model/QtListFactory.hpp>
#include <qt/model/QtList.hpp>
#include <core/component/IComponent.hpp>
#include <core/instance/IComponentInstance.hpp>

void QtListFactoryTest::create_component_list()
{
  List<IComponent> model;

  QtList<IComponent> *list = QtListFactory::createComponentList(model);

  CPPUNIT_ASSERT(list != nullptr);

  delete list;
}

void QtListFactoryTest::create_instance_list()
{
  List<IComponent> typeModel;
  QtList<IComponent> *types = QtListFactory::createComponentList(typeModel);
  List<IComponentInstance> model;

  QtList<IComponentInstance> *list = QtListFactory::createInstanceList(model, types);

  CPPUNIT_ASSERT(list != nullptr);

  delete list;
  delete types;
}

void QtListFactoryTest::create_port_list()
{
  List<ComponentPort> model;

  QtList<ComponentPort> *list = QtListFactory::createPortList(model);

  CPPUNIT_ASSERT(list != nullptr);

  delete list;
}

void QtListFactoryTest::create_connection_list()
{
  List<Connection> model;

  QtList<Connection> *list = QtListFactory::createConnectionList(model);

  CPPUNIT_ASSERT(list != nullptr);

  delete list;
}

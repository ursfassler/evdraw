#include "CompositionInstanceTest.hpp"
#include "../component/ComponentMock.hpp"
#include "../instance/InstanceObserverMock.h"

#include <core/implementation/CompositionInstance.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/implementation/NullImplementation.hpp>
#include <core/implementation/Composition.hpp>
#include <core/connection/ConnectionFactory.hpp>

void CompositionInstanceTest::create()
{
  ComponentMock component;
  CompositionInstance testee(&component);

  CPPUNIT_ASSERT_EQUAL(static_cast<IComponent*>(&component), testee.getComponent());
  CPPUNIT_ASSERT_EQUAL(PaperUnit(0), testee.getWidth());
  CPPUNIT_ASSERT_EQUAL(PaperUnit(0), testee.getHeight());
  CPPUNIT_ASSERT_EQUAL(size_t(0), testee.getPorts().size());
}

void CompositionInstanceTest::can_change_width()
{
  ComponentMock component;
  CompositionInstance testee(&component);

  testee.setWidth(1234);

  CPPUNIT_ASSERT_EQUAL(PaperUnit(0), testee.getHeight());
  CPPUNIT_ASSERT_EQUAL(PaperUnit(1234), testee.getWidth());
}

void CompositionInstanceTest::can_change_height()
{
  ComponentMock component;
  CompositionInstance testee(&component);

  testee.setHeight(1234);

  CPPUNIT_ASSERT_EQUAL(PaperUnit(0), testee.getWidth());
  CPPUNIT_ASSERT_EQUAL(PaperUnit(1234), testee.getHeight());
}

void CompositionInstanceTest::setHeight_notifies_observers()
{
  Component *component = ComponentFactory::produce("", {}, {});
  CompositionInstance *testee = new CompositionInstance(component);

  InstanceObserverMock observer;
  testee->registerObserver(&observer);

  testee->setHeight(100);

  CPPUNIT_ASSERT_EQUAL(uint(1), observer.changedHeight);

  testee->unregisterObserver(&observer);
  delete testee;
  ComponentFactory::dispose(component);
}

void CompositionInstanceTest::setHeight_does_not_notifies_observers_when_new_value_is_the_same()
{
  Component *component = ComponentFactory::produce("", {}, {});
  CompositionInstance *testee = new CompositionInstance(component);

  testee->setHeight(100);
  InstanceObserverMock observer;
  testee->registerObserver(&observer);

  testee->setHeight(100);

  CPPUNIT_ASSERT_EQUAL(uint(0), observer.changedHeight);

  testee->unregisterObserver(&observer);
  delete testee;
  ComponentFactory::dispose(component);
}

void CompositionInstanceTest::change_of_width_notifies_observers()
{
  Component *component = ComponentFactory::produce("", {}, {});
  CompositionInstance *testee = new CompositionInstance(component);

  InstanceObserverMock observer;
  testee->registerObserver(&observer);

  testee->setWidth(100);

  CPPUNIT_ASSERT_EQUAL(uint(1), observer.changedWidth);

  testee->unregisterObserver(&observer);
  delete testee;
  ComponentFactory::dispose(component);
}

void CompositionInstanceTest::setWidth_does_not_notifies_observers_when_new_value_is_the_same()
{
  Component *component = ComponentFactory::produce("", {}, {});
  CompositionInstance *testee = new CompositionInstance(component);

  testee->setWidth(100);
  InstanceObserverMock observer;
  testee->registerObserver(&observer);

  testee->setWidth(100);

  CPPUNIT_ASSERT_EQUAL(uint(0), observer.changedWidth);

  testee->unregisterObserver(&observer);
  delete testee;
  ComponentFactory::dispose(component);
}

void CompositionInstanceTest::change_of_width_updates_port_positions()
{
  Component *component = ComponentFactory::produce("", {}, {"out"});
  CompositionInstance *testee = new CompositionInstance(component);
  InstancePort *port = testee->getPorts()[0];

  const auto oldPos = port->getAbsolutePosition().x;
  testee->setWidth(100);
  const auto newPos = port->getAbsolutePosition().x;

  CPPUNIT_ASSERT(newPos > oldPos);

  delete testee;
  ComponentFactory::dispose(component);
}

void CompositionInstanceTest::create_from_component_with_ports()
{
  Component *component = ComponentFactory::produce("", {"in1", "in2"}, {"out"});
  CompositionInstance *testee = new CompositionInstance(component);

  CPPUNIT_ASSERT_EQUAL(size_t(3), testee->getPorts().size());
  CPPUNIT_ASSERT_EQUAL(std::string("in1"), testee->getPorts()[0]->getName());
  CPPUNIT_ASSERT_EQUAL(std::string("in2"), testee->getPorts()[1]->getName());
  CPPUNIT_ASSERT_EQUAL(std::string("out"), testee->getPorts()[2]->getName());

  CPPUNIT_ASSERT_EQUAL(static_cast<IInstance*>(testee), testee->getPorts()[0]->getInstance());
  CPPUNIT_ASSERT_EQUAL(static_cast<IInstance*>(testee), testee->getPorts()[1]->getInstance());
  CPPUNIT_ASSERT_EQUAL(static_cast<IInstance*>(testee), testee->getPorts()[2]->getInstance());

  delete testee;
  ComponentFactory::dispose(component);
}

void CompositionInstanceTest::syncs_with_new_ports_in_composition()
{
  Component *component = ComponentFactory::produce("", {}, {});
  CompositionInstance *testee = new CompositionInstance(component);

  ComponentPort *port = new ComponentPort("", PortType::Signal);
  component->addPort(port);

  CPPUNIT_ASSERT_EQUAL(size_t(1), testee->getPorts().size());
  CPPUNIT_ASSERT_EQUAL(port, testee->getPorts()[0]->getCompPort());

  delete testee;
  ComponentFactory::dispose(component);
}

void CompositionInstanceTest::syncs_with_deleted_ports_in_composition()
{
  Component *component = ComponentFactory::produce("", {""}, {});
  CompositionInstance *testee = new CompositionInstance(component);

  ComponentPort *port = component->getPorts()[0];
  component->deletePort(port);

  CPPUNIT_ASSERT_EQUAL(size_t(0), testee->getPorts().size());

  delete testee;
  ComponentFactory::dispose(component);
}

void CompositionInstanceTest::port_side_of_slot_is_left()
{
  Component component{"", new NullImplementation()};
  CompositionInstance testee(&component);

  CPPUNIT_ASSERT_EQUAL(Side::Left, testee.portSide(PortType::Slot));

  ComponentFactory::cleanup(component);
}

void CompositionInstanceTest::port_side_of_signal_is_right()
{
  Component component{"", new NullImplementation()};
  CompositionInstance testee(&component);

  CPPUNIT_ASSERT_EQUAL(Side::Right, testee.portSide(PortType::Signal));

  ComponentFactory::cleanup(component);
}

void CompositionInstanceTest::connector_side_of_slot_is_right()
{
  ComponentMock component;
  CompositionInstance testee(&component);

  CPPUNIT_ASSERT_EQUAL(Side::Right, testee.connectorSide(PortType::Slot));
}

void CompositionInstanceTest::connector_side_of_signal_is_left()
{
  ComponentMock component;
  CompositionInstance testee(&component);

  CPPUNIT_ASSERT_EQUAL(Side::Left, testee.connectorSide(PortType::Signal));
}

void CompositionInstanceTest::cleanup_with_connected_ports()
{
  Component *component = ComponentFactory::produce("", {"in"}, {"out"});
  CompositionInstance *instance = new CompositionInstance(component);
  Composition *composition = new Composition(instance);
  component->setImplementation(composition);

  Connection *connection = ConnectionFactory::produce(instance->getPorts().front(), instance->getPorts().back());
  composition->addConnection(connection);

  ComponentFactory::dispose(component);
}

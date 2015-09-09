// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ComponentTest.hpp"

#include <core/component/Component.hpp>
#include <core/component/ComponentPort.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/implementation/NullImplementation.hpp>

void ComponentTest::produce()
{
  Component comp("Lala", new NullImplementation());
  CPPUNIT_ASSERT_EQUAL(std::string("Lala"), comp.getName());
}

void ComponentTest::setName()
{
  Component comp("", new NullImplementation());
  comp.setName("new name");
  CPPUNIT_ASSERT_EQUAL(std::string("new name"), comp.getName());
}

void ComponentTest::addSlot()
{
  Component     comp("", new NullImplementation());
  ComponentPort *port = new ComponentPort("left", PortType::Slot);

  CPPUNIT_ASSERT_EQUAL(size_t(0), comp.getPorts().size());
  comp.addPort(port);
  CPPUNIT_ASSERT_EQUAL(size_t(1), comp.getPorts().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), port->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(port, comp.getPorts()[0]);

  ComponentFactory::cleanup(comp);
}

void ComponentTest::addSignal()
{
  Component     comp("", new NullImplementation());
  ComponentPort *port = new ComponentPort("right", PortType::Signal);

  CPPUNIT_ASSERT_EQUAL(size_t(0), comp.getPorts().size());
  comp.addPort(port);
  CPPUNIT_ASSERT_EQUAL(size_t(1), comp.getPorts().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), port->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(port, comp.getPorts()[0]);

  ComponentFactory::cleanup(comp);
}

void ComponentTest::delPort()
{
  Component     comp("", new NullImplementation());
  ComponentPort *port = new ComponentPort("", PortType::Signal);

  comp.addPort(port);
  CPPUNIT_ASSERT_EQUAL(size_t(1), comp.getPorts().size());

  comp.deletePort(port);
  CPPUNIT_ASSERT_EQUAL(size_t(0), comp.getPorts().size());

  ComponentFactory::cleanup(comp);
}

void ComponentTest::signalSlotCanBeInterleaved()
{
  Component     comp("", new NullImplementation());
  ComponentPort *port1 = new ComponentPort("", PortType::Slot);
  ComponentPort *port2 = new ComponentPort("", PortType::Signal);
  ComponentPort *port3 = new ComponentPort("", PortType::Slot);

  comp.addPort(port1);
  comp.addPort(port2);
  comp.addPort(port3);

  CPPUNIT_ASSERT_EQUAL(size_t(3), comp.getPorts().size());
  CPPUNIT_ASSERT_EQUAL(port1, comp.getPorts()[0]);
  CPPUNIT_ASSERT_EQUAL(port2, comp.getPorts()[1]);
  CPPUNIT_ASSERT_EQUAL(port3, comp.getPorts()[2]);
  CPPUNIT_ASSERT_EQUAL(size_t(0), port1->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(0), port2->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(1), port3->getTopIndex());

  ComponentFactory::cleanup(comp);
}

void ComponentTest::rightPortIndexUpdatedOnAdd()
{
  Component     comp("", new NullImplementation());
  ComponentPort *port1 = new ComponentPort("1", PortType::Signal);
  ComponentPort *port2 = new ComponentPort("2", PortType::Signal);
  ComponentPort *port3 = new ComponentPort("3", PortType::Signal);
  ComponentPort *port4 = new ComponentPort("4", PortType::Signal);

  comp.addPort(port1);
  comp.addPort(port2);
  comp.addPort(port3);
  comp.addPort(port4);

  CPPUNIT_ASSERT_EQUAL(size_t(0), port1->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(1), port2->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(2), port3->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(3), port4->getTopIndex());

  ComponentFactory::cleanup(comp);
}

void ComponentTest::leftPortIndexUpdatedOnAdd()
{
  Component     comp("", new NullImplementation());
  ComponentPort *port1 = new ComponentPort("1", PortType::Slot);
  ComponentPort *port2 = new ComponentPort("2", PortType::Slot);
  ComponentPort *port3 = new ComponentPort("3", PortType::Slot);
  ComponentPort *port4 = new ComponentPort("4", PortType::Slot);

  comp.addPort(port1);
  comp.addPort(port2);
  comp.addPort(port3);
  comp.addPort(port4);

  CPPUNIT_ASSERT_EQUAL(size_t(0), port1->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(1), port2->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(2), port3->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(3), port4->getTopIndex());

  ComponentFactory::cleanup(comp);
}

void ComponentTest::portIndexUpdatedOnDel()
{
  Component     comp("", new NullImplementation());
  ComponentPort *port1 = new ComponentPort("1", PortType::Slot);
  ComponentPort *port2 = new ComponentPort("2", PortType::Slot);
  ComponentPort *port3 = new ComponentPort("3", PortType::Slot);
  ComponentPort *port4 = new ComponentPort("4", PortType::Slot);

  comp.addPort(port1);
  comp.addPort(port2);
  comp.addPort(port3);
  comp.addPort(port4);
  CPPUNIT_ASSERT_EQUAL(size_t(0), port1->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(1), port2->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(2), port3->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(3), port4->getTopIndex());

  comp.deletePort(port1);
  CPPUNIT_ASSERT_EQUAL(size_t(0), port2->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(1), port3->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(2), port4->getTopIndex());

  ComponentFactory::cleanup(comp);
}

void ComponentTest::port_index_update_on_type_change()
{
  Component     comp("", new NullImplementation());
  ComponentPort *port1 = new ComponentPort("1", PortType::Slot);
  ComponentPort *port2 = new ComponentPort("2", PortType::Slot);
  ComponentPort *port3 = new ComponentPort("3", PortType::Slot);
  ComponentPort *port4 = new ComponentPort("4", PortType::Slot);

  comp.addPort(port1);
  comp.addPort(port2);
  comp.addPort(port3);
  comp.addPort(port4);
  CPPUNIT_ASSERT_EQUAL(size_t(0), port1->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(1), port2->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(2), port3->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(3), port4->getTopIndex());

  port1->setType(PortType::Signal);
  CPPUNIT_ASSERT_EQUAL(size_t(0), port1->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(0), port2->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(1), port3->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(2), port4->getTopIndex());

  ComponentFactory::cleanup(comp);
}

void ComponentTest::port_index_update_on_type_change_with_signals_and_slots()
{
  Component     comp("", new NullImplementation());
  ComponentPort *port1 = new ComponentPort("1", PortType::Slot);
  ComponentPort *port2 = new ComponentPort("2", PortType::Slot);
  ComponentPort *port3 = new ComponentPort("3", PortType::Signal);
  ComponentPort *port4 = new ComponentPort("4", PortType::Signal);

  comp.addPort(port1);
  comp.addPort(port2);
  comp.addPort(port3);
  comp.addPort(port4);

  port1->setType(PortType::Signal);
  CPPUNIT_ASSERT_EQUAL(size_t(0), port1->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(0), port2->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(1), port3->getTopIndex());
  CPPUNIT_ASSERT_EQUAL(size_t(2), port4->getTopIndex());

  ComponentFactory::cleanup(comp);
}

void ComponentTest::getPort()
{
  Component *comp = ComponentFactory::produce("", {"in"}, {});
  ComponentPort *port = comp->getPort("in");
  CPPUNIT_ASSERT(port != nullptr);
  ComponentFactory::dispose(comp);
}

void ComponentTest::getPortForNonExistingThrowsError()
{
  Component *comp = ComponentFactory::produce("", {"in"}, {});
  CPPUNIT_ASSERT_THROW(comp->getPort("lala"), std::invalid_argument);
  ComponentFactory::dispose(comp);
}

void ComponentTest::constructWithOwnImplementation()
{
  NullImplementation *impl = new NullImplementation();
  Component     component("", impl);
  CPPUNIT_ASSERT_EQUAL(static_cast<AbstractImplementation*>(impl), component.getImplementation());
}

class DeleteTest : public AbstractImplementation
{
  public:
    DeleteTest(bool &aDeleted) :
      deleted(aDeleted)
    {
    }

    ~DeleteTest()
    {
      deleted = true;
    }

    void accept(Visitor &) {}
    void accept(ConstVisitor &) const {}

    bool &deleted;
};

void ComponentTest::componentDeletesImplementationWhenDeleted()
{
  bool deleted = false;
  DeleteTest *test = new DeleteTest(deleted);
  Component *comp = new Component("", test);
  delete comp;
  CPPUNIT_ASSERT(deleted);
}

void ComponentTest::setImplementation()
{
  Component comp("", new NullImplementation());
  NullImplementation *impl = new NullImplementation();

  CPPUNIT_ASSERT(static_cast<AbstractImplementation*>(impl) != comp.getImplementation());
  comp.setImplementation(impl);
  CPPUNIT_ASSERT_EQUAL(static_cast<AbstractImplementation*>(impl), comp.getImplementation());
}

void ComponentTest::setImplementationDeletesOldOne()
{
  bool deleted = false;
  DeleteTest *test = new DeleteTest(deleted);
  Component comp("", test);

  comp.setImplementation(new NullImplementation());
  CPPUNIT_ASSERT(deleted);
}

void ComponentTest::heightOfEmptyComponent()
{
  Component     comp("", new NullImplementation());
  CPPUNIT_ASSERT_EQUAL(size_t(0), comp.height());
}

void ComponentTest::heightOf2Slots()
{
  Component     *comp = ComponentFactory::produce("", {"", ""}, {});
  CPPUNIT_ASSERT_EQUAL(size_t(2), comp->height());
  ComponentFactory::dispose(comp);
}

void ComponentTest::heightOf2Signals()
{
  Component     *comp = ComponentFactory::produce("", {}, {"", ""});
  CPPUNIT_ASSERT_EQUAL(size_t(2), comp->height());
  ComponentFactory::dispose(comp);
}

void ComponentTest::heightOf2SlotsAnd3Signals()
{
  Component     *comp = ComponentFactory::produce("", {"", ""}, {"", "", ""});
  CPPUNIT_ASSERT_EQUAL(size_t(3), comp->height());
  ComponentFactory::dispose(comp);
}

void ComponentTest::heightOf2SignalsAnd3Slots()
{
  Component     *comp = ComponentFactory::produce("", {"", "", ""}, {"", ""});
  CPPUNIT_ASSERT_EQUAL(size_t(3), comp->height());
  ComponentFactory::dispose(comp);
}

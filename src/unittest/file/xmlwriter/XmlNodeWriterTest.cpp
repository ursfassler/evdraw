// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "XmlNodeWriterTest.hpp"
#include "../../core/implementation/CompositionMock.hpp"
#include "../../core/implementation/CompositionInstanceMock.hpp"
#include "../../core/component/ComponentMock.hpp"

#include <core/component/Library.hpp>
#include <core/component/Component.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/implementation/Composition.hpp>
#include <core/implementation/NullImplementation.hpp>
#include <core/instance/Instance.hpp>
#include <core/instance/InstanceFactory.hpp>
#include <core/connection/Connection.hpp>
#include <core/connection/ConnectionFactory.hpp>
#include <core/util/contract.hpp>

#include <map>

void XmlNodeWriterTest::setUp()
{
  precondition(parent == nullptr);
  precondition(writer == nullptr);
  parent = new TiXmlElement("");
  writer = new XmlNodeWriter(parent);
}

void XmlNodeWriterTest::tearDown()
{
  precondition(writer != nullptr);
  precondition(parent != nullptr);
  delete writer;
  delete parent;
  writer = nullptr;
  parent = nullptr;
}

void XmlNodeWriterTest::writeEmptyLibrary()
{
  Library lib;
  lib.accept(*writer);

  CPPUNIT_ASSERT_EQUAL(std::string("evdraw"), name());
  CPPUNIT_ASSERT_EQUAL(0, childrenCount());
  CPPUNIT_ASSERT_EQUAL(0, attributeCount());
}

void XmlNodeWriterTest::writeEmptyComponent()
{
  Component *comp = ComponentFactory::produce("Compo");
  comp->accept(*writer);

  CPPUNIT_ASSERT_EQUAL(std::string("component"), name());
  CPPUNIT_ASSERT_EQUAL(0, childrenCount());
  CPPUNIT_ASSERT_EQUAL(1, attributeCount());
  CPPUNIT_ASSERT_EQUAL(std::string("Compo"), attr("name"));

  ComponentFactory::dispose(comp);
}

void XmlNodeWriterTest::writeComponentWithSlots()
{
  Component *comp = ComponentFactory::produce("Component", {"in1", "in2"}, {});

  comp->accept(*writer);

  CPPUNIT_ASSERT_EQUAL(2, childrenCount());
  CPPUNIT_ASSERT_EQUAL(std::string("in1"), childAttr(0, "name"));
  CPPUNIT_ASSERT_EQUAL(std::string("in2"), childAttr(1, "name"));

  ComponentFactory::dispose(comp);
}

void XmlNodeWriterTest::writeComponentWithSignals()
{
  Component *comp = ComponentFactory::produce("Component", {}, {"out1", "out2"});

  comp->accept(*writer);

  CPPUNIT_ASSERT_EQUAL(2, childrenCount());
  CPPUNIT_ASSERT_EQUAL(std::string("out1"), childAttr(0, "name"));
  CPPUNIT_ASSERT_EQUAL(std::string("out2"), childAttr(1, "name"));

  ComponentFactory::dispose(comp);
}

void XmlNodeWriterTest::writeComponentWithSlotsAndSignals()
{
  Component *comp = ComponentFactory::produce("Component", {"in1", "in2"}, {"out1", "out2"});

  comp->accept(*writer);

  CPPUNIT_ASSERT_EQUAL(4, childrenCount());
  CPPUNIT_ASSERT_EQUAL(std::string("in1"), childAttr(0, "name"));
  CPPUNIT_ASSERT_EQUAL(std::string("in2"), childAttr(1, "name"));
  CPPUNIT_ASSERT_EQUAL(std::string("out1"), childAttr(2, "name"));
  CPPUNIT_ASSERT_EQUAL(std::string("out2"), childAttr(3, "name"));

  ComponentFactory::dispose(comp);
}

void XmlNodeWriterTest::writeComponentWithSlotsAndSignalsKeepsOrder()
{
  Component *comp = ComponentFactory::produce("Component");
  comp->addPort(new ComponentPort("in1", PortType::Slot));
  comp->addPort(new ComponentPort("out1", PortType::Signal));
  comp->addPort(new ComponentPort("out2", PortType::Signal));
  comp->addPort(new ComponentPort("in2", PortType::Slot));

  comp->accept(*writer);

  CPPUNIT_ASSERT_EQUAL(4, childrenCount());
  CPPUNIT_ASSERT_EQUAL(std::string("in1"),  childAttr(0, "name"));
  CPPUNIT_ASSERT_EQUAL(std::string("out1"), childAttr(1, "name"));
  CPPUNIT_ASSERT_EQUAL(std::string("out2"), childAttr(2, "name"));
  CPPUNIT_ASSERT_EQUAL(std::string("in2"),  childAttr(3, "name"));

  ComponentFactory::dispose(comp);
}

void XmlNodeWriterTest::writeComponentWithComposition()
{
  Composition *composition = new Composition(new CompositionInstanceMock());
  Component component("Compo", composition);

  component.accept(*writer);

  CPPUNIT_ASSERT_EQUAL(1, childrenCount());
  CPPUNIT_ASSERT_EQUAL(std::string("composition"), childName(0));
}

void XmlNodeWriterTest::writeLibraryWithComponents()
{
  Library lib;
  lib.addComponent(ComponentFactory::produce("comp1"));
  lib.addComponent(ComponentFactory::produce("comp2"));
  lib.accept(*writer);

  CPPUNIT_ASSERT_EQUAL(std::string("evdraw"), name());
  CPPUNIT_ASSERT_EQUAL(2, childrenCount());
  CPPUNIT_ASSERT_EQUAL(std::string("comp1"), childAttr(0, "name"));
  CPPUNIT_ASSERT_EQUAL(std::string("comp2"), childAttr(1, "name"));
  CPPUNIT_ASSERT_EQUAL(0, attributeCount());
}

void XmlNodeWriterTest::writeInstance()
{
  Component component("Component", new NullImplementation());
  Instance instance("theInstance", Point(-2,67), &component);
  instance.accept(*writer);

  CPPUNIT_ASSERT_EQUAL(std::string("instance"), name());
  CPPUNIT_ASSERT_EQUAL(0, childrenCount());
  CPPUNIT_ASSERT_EQUAL(4, attributeCount());
  CPPUNIT_ASSERT_EQUAL(std::string("theInstance"), attr("name"));
  CPPUNIT_ASSERT_EQUAL(std::string("Component"), attr("component"));
  CPPUNIT_ASSERT_EQUAL(-2, std::stoi(attr("x")));
  CPPUNIT_ASSERT_EQUAL(67, std::stoi(attr("y")));
}

void XmlNodeWriterTest::writeEmptyComposition()
{
  ComponentMock component;
  CompositionInstance *selfInst = new CompositionInstance(&component);
  Composition composition{selfInst};
  selfInst->setWidth(123);
  selfInst->setHeight(456);
  composition.accept(*writer);

  CPPUNIT_ASSERT_EQUAL(std::string("composition"), name());
  CPPUNIT_ASSERT_EQUAL(0, childrenCount());
  CPPUNIT_ASSERT_EQUAL(2, attributeCount());
  CPPUNIT_ASSERT_EQUAL(std::string("123"), attr("width"));
  CPPUNIT_ASSERT_EQUAL(std::string("456"), attr("height"));
}

void XmlNodeWriterTest::writeCompositionWithInstances()
{
  Component component("Component", new NullImplementation());
  Composition composition{new CompositionInstanceMock()};
  composition.addInstance(new Instance("theInstance1", Point(0,0), &component));
  composition.addInstance(new Instance("theInstance2", Point(0,0), &component));
  composition.addInstance(new Instance("theInstance3", Point(0,0), &component));

  composition.accept(*writer);

  CPPUNIT_ASSERT_EQUAL(std::string("composition"), name());
  CPPUNIT_ASSERT_EQUAL(2, attributeCount());
  CPPUNIT_ASSERT_EQUAL(std::string("0"), attr("width"));
  CPPUNIT_ASSERT_EQUAL(std::string("0"), attr("height"));
  CPPUNIT_ASSERT_EQUAL(3, childrenCount());
  CPPUNIT_ASSERT_EQUAL(std::string("theInstance1"), childAttr(0, "name"));
  CPPUNIT_ASSERT_EQUAL(std::string("theInstance2"), childAttr(1, "name"));
  CPPUNIT_ASSERT_EQUAL(std::string("theInstance3"), childAttr(2, "name"));
}

void XmlNodeWriterTest::writeCompositionWithConnections()
{
  Component *comp = ComponentFactory::produce("Component", {"in"}, {"out"});
  Instance *inst1 = InstanceFactory::produce(comp, "inst1", Point(0,0));
  Instance *inst2 = InstanceFactory::produce(comp, "inst2", Point(0,0));
  Connection *con = ConnectionFactory::produce(inst1->getPorts().back(), inst2->getPorts().front());
  Composition *composition = new Composition(new CompositionInstanceMock());
  composition->addConnection(con);

  composition->accept(*writer);

  CPPUNIT_ASSERT_EQUAL(std::string("composition"), name());
  CPPUNIT_ASSERT_EQUAL(1, childrenCount());
  CPPUNIT_ASSERT_EQUAL(std::string("connection"), childName(0));
  CPPUNIT_ASSERT_EQUAL(2, attributeCount());
  CPPUNIT_ASSERT_EQUAL(std::string("0"), attr("width"));
  CPPUNIT_ASSERT_EQUAL(std::string("0"), attr("height"));

  delete composition;
  InstanceFactory::dispose(inst2);
  InstanceFactory::dispose(inst1);
  ComponentFactory::dispose(comp);
}

void XmlNodeWriterTest::writeInstanceInPort()
{
  Component *comp = ComponentFactory::produce("Component", {"in"}, {});
  Instance *inst = InstanceFactory::produce(comp, "inst", Point(0,0));
  AbstractPort *port = inst->getPorts().front();

  port->accept(*writer);

  CPPUNIT_ASSERT_EQUAL(std::string("instanceport"), name());
  CPPUNIT_ASSERT_EQUAL(0, childrenCount());
  CPPUNIT_ASSERT_EQUAL(2, attributeCount());
  CPPUNIT_ASSERT_EQUAL(std::string("inst"), attr("instance"));
  CPPUNIT_ASSERT_EQUAL(std::string("in"), attr("port"));

  InstanceFactory::dispose(inst);
  ComponentFactory::dispose(comp);
}

void XmlNodeWriterTest::writeInstanceOutPort()
{
  Component *comp = ComponentFactory::produce("Component", {}, {"out"});
  Instance *inst = InstanceFactory::produce(comp, "inst", Point(0,0));
  AbstractPort *port = inst->getPorts().front();

  port->accept(*writer);

  CPPUNIT_ASSERT_EQUAL(std::string("instanceport"), name());
  CPPUNIT_ASSERT_EQUAL(0, childrenCount());
  CPPUNIT_ASSERT_EQUAL(2, attributeCount());
  CPPUNIT_ASSERT_EQUAL(std::string("inst"), attr("instance"));
  CPPUNIT_ASSERT_EQUAL(std::string("out"), attr("port"));

  InstanceFactory::dispose(inst);
  ComponentFactory::dispose(comp);
}

void XmlNodeWriterTest::writeComponentInPort()
{
  Component *comp = ComponentFactory::produce("Component", {"in"}, {});
  ComponentPort *port = comp->getPorts().front();

  port->accept(*writer);

  CPPUNIT_ASSERT_EQUAL(std::string("slot"), name());
  CPPUNIT_ASSERT_EQUAL(0, childrenCount());
  CPPUNIT_ASSERT_EQUAL(1, attributeCount());
  CPPUNIT_ASSERT_EQUAL(std::string("in"), attr("name"));

  ComponentFactory::dispose(comp);
}

void XmlNodeWriterTest::writeComponentOutPort()
{
  Component *comp = ComponentFactory::produce("Component", {}, {"out"});
  ComponentPort *port = comp->getPorts().front();

  port->accept(*writer);

  CPPUNIT_ASSERT_EQUAL(std::string("signal"), name());
  CPPUNIT_ASSERT_EQUAL(0, childrenCount());
  CPPUNIT_ASSERT_EQUAL(1, attributeCount());
  CPPUNIT_ASSERT_EQUAL(std::string("out"), attr("name"));

  ComponentFactory::dispose(comp);
}

void XmlNodeWriterTest::writeConnectionPorts()
{
  Component *comp = ComponentFactory::produce("Component", {"in"}, {"out"});
  Instance *inst1 = InstanceFactory::produce(comp, "inst1", Point(0,0));
  Instance *inst2 = InstanceFactory::produce(comp, "inst2", Point(0,0));
  Connection *con = ConnectionFactory::produce(inst1->getPorts().back(), inst2->getPorts().front());

  con->accept(*writer);

  CPPUNIT_ASSERT_EQUAL(std::string("connection"), name());
  CPPUNIT_ASSERT_EQUAL(2, childrenCount());
  CPPUNIT_ASSERT_EQUAL(std::string("instanceport"), childName(0));
  CPPUNIT_ASSERT_EQUAL(std::string("inst1"), childAttr(0, "instance"));
  CPPUNIT_ASSERT_EQUAL(std::string("out"), childAttr(0, "port"));
  CPPUNIT_ASSERT_EQUAL(std::string("instanceport"), childName(1));
  CPPUNIT_ASSERT_EQUAL(std::string("inst2"), childAttr(1, "instance"));
  CPPUNIT_ASSERT_EQUAL(std::string("in"), childAttr(1, "port"));

  ConnectionFactory::dispose(con);
  InstanceFactory::dispose(inst2);
  InstanceFactory::dispose(inst1);
  ComponentFactory::dispose(comp);
}

void XmlNodeWriterTest::writeConnectionPath()
{
  Component *comp = ComponentFactory::produce("Component", {"in"}, {"out"});
  Instance *inst1 = InstanceFactory::produce(comp, "inst1", Point(-100,50));
  Instance *inst2 = InstanceFactory::produce(comp, "inst2", Point(200,10));
  const std::vector<PaperUnit> path({50});
  Connection *con = ConnectionFactory::produce(inst1->getPorts().back(), inst2->getPorts().front(), path);

  con->accept(*writer);

  CPPUNIT_ASSERT_EQUAL(std::string("connection"), name());
  CPPUNIT_ASSERT_EQUAL(1, attributeCount());
  CPPUNIT_ASSERT_EQUAL(std::string("50"), attr("path"));

  ConnectionFactory::dispose(con);
  InstanceFactory::dispose(inst2);
  InstanceFactory::dispose(inst1);
  ComponentFactory::dispose(comp);
}




const TiXmlElement &XmlNodeWriterTest::getElement() const
{
  precondition(parent->FirstChildElement() != nullptr);
  precondition(parent->FirstChildElement() == parent->LastChild());
  return *parent->FirstChildElement();
}

int XmlNodeWriterTest::attributeCount() const
{
  int count = 0;
  for (const TiXmlAttribute *itr = getElement().FirstAttribute(); itr != nullptr; itr = itr->Next()) {
    count++;
  }
  return count;
}

std::string XmlNodeWriterTest::name() const
{
  return getElement().ValueStr();
}

std::string XmlNodeWriterTest::attr(const std::string &name) const
{
  return *getElement().Attribute(name);
}

std::string XmlNodeWriterTest::childAttr(int childIndex, const std::string &name) const
{
  return *getChild(childIndex)->Attribute(name);
}

std::string XmlNodeWriterTest::childName(int childIndex) const
{
  return getChild(childIndex)->ValueStr();
}

int XmlNodeWriterTest::childrenCount() const
{
  int count = 0;
  for (const TiXmlElement *itr = getElement().FirstChildElement(); itr != nullptr; itr = itr->NextSiblingElement()) {
    count++;
  }
  return count;
}

const TiXmlElement *XmlNodeWriterTest::getChild(int index) const
{
  int count = 0;
  for (const TiXmlElement *itr = getElement().FirstChildElement(); itr != nullptr; itr = itr->NextSiblingElement()) {
    if (count == index) {
      return itr;
    }
    count++;
  }
  throw std::invalid_argument("index out of range");
}


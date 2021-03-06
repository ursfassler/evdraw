// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "XmlReaderTest.hpp"

#include <core/component/Library.hpp>
#include <core/implementation/Composition.hpp>
#include <core/implementation/NullImplementation.hpp>
#include <file/xmlreader/XmlReader.hpp>
#include <sstream>
#include <stdio.h>


void XmlReaderTest::parseEmpty()
{
  const std::string xml =
      "<evdraw />";

  Library *lib = XmlReader::parse(xml);
  CPPUNIT_ASSERT(lib != nullptr);
  CPPUNIT_ASSERT_EQUAL(size_t(0), lib->getComponents().size());
  delete lib;
}

void XmlReaderTest::parseSimple()
{
  const std::string xml =
      "<evdraw>"
      "  <component name=\"Component\" />"
      "</evdraw>";

  Library *lib = XmlReader::parse(xml);

  CPPUNIT_ASSERT(lib != nullptr);
  CPPUNIT_ASSERT_EQUAL(size_t(1), lib->getComponents().size());
  IComponent *comp = lib->getComponents().front();
  CPPUNIT_ASSERT_EQUAL(std::string("Component"), comp->getName());
  CPPUNIT_ASSERT_EQUAL(size_t(0), comp->getPorts().size());
  CPPUNIT_ASSERT(dynamic_cast<NullImplementation*>(comp->getImplementation()) != nullptr);

  delete lib;
}

void XmlReaderTest::twoComponents()
{
  const std::string xml =
      "<evdraw>"
      "  <component name=\"Component1\" />"
      "  <component name=\"Component2\" />"
      "</evdraw>";

  Library *lib = XmlReader::parse(xml);

  CPPUNIT_ASSERT(lib != nullptr);
  CPPUNIT_ASSERT_EQUAL(size_t(2), lib->getComponents().size());
  CPPUNIT_ASSERT_EQUAL(std::string("Component1"), lib->getComponents().front()->getName());
  CPPUNIT_ASSERT_EQUAL(std::string("Component2"), lib->getComponents().back()->getName());

  delete lib;
}

void XmlReaderTest::componentWithSlot()
{
  const std::string xml =
      "<evdraw>"
      "  <component name=\"\">"
      "    <port type=\"slot\" name=\"in\" />"
      "  </component>"
      "</evdraw>";

  Library *lib = XmlReader::parse(xml);

  CPPUNIT_ASSERT(lib != nullptr);
  CPPUNIT_ASSERT_EQUAL(size_t(1), lib->getComponents().size());
  IComponent *comp = lib->getComponents().front();
  CPPUNIT_ASSERT_EQUAL(size_t(1), comp->getPorts().size());
  CPPUNIT_ASSERT_EQUAL(std::string("in"), comp->getPorts()[0]->getName());
  CPPUNIT_ASSERT(dynamic_cast<NullImplementation*>(comp->getImplementation()) != nullptr);

  delete lib;
}

void XmlReaderTest::componentWithSignal()
{
  const std::string xml =
      "<evdraw>"
      "  <component name=\"\">"
      "    <port type=\"signal\" name=\"out\" />"
      "  </component>"
      "</evdraw>";

  Library *lib = XmlReader::parse(xml);

  CPPUNIT_ASSERT(lib != nullptr);
  CPPUNIT_ASSERT_EQUAL(size_t(1), lib->getComponents().size());
  IComponent *comp = lib->getComponents().front();
  CPPUNIT_ASSERT_EQUAL(size_t(1), comp->getPorts().size());
  CPPUNIT_ASSERT_EQUAL(std::string("out"), comp->getPorts()[0]->getName());
  CPPUNIT_ASSERT(dynamic_cast<NullImplementation*>(comp->getImplementation()) != nullptr);

  delete lib;
}

void XmlReaderTest::componentWithSignalAndSlotKeepsOrder()
{
  const std::string xml =
      "<evdraw>"
      "  <component name=\"\">"
      "    <port type=\"signal\" name=\"out1\" />"
      "    <port type=\"slot\" name=\"in1\" />"
      "    <port type=\"slot\" name=\"in2\" />"
      "    <port type=\"signal\" name=\"out2\" />"
      "  </component>"
      "</evdraw>";

  Library *lib = XmlReader::parse(xml);

  CPPUNIT_ASSERT(lib != nullptr);
  CPPUNIT_ASSERT_EQUAL(size_t(1), lib->getComponents().size());
  IComponent *comp = lib->getComponents().front();
  CPPUNIT_ASSERT_EQUAL(size_t(4), comp->getPorts().size());
  CPPUNIT_ASSERT_EQUAL(std::string("out1"), comp->getPorts()[0]->getName());
  CPPUNIT_ASSERT_EQUAL(std::string("in1"), comp->getPorts()[1]->getName());
  CPPUNIT_ASSERT_EQUAL(std::string("in2"), comp->getPorts()[2]->getName());
  CPPUNIT_ASSERT_EQUAL(std::string("out2"), comp->getPorts()[3]->getName());

  delete lib;
}

void XmlReaderTest::compositionEmpty()
{
  const std::string xml =
      "<evdraw>"
      "  <component name=\"\">"
      "    <composition width=\"1234\" height=\"6543\"' />"
      "  </component>"
      "</evdraw>";

  Library *lib = XmlReader::parse(xml);

  CPPUNIT_ASSERT(lib != nullptr);
  CPPUNIT_ASSERT_EQUAL(size_t(1), lib->getComponents().size());
  IComponent *comp = lib->getComponents().front();
  Composition *composition = dynamic_cast<Composition*>(comp->getImplementation());
  CPPUNIT_ASSERT(composition != nullptr);
  ICompositionInstance *selfInst = composition->getSelfInstance();
  CPPUNIT_ASSERT_EQUAL(1234, selfInst->getWidth());
  CPPUNIT_ASSERT_EQUAL(6543, selfInst->getHeight());

  delete lib;
}

void XmlReaderTest::compositionWithInstance()
{
  const std::string xml =
      "<evdraw>"
      "  <component name=\"empty\" />"
      "  <component name=\"full\">"
      "    <composition width=\"1234\" height=\"6543\">"
      "      <instance name=\"instance\" component=\"empty\" x=\"10\" y=\"20\" >"
      "    </composition>"
      "  </component>"
      "</evdraw>";

  Library *lib = XmlReader::parse(xml);

  CPPUNIT_ASSERT(lib != nullptr);

  CPPUNIT_ASSERT_EQUAL(size_t(2), lib->getComponents().size());
  IComponent *empty = lib->getComponents().front();
  CPPUNIT_ASSERT_EQUAL(std::string("empty"), empty->getName());
  IComponent *full = lib->getComponents().back();
  CPPUNIT_ASSERT_EQUAL(std::string("full"), full->getName());

  Composition *composition = dynamic_cast<Composition*>(full->getImplementation());
  CPPUNIT_ASSERT(composition != nullptr);
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition->getInstances().size());
  IComponentInstance *instance = composition->getInstances().front();
  CPPUNIT_ASSERT_EQUAL(std::string("instance"), instance->getName());
  CPPUNIT_ASSERT_EQUAL(empty, instance->getComponent());

  CPPUNIT_ASSERT_EQUAL(Point(10,20), instance->getPosition().getAbsolutePosition());

  delete lib;
}

void XmlReaderTest::compositionWithConnection()
{
  const std::string xml =
      "<evdraw>"
      "  <component name=\"empty\">"
      "    <port type=\"slot\" name=\"in\" />"
      "    <port type=\"signal\" name=\"out\" />"
      "  </component>"
      "  <component name=\"full\">"
      "    <composition width=\"1234\" height=\"6543\">"
      "      <instance name=\"instance\" component=\"empty\" x=\"0\" y=\"0\" >"
      "      <connection path=\"100 -135 -120\" >"
      "        <instanceport instance=\"instance\" port=\"out\" />"
      "        <instanceport instance=\"instance\" port=\"in\" />"
      "      </connection>"
      "    </composition>"
      "  </component>"
      "</evdraw>";

  Library *lib = XmlReader::parse(xml);

  CPPUNIT_ASSERT(lib != nullptr);

  CPPUNIT_ASSERT_EQUAL(size_t(2), lib->getComponents().size());
  IComponent *empty = lib->getComponents().front();
  CPPUNIT_ASSERT_EQUAL(std::string("empty"), empty->getName());
  IComponent *full = lib->getComponents().back();
  CPPUNIT_ASSERT_EQUAL(std::string("full"), full->getName());

  Composition *composition = dynamic_cast<Composition*>(full->getImplementation());
  CPPUNIT_ASSERT(composition != nullptr);
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition->getInstances().size());
  auto *instance = composition->getInstances().front();
  CPPUNIT_ASSERT_EQUAL(std::string("instance"), instance->getName());
  CPPUNIT_ASSERT_EQUAL(empty, instance->getComponent());
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition->getConnections().size());
  Connection *con = composition->getConnections().front();
  CPPUNIT_ASSERT_EQUAL(size_t(6), con->getPoints().size());
  CPPUNIT_ASSERT_EQUAL(Point(100,-135), con->getPoints()[2]->getPosition().getAbsolutePosition());
  CPPUNIT_ASSERT_EQUAL(Point(-120,-135), con->getPoints()[3]->getPosition().getAbsolutePosition());

  delete lib;
}

void XmlReaderTest::CompositionInstance_with_connection()
{
  const std::string xml =
      "<evdraw>"
      "  <component name=\"test\">"
      "    <port type=\"slot\" name=\"in\" />"
      "    <port type=\"signal\" name=\"out\" />"
      "    <composition width=\"1234\" height=\"6543\">"
      "      <connection path=\"0\" >"
      "        <instanceport port=\"in\" />"
      "        <instanceport port=\"out\" />"
      "      </connection>"
      "    </composition>"
      "  </component>"
      "</evdraw>";

  Library *lib = XmlReader::parse(xml);

  CPPUNIT_ASSERT(lib != nullptr);

  CPPUNIT_ASSERT_EQUAL(size_t(1), lib->getComponents().size());
  IComponent *empty = lib->getComponents().front();
  CPPUNIT_ASSERT_EQUAL(std::string("test"), empty->getName());

  Composition *composition = dynamic_cast<Composition*>(empty->getImplementation());
  CPPUNIT_ASSERT(composition != nullptr);
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition->getConnections().size());

  delete lib;
}

void XmlReaderTest::openFile()
{
  const std::string xml =
      "<evdraw>"
      "  <component name=\"empty\">"
      "    <port type=\"slot\" name=\"in\" />"
      "    <port type=\"signal\" name=\"out\" />"
      "  </component>"
      "  <component name=\"full\">"
      "    <composition width=\"1234\" height=\"6543\">"
      "      <instance name=\"instance\" component=\"empty\" x=\"0\" y=\"0\" >"
      "      <connection path=\"100 -135 -120\" >"
      "        <instanceport instance=\"instance\" port=\"out\" />"
      "        <instanceport instance=\"instance\" port=\"in\" />"
      "      </connection>"
      "    </composition>"
      "  </component>"
      "</evdraw>";

  char filename[] = "testXXXXXX";
  int fd = mkstemp(filename);
  FILE *file = ::fdopen(fd, "w");
  ::fwrite(xml.c_str(), xml.size(), 1, file);
  ::fclose(file);

  Library *lib = XmlReader::loadFile(filename);

  ::remove(filename);

  CPPUNIT_ASSERT_EQUAL(size_t(2), lib->getComponents().size());

  delete lib;
}

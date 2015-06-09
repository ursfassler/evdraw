#include "XmlReaderTest.hpp"

#include <core/component/Library.hpp>
#include <core/implementation/Composition.hpp>
#include <file/XmlReader.hpp>
#include <sstream>


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
  Component *comp = lib->getComponents().front();
  CPPUNIT_ASSERT_EQUAL(std::string("Component"), comp->getName());
  CPPUNIT_ASSERT_EQUAL(size_t(0), comp->getPortLeft().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), comp->getPortRight().size());
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
      "    <slot name=\"in\" />"
      "  </component>"
      "</evdraw>";

  Library *lib = XmlReader::parse(xml);

  CPPUNIT_ASSERT(lib != nullptr);
  CPPUNIT_ASSERT_EQUAL(size_t(1), lib->getComponents().size());
  Component *comp = lib->getComponents().front();
  CPPUNIT_ASSERT_EQUAL(size_t(1), comp->getPortLeft().size());
  CPPUNIT_ASSERT_EQUAL(std::string("in"), comp->getPortLeft()[0]->getName());
  CPPUNIT_ASSERT_EQUAL(size_t(0), comp->getPortRight().size());
  CPPUNIT_ASSERT(dynamic_cast<NullImplementation*>(comp->getImplementation()) != nullptr);

  delete lib;
}

void XmlReaderTest::componentWithSignal()
{
  const std::string xml =
      "<evdraw>"
      "  <component name=\"\">"
      "    <signal name=\"out\" />"
      "  </component>"
      "</evdraw>";

  Library *lib = XmlReader::parse(xml);

  CPPUNIT_ASSERT(lib != nullptr);
  CPPUNIT_ASSERT_EQUAL(size_t(1), lib->getComponents().size());
  Component *comp = lib->getComponents().front();
  CPPUNIT_ASSERT_EQUAL(size_t(0), comp->getPortLeft().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), comp->getPortRight().size());
  CPPUNIT_ASSERT_EQUAL(std::string("out"), comp->getPortRight()[0]->getName());
  CPPUNIT_ASSERT(dynamic_cast<NullImplementation*>(comp->getImplementation()) != nullptr);

  delete lib;
}

void XmlReaderTest::compositionEmpty()
{
  const std::string xml =
      "<evdraw>"
      "  <component name=\"\">"
      "    <composition />"
      "  </component>"
      "</evdraw>";

  Library *lib = XmlReader::parse(xml);

  CPPUNIT_ASSERT(lib != nullptr);
  CPPUNIT_ASSERT_EQUAL(size_t(1), lib->getComponents().size());
  Component *comp = lib->getComponents().front();
  CPPUNIT_ASSERT(dynamic_cast<Composition*>(comp->getImplementation()) != nullptr);

  delete lib;
}

void XmlReaderTest::compositionWithInstance()
{
  const std::string xml =
      "<evdraw>"
      "  <component name=\"empty\" />"
      "  <component name=\"full\">"
      "    <composition>"
      "      <instance name=\"instance\" component=\"empty\">"
      "    </composition>"
      "  </component>"
      "</evdraw>";

  Library *lib = XmlReader::parse(xml);

  CPPUNIT_ASSERT(lib != nullptr);

  CPPUNIT_ASSERT_EQUAL(size_t(2), lib->getComponents().size());
  Component *empty = lib->getComponents().front();
  CPPUNIT_ASSERT_EQUAL(std::string("empty"), empty->getName());
  Component *full = lib->getComponents().back();
  CPPUNIT_ASSERT_EQUAL(std::string("full"), full->getName());

  Composition *composition = dynamic_cast<Composition*>(full->getImplementation());
  CPPUNIT_ASSERT(composition != nullptr);
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition->getInstances().size());
  Instance *instance = composition->getInstances().front();
  CPPUNIT_ASSERT_EQUAL(std::string("instance"), instance->getName());
  CPPUNIT_ASSERT_EQUAL(empty, instance->getComponent());

  delete lib;
}

void XmlReaderTest::compositionWithConnection()
{
  const std::string xml =
      "<evdraw>"
      "  <component name=\"empty\">"
      "    <slot name=\"in\" />"
      "    <signal name=\"out\" />"
      "  </component>"
      "  <component name=\"full\">"
      "    <composition>"
      "      <instance name=\"instance\" component=\"empty\">"
      "      <connection>"
      "        <instanceport instance=\"instance\" port=\"out\" />"
      "        <instanceport instance=\"instance\" port=\"in\" />"
      "      </connection>"
      "    </composition>"
      "  </component>"
      "</evdraw>";

  Library *lib = XmlReader::parse(xml);

  CPPUNIT_ASSERT(lib != nullptr);

  CPPUNIT_ASSERT_EQUAL(size_t(2), lib->getComponents().size());
  Component *empty = lib->getComponents().front();
  CPPUNIT_ASSERT_EQUAL(std::string("empty"), empty->getName());
  Component *full = lib->getComponents().back();
  CPPUNIT_ASSERT_EQUAL(std::string("full"), full->getName());

  Composition *composition = dynamic_cast<Composition*>(full->getImplementation());
  CPPUNIT_ASSERT(composition != nullptr);
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition->getInstances().size());
  Instance *instance = composition->getInstances().front();
  CPPUNIT_ASSERT_EQUAL(std::string("instance"), instance->getName());
  CPPUNIT_ASSERT_EQUAL(empty, instance->getComponent());
  CPPUNIT_ASSERT_EQUAL(size_t(1), composition->getConnections().size());

  delete lib;
}

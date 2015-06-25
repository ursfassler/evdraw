#include "ConnectionParserTest.hpp"

#include <core/implementation/NullImplementation.hpp>

void ConnectionTestEnvironment::setUp()
{
  compA = new Component("CompA", new NullImplementation());
  theCompPort1 = new Signal("thePort1");
  theCompPort2 = new Slot("thePort2");
  compA->addPort(theCompPort1);
  compA->addPort(theCompPort2);

  theInstance = new Instance("theInstance", Point(0,0), compA);
  theInstPort1 = new InstancePort(theInstance, theCompPort1, Point(0,0));
  theInstPort2 = new InstancePort(theInstance, theCompPort2, Point(0,0));
  theInstance->addPort(theInstPort1);
  theInstance->addPort(theInstPort2);
  composition = new Composition();
  composition->addInstance(theInstance);
  compB = new Component("CompB", composition);

  library = new Library();
  library->add(compA);
  library->add(compB);

  element = new TiXmlElement("");
}

void ConnectionTestEnvironment::tearDown()
{
  delete element;
  delete library;
}

void ConnectionPortParserTest::setUp()
{
  ConnectionTestEnvironment::setUp();
  parser = new ConnectionPortParser(*library, *element, *composition);
}

void ConnectionPortParserTest::tearDown()
{
  delete parser;
  ConnectionTestEnvironment::tearDown();
}

void ConnectionPortParserTest::getInstance()
{
  element->SetAttribute("instance", "theInstance");
  CPPUNIT_ASSERT_EQUAL(theInstance, parser->instance());
}

void ConnectionPortParserTest::getPort()
{
  element->SetAttribute("instance", "theInstance");
  element->SetAttribute("port", "thePort1");
  CPPUNIT_ASSERT_EQUAL(theInstPort1, parser->port());
}




void ConnectionParserTest::setUp()
{
  ConnectionTestEnvironment::setUp();
  parser = new ConnectionParser(*library, *element, *composition);
}

void ConnectionParserTest::tearDown()
{
  ConnectionTestEnvironment::tearDown();
  delete parser;
}

void ConnectionParserTest::path()
{
  element->SetAttribute("path", "10 3 -4 15");
  CPPUNIT_ASSERT_EQUAL(std::vector<PaperUnit>({10, 3, -4, 15}), parser->path());
}

void ConnectionParserTest::pathNotSet()
{
  CPPUNIT_ASSERT_THROW(parser->path(), NoSuchAttributeException);
}

void ConnectionParserTest::pathHasInvalidContent()
{
  element->SetAttribute("path", "10 lala -4 15");
  CPPUNIT_ASSERT_THROW(parser->path(), std::invalid_argument);
}

void ConnectionParserTest::startPort()
{
  TiXmlElement connection("");
  connection.SetAttribute("instance", "theInstance");
  connection.SetAttribute("port", "thePort1");
  element->InsertEndChild(connection);

  CPPUNIT_ASSERT_EQUAL(theInstPort1, parser->startPort());
}

void ConnectionParserTest::endPort()
{
  TiXmlElement startPort("");
  element->InsertEndChild(startPort);

  TiXmlElement endPort("");
  endPort.SetAttribute("instance", "theInstance");
  endPort.SetAttribute("port", "thePort1");
  element->InsertEndChild(endPort);

  CPPUNIT_ASSERT_EQUAL(theInstPort1, parser->endPort());
}

void ConnectionParserTest::startAndEndPort()
{
  TiXmlElement startPort("");
  startPort.SetAttribute("instance", "theInstance");
  startPort.SetAttribute("port", "thePort1");
  element->InsertEndChild(startPort);

  TiXmlElement endPort("");
  endPort.SetAttribute("instance", "theInstance");
  endPort.SetAttribute("port", "thePort2");
  element->InsertEndChild(endPort);

  CPPUNIT_ASSERT_EQUAL(theInstPort1, parser->startPort());
  CPPUNIT_ASSERT_EQUAL(theInstPort2, parser->endPort());
}

void ConnectionParserTest::startPortDoesNotExist()
{
  CPPUNIT_ASSERT_THROW(parser->startPort(), NoSuchElementException);
}

void ConnectionParserTest::endPortDoesNotExist()
{
  CPPUNIT_ASSERT_THROW(parser->endPort(), NoSuchElementException);
}

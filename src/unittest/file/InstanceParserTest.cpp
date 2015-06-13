#include "InstanceParserTest.hpp"

#include <file/InstanceParser.hpp>

void InstanceParserTest::create()
{
  Library library;
  TiXmlElement  element("");
  InstanceParser parser(library, element);

  CPPUNIT_ASSERT_EQUAL(static_cast<const TiXmlElement*>(&element), &parser.element);
  CPPUNIT_ASSERT_EQUAL(static_cast<const Library*>(&library), &parser.library);
}

void InstanceParserTest::component()
{
  Component *comp = new Component("TheComponent");
  Library library;
  library.add(comp);

  TiXmlElement  element("");
  element.SetAttribute("component", "TheComponent");

  InstanceParser parser(library, element);

  CPPUNIT_ASSERT_EQUAL(comp, parser.component());
}

void InstanceParserTest::componentDoesNotExist()
{
  Library library;
  TiXmlElement  element("");
  element.SetAttribute("component", "TheComponent");

  InstanceParser parser(library, element);

  CPPUNIT_ASSERT_THROW(parser.component(), std::invalid_argument);
}

void InstanceParserTest::name()
{
  Library library;
  TiXmlElement  element("");
  element.SetAttribute("name", "TheName");

  InstanceParser parser(library, element);

  CPPUNIT_ASSERT_EQUAL(std::string("TheName"), parser.name());
}

void InstanceParserTest::nameNotSet()
{
  Library library;
  TiXmlElement  element("");
  InstanceParser parser(library, element);

  CPPUNIT_ASSERT_THROW(parser.name(), NoSuchAttributeException);
}

void InstanceParserTest::position()
{
  Library library;
  TiXmlElement  element("");
  element.SetAttribute("x", "10");
  element.SetAttribute("y", "30");

  InstanceParser parser(library, element);

  CPPUNIT_ASSERT_EQUAL(Point(10,30), parser.position());
}

void InstanceParserTest::positionXNotSet()
{
  Library library;
  TiXmlElement  element("");
  element.SetAttribute("y", "0");

  InstanceParser parser(library, element);

  CPPUNIT_ASSERT_THROW(parser.position(), NoSuchAttributeException);
}

void InstanceParserTest::positionYNotSet()
{
  Library library;
  TiXmlElement  element("");
  element.SetAttribute("x", "0");

  InstanceParser parser(library, element);

  CPPUNIT_ASSERT_THROW(parser.position(), NoSuchAttributeException);
}


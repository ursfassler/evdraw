#include "BaseParserTest.hpp"

#include <file/xmlreader/BaseParser.hpp>

#include <stdexcept>

void BaseParserTest::throwNoSuchAttributeException()
{
  NoSuchAttributeException exception("attrName");
  CPPUNIT_ASSERT_EQUAL(std::string("attribute not found: attrName"), std::string(exception.what()));
}

void BaseParserTest::noSuchElementException()
{
  NoSuchElementException exception;
  CPPUNIT_ASSERT_EQUAL(std::string("element not found"), std::string(exception.what()));
}

void BaseParserTest::create()
{
  Library library;
  TiXmlElement  element("");
  BaseParser parser(library, element);

  CPPUNIT_ASSERT_EQUAL(static_cast<const TiXmlElement*>(&element), &parser.element);
  CPPUNIT_ASSERT_EQUAL(static_cast<const Library*>(&library), &parser.library);
}

void BaseParserTest::getExistingAttribute()
{
  Library library;
  TiXmlElement  element("");
  element.SetAttribute("attrName", "attrValue");
  BaseParser parser(library, element);

  CPPUNIT_ASSERT_EQUAL(std::string("attrValue"), parser.getAttribute("attrName"));
}

void BaseParserTest::getNonExistingAttribute()
{
  Library library;
  TiXmlElement  element("");
  BaseParser parser(library, element);

  CPPUNIT_ASSERT_THROW(parser.getAttribute("attrName"), NoSuchAttributeException);
}


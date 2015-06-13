#include "BaseParser.hpp"

NoSuchAttributeException::NoSuchAttributeException(const std::string &aAttributeName) :
  attributeName(aAttributeName)
{
}

const char *NoSuchAttributeException::what() const _GLIBCXX_USE_NOEXCEPT
{
  return ("attribute not found: " + attributeName).c_str();
}


BaseParser::BaseParser(const Library &aLibrary, const TiXmlElement &aElement) :
  library(aLibrary),
  element(aElement)
{
}

std::string BaseParser::getAttribute(const std::string &attribute) const
{
  std::string value = "";
  if (element.QueryStringAttribute(attribute.c_str(), &value) != TIXML_SUCCESS) {
    throw NoSuchAttributeException(attribute);
  }
  return value;
}


const char *NoSuchElementException::what() const _GLIBCXX_USE_NOEXCEPT
{
  return "element not found";
}

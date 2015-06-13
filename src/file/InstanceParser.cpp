#include "InstanceParser.hpp"

InstanceParser::InstanceParser(const Library &library, const TiXmlElement &element) :
  BaseParser(library, element)
{
}

Component *InstanceParser::component() const
{
  const std::string componentName = getAttribute("component");
  return library.getComponent(componentName);
}

std::string InstanceParser::name() const
{
  return getAttribute("name");
}

Point InstanceParser::position() const
{
  const PaperUnit x = std::atoi(getAttribute("x").c_str());
  const PaperUnit y = std::atoi(getAttribute("y").c_str());
  return Point(x,y);
}

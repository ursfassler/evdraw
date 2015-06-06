#include "XmlReader.hpp"

XmlReader::XmlReader()
{
}

void XmlReader::parse(const std::string &data)
{
  TiXmlDocument doc;
  doc.Parse(data.c_str());
}

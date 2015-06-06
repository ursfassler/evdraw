#ifndef XMLREADER_HPP
#define XMLREADER_HPP

#include <tinyxml.h>

class XmlVisitor : public TiXmlVisitor
{

};

class XmlReader
{
  public:
    XmlReader();

    void parse(const std::string &data);
};

#endif // XMLREADER_HPP

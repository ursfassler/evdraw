#ifndef CONNECTIONPARSER_HPP
#define CONNECTIONPARSER_HPP

#include "BaseParser.hpp"
#include "../core/connection/AbstractPort.hpp"

class ConnectionPortParserTest;

class ConnectionPortParser final : protected BaseParser
{
  public:
    ConnectionPortParser(const Library &library, const TiXmlElement &element, const Composition &composition);

    Instance *instance() const;
    AbstractPort *port() const;

  private:
    const Composition &composition;

    friend ConnectionPortParserTest;
};


class ConnectionParserTest;

class ConnectionParser final : protected BaseParser
{
  public:
    ConnectionParser(const Library &library, const TiXmlElement &element, const Composition &composition);

    std::vector<PaperUnit> path() const;
    AbstractPort *startPort() const;
    AbstractPort *endPort() const;

  private:
    const Composition &composition;
    AbstractPort *port(unsigned index) const;
    std::vector<std::string> splitString(const std::string value) const;
    std::vector<PaperUnit> parsePath(const std::string &path) const;
    const TiXmlElement *childElement(unsigned index) const;

    friend ConnectionParserTest;
};


#endif // CONNECTIONPARSER_HPP

// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ConnectionParser.hpp"

#include <core/implementation/Composition.hpp>

#include <regex>


ConnectionPortParser::ConnectionPortParser(const Library &library, const TiXmlElement &element, const Composition &aComposition) :
  BaseParser(library, element),
  composition(aComposition)
{
  (void)(composition);
}

Instance *ConnectionPortParser::instance() const
{
  const std::string instanceName = getAttribute("instance");
  return composition.getInstance(instanceName);
}

AbstractPort *ConnectionPortParser::port() const
{
  const std::string portName = getAttribute("port");
  return instance()->getPort(portName);
}





ConnectionParser::ConnectionParser(const Library &library, const TiXmlElement &element, const Composition &aComposition):
  BaseParser(library, element),
  composition(aComposition)
{
}

std::vector<PaperUnit> ConnectionParser::path() const
{
  return parsePath(getAttribute("path"));
}

AbstractPort *ConnectionParser::startPort() const
{
  const TiXmlElement *child = childElement(0);
  ConnectionPortParser pp(library, *child, composition);
  return pp.port();
}

AbstractPort *ConnectionParser::endPort() const
{
  const TiXmlElement *child = childElement(1);
  ConnectionPortParser pp(library, *child, composition);
  return pp.port();
}

AbstractPort *ConnectionParser::port(unsigned index) const
{
  const TiXmlElement *child = childElement(index);
  ConnectionPortParser pp(library, *child, composition);
  return pp.port();
}

std::vector<std::string> ConnectionParser::splitString(const std::string value) const
{
  std::regex regex(" ");
  std::regex_token_iterator<std::string::const_iterator>  first(value.begin(), value.end(), regex, -1);
  std::regex_token_iterator<std::string::const_iterator>  last;
  return std::vector<std::string>(first, last);
}

std::vector<PaperUnit> ConnectionParser::parsePath(const std::string &path) const
{
  std::vector<std::string> tokens = splitString(path);
  std::vector<PaperUnit> ret;

  for (const std::string &itr : tokens) {
    ret.push_back(std::stoi(itr));
  }

  return ret;
}

const TiXmlElement *ConnectionParser::childElement(unsigned index) const
{
  unsigned nr = 0;
  for (const TiXmlElement *itr = element.FirstChildElement(); itr != nullptr; itr = itr->NextSiblingElement()) {
    if (nr == index) {
      return itr;
    } else {
      nr++;
    }
  }

  throw NoSuchElementException();
}

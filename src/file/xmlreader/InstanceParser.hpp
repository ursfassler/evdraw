// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef INSTANCEPARSER_HPP
#define INSTANCEPARSER_HPP

#include <core/Point.hpp>

#include "BaseParser.hpp"

class InstanceParserTest;

class InstanceParser final : protected BaseParser
{
  public:
    InstanceParser(const Library &library, const TiXmlElement &element);

    Component *component() const;
    std::string name() const;
    Point position() const;

  private:

    friend InstanceParserTest;
};


#endif // INSTANCEPARSER_HPP

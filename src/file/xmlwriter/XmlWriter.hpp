// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef XMLWRITER_HPP
#define XMLWRITER_HPP

#include <core/component/Library.hpp>
#include <tinyxml.h>
#include <string>

class XmlWriter
{
  public:
    static TiXmlDocument *write(const Library &library);
    static void saveFile(const std::string &filename, const Library &library);
};

#endif // XMLWRITER_HPP

// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "XmlWriterTest.hpp"

#include <core/component/Library.hpp>
#include <tinyxml.h>
#include <file/xmlwriter/XmlWriter.hpp>

#include <fstream>

#include <stdio.h>
#include <unistd.h>

void XmlWriterTest::emptyToXml()
{
  Library lib;

  TiXmlDocument *doc = XmlWriter::write(lib);
  CPPUNIT_ASSERT(doc != nullptr);
  CPPUNIT_ASSERT(doc->RootElement() != nullptr);
  CPPUNIT_ASSERT_EQUAL(std::string("evdraw"), doc->RootElement()->ValueStr());

  delete doc;
}

void XmlWriterTest::writeEmpty()
{
  char filename[] = "testXXXXXX";
  int fd = mkstemp(filename);
  ::close(fd);

  Library lib;
  XmlWriter::saveFile(filename, lib);

  std::ifstream file;
  file.open(filename);

  char line[200];
  CPPUNIT_ASSERT(file.getline(line, sizeof(line)));
  CPPUNIT_ASSERT_EQUAL(std::string("<evdraw />"), std::string(line));
  CPPUNIT_ASSERT(!file.getline(line, sizeof(line)));

  file.close();
  ::remove(filename);
}

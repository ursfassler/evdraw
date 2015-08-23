// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "XmlWriter.hpp"

#include "XmlNodeWriter.hpp"

TiXmlDocument *XmlWriter::write(const Library &library)
{
  TiXmlDocument *doc = new TiXmlDocument();

  XmlNodeWriter writer(doc);
  library.accept(writer);

  return doc;
}

void XmlWriter::saveFile(const std::string &filename, const Library &library)
{
  TiXmlDocument *doc = write(library);
  doc->SaveFile(filename);
  delete doc;
}

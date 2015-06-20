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

#include "XmlReaderTest.hpp"

#include <file/XmlReader.hpp>
#include <sstream>


static const std::string fileContent =
    "<evdraw>"
    "  <component name=\"Component\">"
    "    <slot name=\"in\" />"
    "    <signal name=\"out\" />"
    "  </component>"
    "  <component name=\"Drawing\">"
    "    <composition>"
    "      <instance name=\"instance\" component=\"Component\">"
    "      <connection>"
    "        <instanceport instance=\"instance\" port=\"out\" />"
    "        <instanceport instance=\"instance\" port=\"in\" />"
    "      </connection>"
    "    </composition>"
    "  </component>"
    "</evdraw>";

void XmlReaderTest::readEmpty()
{
  XmlReader reader;
  reader.parse("");
}

void XmlReaderTest::parseFull()
{
  XmlReader reader;
  reader.parse(fileContent);
}

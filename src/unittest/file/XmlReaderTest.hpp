#ifndef XMLREADERTEST_HPP
#define XMLREADERTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class XmlReaderTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( XmlReaderTest );

    CPPUNIT_TEST(readEmpty);
    CPPUNIT_TEST(parseFull);

    CPPUNIT_TEST_SUITE_END();

  public:
    void readEmpty();
    void parseFull();
};

CPPUNIT_TEST_SUITE_REGISTRATION( XmlReaderTest );

#endif // XMLREADERTEST_HPP

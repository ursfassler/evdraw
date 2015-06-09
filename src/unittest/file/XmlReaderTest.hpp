#ifndef XMLREADERTEST_HPP
#define XMLREADERTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class XmlReaderTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( XmlReaderTest );

    CPPUNIT_TEST(parseEmpty);
    CPPUNIT_TEST(parseSimple);
    CPPUNIT_TEST(twoComponents);

    CPPUNIT_TEST(componentWithSlot);
    CPPUNIT_TEST(componentWithSignal);

    CPPUNIT_TEST(compositionEmpty);
    CPPUNIT_TEST(compositionWithInstance);
    CPPUNIT_TEST(compositionWithConnection);

    CPPUNIT_TEST_SUITE_END();

  public:
    void parseEmpty();
    void parseSimple();
    void twoComponents();

    void componentWithSlot();
    void componentWithSignal();

    void compositionEmpty();
    void compositionWithInstance();
    void compositionWithConnection();
};

CPPUNIT_TEST_SUITE_REGISTRATION( XmlReaderTest );

#endif // XMLREADERTEST_HPP

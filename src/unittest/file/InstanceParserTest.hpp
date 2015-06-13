#ifndef INSTANCEPARSERTEST_HPP
#define INSTANCEPARSERTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class InstanceParserTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( InstanceParserTest );

    CPPUNIT_TEST(create);
    CPPUNIT_TEST(component);
    CPPUNIT_TEST(componentDoesNotExist);
    CPPUNIT_TEST(name);
    CPPUNIT_TEST(nameNotSet);
    CPPUNIT_TEST(position);
    CPPUNIT_TEST(positionXNotSet);
    CPPUNIT_TEST(positionYNotSet);

    CPPUNIT_TEST_SUITE_END();

  public:
    void create();
    void component();
    void componentDoesNotExist();
    void name();
    void nameNotSet();
    void position();
    void positionXNotSet();
    void positionYNotSet();

};

CPPUNIT_TEST_SUITE_REGISTRATION( InstanceParserTest );


#endif // INSTANCEPARSERTEST_HPP

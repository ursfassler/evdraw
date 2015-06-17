#ifndef BASEPARSERTEST_HPP
#define BASEPARSERTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class BaseParserTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( BaseParserTest );

    CPPUNIT_TEST(throwNoSuchAttributeException);
    CPPUNIT_TEST(noSuchElementException);

    CPPUNIT_TEST(create);
    CPPUNIT_TEST(getExistingAttribute);
    CPPUNIT_TEST(getNonExistingAttribute);

    CPPUNIT_TEST_SUITE_END();

  public:
    void throwNoSuchAttributeException();
    void noSuchElementException();

    void create();
    void getExistingAttribute();
    void getNonExistingAttribute();

};

CPPUNIT_TEST_SUITE_REGISTRATION( BaseParserTest );


#endif // BASEPARSERTEST_HPP

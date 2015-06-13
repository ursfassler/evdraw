#ifndef TYPESTEST_HPP
#define TYPESTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TypesTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( TypesTest );

    CPPUNIT_TEST(printConnectorSideLeft);
    CPPUNIT_TEST(printConnectorSideRight);

    CPPUNIT_TEST(printVectorOfPaperUnit);

    CPPUNIT_TEST_SUITE_END();

  public:
    void printConnectorSideLeft();
    void printConnectorSideRight();

    void printVectorOfPaperUnit();

};

CPPUNIT_TEST_SUITE_REGISTRATION( TypesTest );


#endif // TYPESTEST_HPP

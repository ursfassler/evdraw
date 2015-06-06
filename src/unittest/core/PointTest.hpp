#ifndef POINTTEST_HPP
#define POINTTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class PointTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( PointTest );

    CPPUNIT_TEST(create);
    CPPUNIT_TEST(print);
    CPPUNIT_TEST(equal);
    CPPUNIT_TEST(notEqual);
    CPPUNIT_TEST(plus);
    CPPUNIT_TEST(minus);
    CPPUNIT_TEST(unaryMinus);
    CPPUNIT_TEST(divisionByScalar);

    CPPUNIT_TEST_SUITE_END();

  public:
    void create();
    void print();
    void equal();
    void notEqual();
    void plus();
    void minus();
    void unaryMinus();
    void divisionByScalar();
};

CPPUNIT_TEST_SUITE_REGISTRATION( PointTest );


#endif // POINTTEST_HPP

#ifndef ERRORTEST_HPP
#define ERRORTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class errorTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( errorTest );

    CPPUNIT_TEST(unreachableCode_throws_exception);
    CPPUNIT_TEST(notYetImplemented_throws_exception);

    CPPUNIT_TEST_SUITE_END();

  public:
    void unreachableCode_throws_exception();
    void notYetImplemented_throws_exception();

};

CPPUNIT_TEST_SUITE_REGISTRATION( errorTest );


#endif // ERRORTEST_HPP

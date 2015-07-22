#ifndef CHILDREMOVERTEST_HPP
#define CHILDREMOVERTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ChildRemoverTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ChildRemoverTest );

    CPPUNIT_TEST(inheritsDefaultVisitor);
    CPPUNIT_TEST(compositionRemovesInstance);
    CPPUNIT_TEST(compositionRemovesConnection);

    CPPUNIT_TEST_SUITE_END();

  public:
    void inheritsDefaultVisitor();
    void compositionRemovesInstance();
    void compositionRemovesConnection();

};

CPPUNIT_TEST_SUITE_REGISTRATION( ChildRemoverTest );

#endif // CHILDREMOVERTEST_HPP

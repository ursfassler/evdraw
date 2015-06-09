#ifndef LISTTEST_HPP
#define LISTTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ListTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ListTest );

    CPPUNIT_TEST(containsInt);
    CPPUNIT_TEST(notContainsInt);
    CPPUNIT_TEST(containsStringPointer);
    CPPUNIT_TEST(notContainsStringPointer);

    CPPUNIT_TEST(indexOfInt);
    CPPUNIT_TEST(noIndexOfInt);
    CPPUNIT_TEST(indexOfStringPointer);

    CPPUNIT_TEST(listGetWithPredicate);
    CPPUNIT_TEST(listGetThrowsErrorWhenNotFound);

    CPPUNIT_TEST_SUITE_END();

  public:
    void containsInt();
    void notContainsInt();
    void containsStringPointer();
    void notContainsStringPointer();

    void indexOfInt();
    void noIndexOfInt();
    void indexOfStringPointer();

    void listGetWithPredicate();
    void listGetThrowsErrorWhenNotFound();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ListTest );

#endif // LISTTEST_HPP

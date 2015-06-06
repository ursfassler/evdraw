#ifndef LIBRARYTEST_HPP
#define LIBRARYTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class LibraryTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( LibraryTest );

    CPPUNIT_TEST(create);
    CPPUNIT_TEST(addComponent);
    CPPUNIT_TEST(deletsComponentsWhenDeleted);

    CPPUNIT_TEST_SUITE_END();

  public:
    void create();
    void addComponent();
    void deletsComponentsWhenDeleted();

};

CPPUNIT_TEST_SUITE_REGISTRATION( LibraryTest );


#endif // LIBRARYTEST_HPP

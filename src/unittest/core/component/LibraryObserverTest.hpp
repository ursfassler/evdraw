#ifndef LIBRARYOBSERVERTEST_HPP
#define LIBRARYOBSERVERTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class LibraryObserverTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( LibraryObserverTest );

    CPPUNIT_TEST(destructorIsVirtual);
    CPPUNIT_TEST(libraryInheritsObserverCollection);

    CPPUNIT_TEST(getInformedOnAdd);
    CPPUNIT_TEST(getInformedOnDelete);

    CPPUNIT_TEST_SUITE_END();

  public:
    void destructorIsVirtual();
    void libraryInheritsObserverCollection();

    void getInformedOnAdd();
    void getInformedOnDelete();

};

CPPUNIT_TEST_SUITE_REGISTRATION( LibraryObserverTest );


#endif // LIBRARYOBSERVERTEST_HPP

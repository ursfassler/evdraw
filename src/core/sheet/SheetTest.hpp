#ifndef SHEETTEST_HPP
#define SHEETTEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class SheetTest: public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( SheetTest );

    CPPUNIT_TEST(create);
    CPPUNIT_TEST(addInstance);
    CPPUNIT_TEST(addConnection);

    CPPUNIT_TEST_SUITE_END();

  public:
    void create();
    void addInstance();
    void addConnection();

};

CPPUNIT_TEST_SUITE_REGISTRATION( SheetTest );


#endif // SHEETTEST_HPP

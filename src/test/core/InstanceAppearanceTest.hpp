#ifndef INSTANCEAPPEARANCETEST_HPP
#define INSTANCEAPPEARANCETEST_HPP

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class InstanceAppearanceTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( InstanceAppearanceTest );

    CPPUNIT_TEST(dimension);
    CPPUNIT_TEST(width);
    CPPUNIT_TEST(height);

    CPPUNIT_TEST_SUITE_END();

  public:
    void dimension();
    void width();
    void height();

};

CPPUNIT_TEST_SUITE_REGISTRATION( InstanceAppearanceTest );


#endif // INSTANCEAPPEARANCETEST_HPP

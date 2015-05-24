#ifndef POINTTEST_HPP
#define POINTTEST_HPP

#include "Endpoint.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class EndpointTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( EndpointTest );

    CPPUNIT_TEST(initialPortPointPosition);
    CPPUNIT_TEST(portPointIsFixed);

    CPPUNIT_TEST(initialIntermediatePointPosition);
    CPPUNIT_TEST(intermediatePointIsMovable);

    CPPUNIT_TEST(setPosition);

    CPPUNIT_TEST(notifyListenerOnPosChange);

    CPPUNIT_TEST_SUITE_END();

  public:
    void initialPortPointPosition();
    void portPointIsFixed();

    void initialIntermediatePointPosition();
    void intermediatePointIsMovable();

    void setPosition();

    void notifyListenerOnPosChange();

};

CPPUNIT_TEST_SUITE_REGISTRATION( EndpointTest );

#endif // POINTTEST_HPP

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

    CPPUNIT_TEST(setXpos);
    CPPUNIT_TEST(setYpos);

    CPPUNIT_TEST(addRemoveListener);
    CPPUNIT_TEST(notifyListenerX);
    CPPUNIT_TEST(notifyListenerY);

    CPPUNIT_TEST_SUITE_END();

  public:
    void initialPortPointPosition();
    void portPointIsFixed();

    void initialIntermediatePointPosition();
    void intermediatePointIsMovable();

    void setXpos();
    void setYpos();

    void addRemoveListener();
    void notifyListenerX();
    void notifyListenerY();

};

CPPUNIT_TEST_SUITE_REGISTRATION( EndpointTest );

#endif // POINTTEST_HPP

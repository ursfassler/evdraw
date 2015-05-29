#ifndef SEGMENTTEST_HPP
#define SEGMENTTEST_HPP

#include "Endpoint.hpp"
#include "Segment.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class SegmentTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( SegmentTest );

    CPPUNIT_TEST(createSegment);
    CPPUNIT_TEST(setStart);
    CPPUNIT_TEST(setEnd);

    CPPUNIT_TEST(checkFixedFixed);
    CPPUNIT_TEST(checkFixedMovable);
    CPPUNIT_TEST(checkMovableFixed);
    CPPUNIT_TEST(checkMovableMovable);

    CPPUNIT_TEST_SUITE_END();

  public:
    void createSegment();
    void setStart();
    void setEnd();

    void checkFixedFixed();
    void checkFixedMovable();
    void checkMovableFixed();
    void checkMovableMovable();
};

CPPUNIT_TEST_SUITE_REGISTRATION( SegmentTest );

class HorizontalSegmentTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( HorizontalSegmentTest );

    CPPUNIT_TEST(createSegment);

    CPPUNIT_TEST(getY0);
    CPPUNIT_TEST(getY42);
    CPPUNIT_TEST(getY_23_42);

    CPPUNIT_TEST(moveZero);
    CPPUNIT_TEST(move42);
    CPPUNIT_TEST(moveUnmoveable);

    CPPUNIT_TEST(notifyListenerOnPositionChange);

    CPPUNIT_TEST_SUITE_END();

  public:
    void createSegment();

    void getY0();
    void getY42();
    void getY_23_42();

    void moveZero();
    void move42();
    void moveUnmoveable();

    void notifyListenerOnPositionChange();
};

CPPUNIT_TEST_SUITE_REGISTRATION( HorizontalSegmentTest );

class VerticalSegmentTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( VerticalSegmentTest );

    CPPUNIT_TEST(createSegment);

    CPPUNIT_TEST(getX0);
    CPPUNIT_TEST(getX42);
    CPPUNIT_TEST(getX_23_42);

    CPPUNIT_TEST(moveZero);
    CPPUNIT_TEST(move42);
    CPPUNIT_TEST(moveUnmoveable);

    CPPUNIT_TEST(notifyListenerOnPositionChange);

    CPPUNIT_TEST_SUITE_END();

  public:
    void createSegment();

    void getX0();
    void getX42();
    void getX_23_42();

    void moveZero();
    void move42();
    void moveUnmoveable();

    void notifyListenerOnPositionChange();
};

CPPUNIT_TEST_SUITE_REGISTRATION( VerticalSegmentTest );

class MultiSegment
{
  public:
    MultiSegment(PaperUnit x0, PaperUnit y0, PaperUnit xm, PaperUnit y1, PaperUnit x1);

    PortPoint         m0;
    IntermediatePoint m1;
    IntermediatePoint m2;
    PortPoint         m3;

    HorizontalSegment s0;
    VerticalSegment   s1;
    HorizontalSegment s2;
};

class MultiSegmentTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( MultiSegmentTest );

    CPPUNIT_TEST(createSegment);
    CPPUNIT_TEST(moveSegment);
    CPPUNIT_TEST(moveIntermediatePoint);
    CPPUNIT_TEST(movePortPoint);

    CPPUNIT_TEST_SUITE_END();

  public:
    void createSegment();
    void moveSegment();
    void moveIntermediatePoint();
    void movePortPoint();

};

CPPUNIT_TEST_SUITE_REGISTRATION( MultiSegmentTest );

#endif // SEGMENTTEST_HPP

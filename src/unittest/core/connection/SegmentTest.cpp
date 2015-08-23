// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "SegmentTest.hpp"

class SegObserver : public SegmentObserver
{
  public:
    void positionChanged(const Segment *sender)
    {
      lastSender = sender;
    }

    Segment const *lastSender = nullptr;
};

void SegmentTest::createSegment()
{
  Endpoint start(Point(1, 2));
  Endpoint end(Point(3, 4));
  Segment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&start), segment.getStart());
  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&end), segment.getEnd());
}

void SegmentTest::setStart()
{
  Endpoint start(Point(1, 2));
  Endpoint start2(Point(5, 6));
  Endpoint end(Point(3, 4));

  Segment segment(&start, &end);

  segment.setStart(&start2);

  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&start2), segment.getStart());
  CPPUNIT_ASSERT(!start.hasObserver());
  CPPUNIT_ASSERT(start2.hasObserver());
}

void SegmentTest::setEnd()
{
  Endpoint start(Point(1, 2));
  Endpoint end(Point(3, 4));
  Endpoint end2(Point(5, 6));

  Segment segment(&start, &end);

  segment.setEnd(&end2);

  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&end2), segment.getEnd());
  CPPUNIT_ASSERT(!end.hasObserver());
  CPPUNIT_ASSERT(end2.hasObserver());
}

void SegmentTest::checkFixedFixed()
{
  RelativePosition p(Point(0,0));
  Endpoint start(Point(0, 0));
  Endpoint end(Point(0, 0));
  start.replaceAnchor(&p);
  end.replaceAnchor(&p);
  Segment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(false, segment.moveable());
}

void SegmentTest::checkFixedMovable()
{
  RelativePosition p(Point(0,0));
  Endpoint start(Point(0, 0));
  Endpoint end(Point(0, 0));
  start.replaceAnchor(&p);
  Segment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(false, segment.moveable());
}

void SegmentTest::checkMovableFixed()
{
  RelativePosition p(Point(0,0));
  Endpoint start(Point(0, 0));
  Endpoint end(Point(0, 0));
  end.replaceAnchor(&p);
  Segment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(false, segment.moveable());
}

void SegmentTest::checkMovableMovable()
{
  Endpoint start(Point(0, 0));
  Endpoint end(Point(0, 0));
  Segment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(true, segment.moveable());
}


void HorizontalSegmentTest::createSegment()
{
  Endpoint start(Point(1, 2));
  Endpoint end(Point(3, 4));
  HorizontalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&start), segment.getStart());
  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&end), segment.getEnd());
}

void HorizontalSegmentTest::getY0()
{
  Endpoint start(Point(0, 0));
  Endpoint end(Point(0, 0));
  HorizontalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(0, segment.getY());
}

void HorizontalSegmentTest::getY42()
{
  Endpoint start(Point(0, 42));
  Endpoint end(Point(0, 42));

  HorizontalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(42, segment.getY());
}

void HorizontalSegmentTest::getY_23_42()
{
  Endpoint start(Point(0, 23));
  Endpoint end(Point(0, 42));

  HorizontalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(23, segment.getY());
}

void HorizontalSegmentTest::moveZero()
{
  Endpoint start(Point(-10, 0));
  Endpoint end(Point(10, 0));

  HorizontalSegment segment(&start, &end);

  segment.moveToY(0);

  CPPUNIT_ASSERT_EQUAL(Point(-10,0), start.getOffset());
  CPPUNIT_ASSERT_EQUAL(Point( 10,0), end.getOffset());
}

void HorizontalSegmentTest::move42()
{
  Endpoint start(Point(-10, 0));
  Endpoint end(Point(10, 0));

  HorizontalSegment segment(&start, &end);

  segment.moveToY(42);

  CPPUNIT_ASSERT_EQUAL(Point(-10,42), start.getOffset());
  CPPUNIT_ASSERT_EQUAL(Point( 10,42), end.getOffset());
}

void HorizontalSegmentTest::moveUnmoveable()
{
  RelativePosition p(Point(0,0));
  Endpoint start(Point(-10, 0));
  Endpoint end(Point(10, 0));
  start.replaceAnchor(&p);
  end.replaceAnchor(&p);

  HorizontalSegment segment(&start, &end);

  segment.moveToY(42);

  CPPUNIT_ASSERT_EQUAL(Point(-10,0), start.getOffset());
  CPPUNIT_ASSERT_EQUAL(Point( 10,0), end.getOffset());
}

void HorizontalSegmentTest::moveStartAnchor()
{
  RelativePosition p(Point(-10, 0));
  Endpoint start(Point(0, 0));
  start.replaceAnchor(&p);
  Endpoint end(Point(10, 0));
  HorizontalSegment segment(&start, &end);

  p.setOffset(Point(-5, 15));
  CPPUNIT_ASSERT_EQUAL(Point(-5, 15), start.getAbsolutePosition());
  CPPUNIT_ASSERT_EQUAL(Point(10, 15), end.getAbsolutePosition());
}

void HorizontalSegmentTest::moveEndAnchor()
{
  Endpoint start(Point(-10, 0));
  RelativePosition p(Point(10, 0));
  Endpoint end(Point(0, 0));
  end.replaceAnchor(&p);
  HorizontalSegment segment(&start, &end);

  p.setOffset(Point(5, 15));
  CPPUNIT_ASSERT_EQUAL(Point(-10, 15), start.getAbsolutePosition());
}

void HorizontalSegmentTest::notifyListenerOnPositionChange()
{
  Endpoint start(Point(1, 2));
  Endpoint end(Point(3, 4));
  HorizontalSegment segment(&start, &end);

  SegObserver observer;
  segment.registerObserver(&observer);

  CPPUNIT_ASSERT_EQUAL(static_cast<const Segment *>(nullptr), observer.lastSender);
  start.setOffset(Point(10,0));
  CPPUNIT_ASSERT_EQUAL(static_cast<const Segment *>(&segment), observer.lastSender);

  segment.unregisterObserver(&observer);
}


void VerticalSegmentTest::createSegment()
{
  Endpoint start(Point(1, 2));
  Endpoint end(Point(3, 4));
  VerticalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&start), segment.getStart());
  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&end), segment.getEnd());
}

void VerticalSegmentTest::getX0()
{
  Endpoint start(Point(0, 0));
  Endpoint end(Point(0, 0));
  VerticalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(0, segment.getX());
}

void VerticalSegmentTest::getX42()
{
  Endpoint start(Point(42, 0));
  Endpoint end(Point(42, 0));

  VerticalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(42, segment.getX());
}

void VerticalSegmentTest::getX_23_42()
{
  Endpoint start(Point(23, 0));
  Endpoint end(Point(42, 0));

  VerticalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(23, segment.getX());
}

void VerticalSegmentTest::moveZero()
{
  Endpoint start(Point(0, -10));
  Endpoint end(Point(0, 10));

  VerticalSegment segment(&start, &end);

  segment.moveToX(0);

  CPPUNIT_ASSERT_EQUAL(Point(0,-10), start.getOffset());
  CPPUNIT_ASSERT_EQUAL(Point(0, 10), end.getOffset());
}

void VerticalSegmentTest::move42()
{
  Endpoint start(Point(0, -10));
  Endpoint end(Point(0, 10));

  VerticalSegment segment(&start, &end);

  segment.moveToX(42);

  CPPUNIT_ASSERT_EQUAL(Point(42,-10), start.getOffset());
  CPPUNIT_ASSERT_EQUAL(Point(42, 10), end.getOffset());
}

void VerticalSegmentTest::moveUnmoveable()
{
  RelativePosition p(Point(0,0));
  Endpoint start(Point(0, -10));
  Endpoint end(Point(0, 10));
  start.replaceAnchor(&p);
  end.replaceAnchor(&p);

  VerticalSegment segment(&start, &end);

  segment.moveToX(42);

  CPPUNIT_ASSERT_EQUAL(Point(0,-10), start.getOffset());
  CPPUNIT_ASSERT_EQUAL(Point(0, 10), end.getOffset());
}

void VerticalSegmentTest::moveStartAnchor()
{
  RelativePosition p(Point(0, -10));
  Endpoint start(Point(0, 0));
  start.replaceAnchor(&p);
  Endpoint end(Point(0, 10));
  VerticalSegment segment(&start, &end);

  p.setOffset(Point(15, -5));
  CPPUNIT_ASSERT_EQUAL(Point(15, 10), end.getAbsolutePosition());
}

void VerticalSegmentTest::moveEndAnchor()
{
  Endpoint start(Point(0, -10));
  RelativePosition p(Point(0, 10));
  Endpoint end(Point(0, 0));
  end.replaceAnchor(&p);
  VerticalSegment segment(&start, &end);

  p.setOffset(Point(15, 5));
  CPPUNIT_ASSERT_EQUAL(Point(15, -10), start.getAbsolutePosition());
}

void VerticalSegmentTest::notifyListenerOnPositionChange()
{
  Endpoint start(Point(1, 2));
  Endpoint end(Point(3, 4));
  VerticalSegment segment(&start, &end);

  SegObserver observer;
  segment.registerObserver(&observer);

  CPPUNIT_ASSERT_EQUAL(static_cast<const Segment *>(nullptr), observer.lastSender);
  start.setOffset(Point(10,1));
  CPPUNIT_ASSERT_EQUAL(static_cast<const Segment *>(&segment), observer.lastSender);

  segment.unregisterObserver(&observer);
}



void MultiSegmentTest::createSegment()
{
  MultiSegment ms(0, 0, 15, 20, 30);

  CPPUNIT_ASSERT_EQUAL( 0, ms.s0.getY());
  CPPUNIT_ASSERT_EQUAL(15, ms.s1.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.s2.getY());
}

void MultiSegmentTest::moveSegment()
{
  MultiSegment ms(0, 0, 15, 20, 30);

  CPPUNIT_ASSERT_EQUAL( 0, ms.s0.getY());
  CPPUNIT_ASSERT_EQUAL(15, ms.s1.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.s2.getY());

  ms.s1.moveToX(17);

  CPPUNIT_ASSERT_EQUAL( 0, ms.s0.getY());
  CPPUNIT_ASSERT_EQUAL(17, ms.s1.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.s2.getY());

  CPPUNIT_ASSERT_EQUAL(Point( 0, 0), ms.m0.getOffset());
  CPPUNIT_ASSERT_EQUAL(Point(17, 0), ms.m1.getOffset());
  CPPUNIT_ASSERT_EQUAL(Point(17,20), ms.m2.getOffset());
  CPPUNIT_ASSERT_EQUAL(Point(30,20), ms.m3.getOffset());
}

void MultiSegmentTest::moveIntermediatePoint()
{
  MultiSegment ms(0, 0, 15, 20, 30);

  ms.m1.setOffset(Point(13,-2));

  CPPUNIT_ASSERT_EQUAL(-2, ms.s0.getY());
  CPPUNIT_ASSERT_EQUAL(13, ms.s1.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.s2.getY());

  CPPUNIT_ASSERT_EQUAL(Point( 0,-2), ms.m0.getOffset());
  CPPUNIT_ASSERT_EQUAL(Point(13,-2), ms.m1.getOffset());
  CPPUNIT_ASSERT_EQUAL(Point(13,20), ms.m2.getOffset());
  CPPUNIT_ASSERT_EQUAL(Point(30,20), ms.m3.getOffset());
}

void MultiSegmentTest::movePortPoint()
{
  MultiSegment ms(0, 0, 15, 20, 30);

  ms.m0.setOffset(Point(2,3));

  CPPUNIT_ASSERT_EQUAL( 3, ms.s0.getY());
  CPPUNIT_ASSERT_EQUAL(15, ms.s1.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.s2.getY());

  CPPUNIT_ASSERT_EQUAL(Point( 2, 3), ms.m0.getOffset());
  CPPUNIT_ASSERT_EQUAL(Point(15, 3), ms.m1.getOffset());
  CPPUNIT_ASSERT_EQUAL(Point(15,20), ms.m2.getOffset());
  CPPUNIT_ASSERT_EQUAL(Point(30,20), ms.m3.getOffset());
}


MultiSegment::MultiSegment(PaperUnit x0, PaperUnit y0, PaperUnit xm, PaperUnit y1, PaperUnit x1) :
  m0(Point(x0, y0)),
  m1(Point(xm, y0)),
  m2(Point(xm, y1)),
  m3(Point(x1, y1)),
  s0(&m0, &m1),
  s1(&m1, &m2),
  s2(&m2, &m3)
{
}

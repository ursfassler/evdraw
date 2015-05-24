#include "SegmentTest.hpp"

class SegObserver : public Observer<Segment>
{
  public:
    void notify(const Segment *sender)
    {
      lastSender = sender;
    }

    Segment const *lastSender = nullptr;
};

void SegmentTest::createSegment()
{
  PortPoint start(Point(1, 2));
  PortPoint end(Point(3, 4));
  Segment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&start), segment.getStart());
  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&end), segment.getEnd());
}

void SegmentTest::checkFixedFixed()
{
  PortPoint start(Point(0, 0));
  PortPoint end(Point(0, 0));
  Segment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(false, segment.moveable());
}

void SegmentTest::checkFixedMovable()
{
  PortPoint start(Point(0, 0));
  IntermediatePoint end(Point(0, 0));
  Segment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(false, segment.moveable());
}

void SegmentTest::checkMovableFixed()
{
  IntermediatePoint start(Point(0, 0));
  PortPoint end(Point(0, 0));
  Segment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(false, segment.moveable());
}

void SegmentTest::checkMovableMovable()
{
  IntermediatePoint start(Point(0, 0));
  IntermediatePoint end(Point(0, 0));
  Segment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(true, segment.moveable());
}


void HorizontalSegmentTest::createSegment()
{
  PortPoint start(Point(1, 2));
  PortPoint end(Point(3, 4));
  HorizontalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&start), segment.getStart());
  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&end), segment.getEnd());
}

void HorizontalSegmentTest::getY0()
{
  IntermediatePoint start(Point(0, 0));
  IntermediatePoint end(Point(0, 0));
  HorizontalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(0, segment.getY());
}

void HorizontalSegmentTest::getY42()
{
  IntermediatePoint start(Point(0, 42));
  IntermediatePoint end(Point(0, 42));

  HorizontalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(42, segment.getY());
}

void HorizontalSegmentTest::getY_23_42()
{
  IntermediatePoint start(Point(0, 23));
  IntermediatePoint end(Point(0, 42));

  HorizontalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(23, segment.getY());
}

void HorizontalSegmentTest::moveZero()
{
  IntermediatePoint start(Point(-10, 0));
  IntermediatePoint end(Point(10, 0));

  HorizontalSegment segment(&start, &end);

  segment.moveToY(0);

  CPPUNIT_ASSERT_EQUAL(Point(-10,0), start.getPosition());
  CPPUNIT_ASSERT_EQUAL(Point( 10,0), end.getPosition());
}

void HorizontalSegmentTest::move42()
{
  IntermediatePoint start(Point(-10, 0));
  IntermediatePoint end(Point(10, 0));

  HorizontalSegment segment(&start, &end);

  segment.moveToY(42);

  CPPUNIT_ASSERT_EQUAL(Point(-10,42), start.getPosition());
  CPPUNIT_ASSERT_EQUAL(Point( 10,42), end.getPosition());
}

void HorizontalSegmentTest::notifyListenerOnPositionChange()
{
  PortPoint start(Point(1, 2));
  PortPoint end(Point(3, 4));
  HorizontalSegment segment(&start, &end);

  SegObserver observer;
  segment.registerObserver(&observer);

  CPPUNIT_ASSERT_EQUAL(static_cast<const Segment *>(nullptr), observer.lastSender);
  start.setPosition(Point(10,0));
  CPPUNIT_ASSERT_EQUAL(static_cast<const Segment *>(&segment), observer.lastSender);

  segment.unregisterObserver(&observer);
}


void VerticalSegmentTest::createSegment()
{
  PortPoint start(Point(1, 2));
  PortPoint end(Point(3, 4));
  VerticalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&start), segment.getStart());
  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&end), segment.getEnd());
}

void VerticalSegmentTest::getX0()
{
  IntermediatePoint start(Point(0, 0));
  IntermediatePoint end(Point(0, 0));
  VerticalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(0, segment.getX());
}

void VerticalSegmentTest::getX42()
{
  IntermediatePoint start(Point(42, 0));
  IntermediatePoint end(Point(42, 0));

  VerticalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(42, segment.getX());
}

void VerticalSegmentTest::getX_23_42()
{
  IntermediatePoint start(Point(23, 0));
  IntermediatePoint end(Point(42, 0));

  VerticalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(23, segment.getX());
}

void VerticalSegmentTest::moveZero()
{
  IntermediatePoint start(Point(0, -10));
  IntermediatePoint end(Point(0, 10));

  VerticalSegment segment(&start, &end);

  segment.moveToX(0);

  CPPUNIT_ASSERT_EQUAL(Point(0,-10), start.getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(0, 10), end.getPosition());
}

void VerticalSegmentTest::move42()
{
  IntermediatePoint start(Point(0, -10));
  IntermediatePoint end(Point(0, 10));

  VerticalSegment segment(&start, &end);

  segment.moveToX(42);

  CPPUNIT_ASSERT_EQUAL(Point(42,-10), start.getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(42, 10), end.getPosition());
}

void VerticalSegmentTest::notifyListenerOnPositionChange()
{
  PortPoint start(Point(1, 2));
  PortPoint end(Point(3, 4));
  VerticalSegment segment(&start, &end);

  SegObserver observer;
  segment.registerObserver(&observer);

  CPPUNIT_ASSERT_EQUAL(static_cast<const Segment *>(nullptr), observer.lastSender);
  start.setPosition(Point(10,1));
  CPPUNIT_ASSERT_EQUAL(static_cast<const Segment *>(&segment), observer.lastSender);

  segment.unregisterObserver(&observer);
}



void MultiSegmentTest::createSegment()
{
  MultiSegment ms(0, 0, 15, 20, 30);

  CPPUNIT_ASSERT_EQUAL( 0, ms.s0.getY());
  CPPUNIT_ASSERT_EQUAL(15, ms.s1.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.s2.getY());

  CPPUNIT_ASSERT_EQUAL(false, ms.s0.moveable());
  CPPUNIT_ASSERT_EQUAL( true, ms.s1.moveable());
  CPPUNIT_ASSERT_EQUAL(false, ms.s2.moveable());
}

void MultiSegmentTest::moveSegment()
{
  MultiSegment ms(0, 0, 15, 20, 30);

  CPPUNIT_ASSERT_EQUAL( 0, ms.s0.getY());
  CPPUNIT_ASSERT_EQUAL(15, ms.s1.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.s2.getY());

  CPPUNIT_ASSERT_EQUAL(false, ms.s0.moveable());
  CPPUNIT_ASSERT_EQUAL( true, ms.s1.moveable());
  CPPUNIT_ASSERT_EQUAL(false, ms.s2.moveable());

  ms.s1.moveToX(17);

  CPPUNIT_ASSERT_EQUAL( 0, ms.s0.getY());
  CPPUNIT_ASSERT_EQUAL(17, ms.s1.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.s2.getY());

  CPPUNIT_ASSERT_EQUAL(Point( 0, 0), ms.m0.getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(17, 0), ms.m1.getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(17,20), ms.m2.getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(30,20), ms.m3.getPosition());
}

void MultiSegmentTest::moveIntermediatePoint()
{
  MultiSegment ms(0, 0, 15, 20, 30);

  ms.m1.setPosition(Point(13,-2));

  CPPUNIT_ASSERT_EQUAL(-2, ms.s0.getY());
  CPPUNIT_ASSERT_EQUAL(13, ms.s1.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.s2.getY());

  CPPUNIT_ASSERT_EQUAL(Point( 0,-2), ms.m0.getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(13,-2), ms.m1.getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(13,20), ms.m2.getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(30,20), ms.m3.getPosition());
}

void MultiSegmentTest::movePortPoint()
{
  MultiSegment ms(0, 0, 15, 20, 30);

  ms.m0.setPosition(Point(2,3));

  CPPUNIT_ASSERT_EQUAL( 3, ms.s0.getY());
  CPPUNIT_ASSERT_EQUAL(15, ms.s1.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.s2.getY());

  CPPUNIT_ASSERT_EQUAL(Point( 2, 3), ms.m0.getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(15, 3), ms.m1.getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(15,20), ms.m2.getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(30,20), ms.m3.getPosition());
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

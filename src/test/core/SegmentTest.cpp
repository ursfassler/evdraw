#include "SegmentTest.hpp"

class SegListener : public SegmentListener
{
  public:
    void positionChange(Segment *sender)
    {
      lastSender = sender;
    }

    Segment *lastSender = nullptr;
};

void SegmentTest::createSegment()
{
  PortPoint start(1, 2);
  PortPoint end(3, 4);
  Segment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&start), segment.getStart());
  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&end), segment.getEnd());
}

void SegmentTest::checkFixedFixed()
{
  PortPoint start(0, 0);
  PortPoint end(0, 0);
  Segment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(false, segment.moveable());
}

void SegmentTest::checkFixedMovable()
{
  PortPoint start(0, 0);
  IntermediatePoint end(0, 0);
  Segment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(false, segment.moveable());
}

void SegmentTest::checkMovableFixed()
{
  IntermediatePoint start(0, 0);
  PortPoint end(0, 0);
  Segment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(false, segment.moveable());
}

void SegmentTest::checkMovableMovable()
{
  IntermediatePoint start(0, 0);
  IntermediatePoint end(0, 0);
  Segment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(true, segment.moveable());
}

void SegmentTest::addRemoveListener()
{
  PortPoint start(1, 2);
  PortPoint end(3, 4);
  Segment segment(&start, &end);

  SegListener listener;

  CPPUNIT_ASSERT_EQUAL(false, segment.hasListener());
  segment.addListener(&listener);
  CPPUNIT_ASSERT_EQUAL(true, segment.hasListener());
  segment.removeListener(&listener);
  CPPUNIT_ASSERT_EQUAL(false, segment.hasListener());
}


void HorizontalSegmentTest::createSegment()
{
  PortPoint start(1, 2);
  PortPoint end(3, 4);
  HorizontalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&start), segment.getStart());
  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&end), segment.getEnd());
}

void HorizontalSegmentTest::getY0()
{
  IntermediatePoint start(0, 0);
  IntermediatePoint end(0, 0);
  HorizontalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(0, segment.getY());
}

void HorizontalSegmentTest::getY42()
{
  IntermediatePoint start(0, 42);
  IntermediatePoint end(0, 42);

  HorizontalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(42, segment.getY());
}

void HorizontalSegmentTest::getY_23_42()
{
  IntermediatePoint start(0, 23);
  IntermediatePoint end(0, 42);

  HorizontalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(23, segment.getY());
}

void HorizontalSegmentTest::moveZero()
{
  IntermediatePoint start(-10, 0);
  IntermediatePoint end(10, 0);

  HorizontalSegment segment(&start, &end);

  segment.moveToY(0);

  CPPUNIT_ASSERT_EQUAL(  0, start.getY());
  CPPUNIT_ASSERT_EQUAL(-10, start.getX());
  CPPUNIT_ASSERT_EQUAL(  0, end.getY());
  CPPUNIT_ASSERT_EQUAL( 10, end.getX());
}

void HorizontalSegmentTest::move42()
{
  IntermediatePoint start(-10, 0);
  IntermediatePoint end(10, 0);

  HorizontalSegment segment(&start, &end);

  segment.moveToY(42);

  CPPUNIT_ASSERT_EQUAL( 42, start.getY());
  CPPUNIT_ASSERT_EQUAL(-10, start.getX());
  CPPUNIT_ASSERT_EQUAL( 42, end.getY());
  CPPUNIT_ASSERT_EQUAL( 10, end.getX());
}

void HorizontalSegmentTest::notifyListenerOnY()
{
  PortPoint start(1, 2);
  PortPoint end(3, 4);
  HorizontalSegment segment(&start, &end);

  SegListener listener;
  segment.addListener(&listener);

  CPPUNIT_ASSERT_EQUAL(static_cast<Segment *>(nullptr), listener.lastSender);
  start.setY(10);
  CPPUNIT_ASSERT_EQUAL(static_cast<Segment *>(&segment), listener.lastSender);
}

void HorizontalSegmentTest::notifyListenerOnX()
{
  PortPoint start(1, 2);
  PortPoint end(3, 4);
  HorizontalSegment segment(&start, &end);

  SegListener listener;
  segment.addListener(&listener);

  CPPUNIT_ASSERT_EQUAL(static_cast<Segment *>(nullptr), listener.lastSender);
  start.setX(10);
  CPPUNIT_ASSERT_EQUAL(static_cast<Segment *>(&segment), listener.lastSender);
}


void VerticalSegmentTest::createSegment()
{
  PortPoint start(1, 2);
  PortPoint end(3, 4);
  VerticalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&start), segment.getStart());
  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&end), segment.getEnd());
}

void VerticalSegmentTest::getX0()
{
  IntermediatePoint start(0, 0);
  IntermediatePoint end(0, 0);
  VerticalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(0, segment.getX());
}

void VerticalSegmentTest::getX42()
{
  IntermediatePoint start(42, 0);
  IntermediatePoint end(42, 0);

  VerticalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(42, segment.getX());
}

void VerticalSegmentTest::getX_23_42()
{
  IntermediatePoint start(23, 0);
  IntermediatePoint end(42, 0);

  VerticalSegment segment(&start, &end);

  CPPUNIT_ASSERT_EQUAL(23, segment.getX());
}

void VerticalSegmentTest::moveZero()
{
  IntermediatePoint start(0, -10);
  IntermediatePoint end(0, 10);

  VerticalSegment segment(&start, &end);

  segment.moveToX(0);

  CPPUNIT_ASSERT_EQUAL(-10, start.getY());
  CPPUNIT_ASSERT_EQUAL(  0, start.getX());
  CPPUNIT_ASSERT_EQUAL( 10, end.getY());
  CPPUNIT_ASSERT_EQUAL(  0, end.getX());
}

void VerticalSegmentTest::move42()
{
  IntermediatePoint start(0, -10);
  IntermediatePoint end(0, 10);

  VerticalSegment segment(&start, &end);

  segment.moveToX(42);

  CPPUNIT_ASSERT_EQUAL(-10, start.getY());
  CPPUNIT_ASSERT_EQUAL( 42, start.getX());
  CPPUNIT_ASSERT_EQUAL( 10, end.getY());
  CPPUNIT_ASSERT_EQUAL( 42, end.getX());
}

void VerticalSegmentTest::notifyListenerOnX()
{
  PortPoint start(1, 2);
  PortPoint end(3, 4);
  VerticalSegment segment(&start, &end);

  SegListener listener;
  segment.addListener(&listener);

  CPPUNIT_ASSERT_EQUAL(static_cast<Segment *>(nullptr), listener.lastSender);
  start.setX(10);
  CPPUNIT_ASSERT_EQUAL(static_cast<Segment *>(&segment), listener.lastSender);
}

void VerticalSegmentTest::notifyListenerOnY()
{
  PortPoint start(1, 2);
  PortPoint end(3, 4);
  VerticalSegment segment(&start, &end);

  SegListener listener;
  segment.addListener(&listener);

  CPPUNIT_ASSERT_EQUAL(static_cast<Segment *>(nullptr), listener.lastSender);
  start.setY(10);
  CPPUNIT_ASSERT_EQUAL(static_cast<Segment *>(&segment), listener.lastSender);
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

  CPPUNIT_ASSERT_EQUAL( 0, ms.m0.getX());
  CPPUNIT_ASSERT_EQUAL( 0, ms.m0.getY());
  CPPUNIT_ASSERT_EQUAL(17, ms.m1.getX());
  CPPUNIT_ASSERT_EQUAL( 0, ms.m1.getY());
  CPPUNIT_ASSERT_EQUAL(17, ms.m2.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.m2.getY());
  CPPUNIT_ASSERT_EQUAL(30, ms.m3.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.m3.getY());
}

void MultiSegmentTest::moveIntermediatePoint()
{
  MultiSegment ms(0, 0, 15, 20, 30);

  ms.m1.setX(13);

  CPPUNIT_ASSERT_EQUAL( 0, ms.s0.getY());
  CPPUNIT_ASSERT_EQUAL(13, ms.s1.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.s2.getY());

  CPPUNIT_ASSERT_EQUAL( 0, ms.m0.getX());
  CPPUNIT_ASSERT_EQUAL( 0, ms.m0.getY());
  CPPUNIT_ASSERT_EQUAL(13, ms.m1.getX());
  CPPUNIT_ASSERT_EQUAL( 0, ms.m1.getY());
  CPPUNIT_ASSERT_EQUAL(13, ms.m2.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.m2.getY());
  CPPUNIT_ASSERT_EQUAL(30, ms.m3.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.m3.getY());

  ms.m1.setY(-2);

  CPPUNIT_ASSERT_EQUAL(-2, ms.s0.getY());
  CPPUNIT_ASSERT_EQUAL(13, ms.s1.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.s2.getY());

  CPPUNIT_ASSERT_EQUAL( 0, ms.m0.getX());
  CPPUNIT_ASSERT_EQUAL(-2, ms.m0.getY());
  CPPUNIT_ASSERT_EQUAL(13, ms.m1.getX());
  CPPUNIT_ASSERT_EQUAL(-2, ms.m1.getY());
  CPPUNIT_ASSERT_EQUAL(13, ms.m2.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.m2.getY());
  CPPUNIT_ASSERT_EQUAL(30, ms.m3.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.m3.getY());
}

void MultiSegmentTest::movePortPoint()
{
  MultiSegment ms(0, 0, 15, 20, 30);

  ms.m0.setX(2);
  ms.m0.setY(3);

  CPPUNIT_ASSERT_EQUAL( 3, ms.s0.getY());
  CPPUNIT_ASSERT_EQUAL(15, ms.s1.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.s2.getY());

  CPPUNIT_ASSERT_EQUAL( 2, ms.m0.getX());
  CPPUNIT_ASSERT_EQUAL( 3, ms.m0.getY());
  CPPUNIT_ASSERT_EQUAL(15, ms.m1.getX());
  CPPUNIT_ASSERT_EQUAL( 3, ms.m1.getY());
  CPPUNIT_ASSERT_EQUAL(15, ms.m2.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.m2.getY());
  CPPUNIT_ASSERT_EQUAL(30, ms.m3.getX());
  CPPUNIT_ASSERT_EQUAL(20, ms.m3.getY());
}


MultiSegment::MultiSegment(PaperUnit x0, PaperUnit y0, PaperUnit xm, PaperUnit y1, PaperUnit x1) :
  m0(x0, y0),
  m1(xm, y0),
  m2(xm, y1),
  m3(x1, y1),
  s0(&m0, &m1),
  s1(&m1, &m2),
  s2(&m2, &m3)
{
}

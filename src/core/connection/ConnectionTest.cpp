#include "ConnectionTest.hpp"

#include "Connection.hpp"
#include "ConnectionFactory.hpp"
#include "Segment.hpp"

#include "../util/contract.hpp"

void ConnectionTest::create()
{
  Connection connection;
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getIntermediatePoints().size());
  CPPUNIT_ASSERT_EQUAL(Point(0,0), connection.getStart().getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(0,0), connection.getEnd().getPosition());
}

void ConnectionTest::addHorizontalSegment()
{
  Connection connection;
  HorizontalSegment *segment = new HorizontalSegment(&connection.getStart(), &connection.getEnd());

  connection.addHorizontalSegment(segment);
  CPPUNIT_ASSERT_EQUAL(segment, connection.getHorizontalSegment()[0]);

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::addVerticalSegment()
{
  Connection connection;
  VerticalSegment *segment = new VerticalSegment(&connection.getStart(), &connection.getEnd());

  connection.addVerticalSegment(segment);
  CPPUNIT_ASSERT_EQUAL(segment, connection.getVerticalSegment()[0]);

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::addIntermediatePoint()
{
  Connection connection;
  IntermediatePoint *ip = new IntermediatePoint(Point(0,0));

  connection.addIntermediatePoint(ip);
  CPPUNIT_ASSERT_EQUAL(ip, connection.getIntermediatePoints()[0]);

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::interactveCreateConnection()
{
  Connection connection;

  IntermediatePoint *ip1 = new IntermediatePoint(Point(0,0));
  HorizontalSegment *seg1 = new HorizontalSegment(&connection.getStart(), ip1);
  VerticalSegment *seg2 = new VerticalSegment(ip1, &connection.getEnd());

  connection.addIntermediatePoint(ip1);
  connection.addHorizontalSegment(seg1);
  connection.addVerticalSegment(seg2);

  connection.getEnd().setPosition(Point(20,30));

  IntermediatePoint *ip2 = new IntermediatePoint(Point(21,31));
  HorizontalSegment *seg3 = new HorizontalSegment(ip2, &connection.getEnd());
  seg2->setEnd(ip2);
  connection.addIntermediatePoint(ip2);
  connection.addHorizontalSegment(seg3);

  connection.getEnd().setPosition(Point(50,60));

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection.getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection.getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(2), connection.getIntermediatePoints().size());
  CPPUNIT_ASSERT_EQUAL(Point(21,0), connection.getIntermediatePoints()[0]->getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(21,60), connection.getIntermediatePoints()[1]->getPosition());

  ConnectionFactory::cleanup(connection);
}



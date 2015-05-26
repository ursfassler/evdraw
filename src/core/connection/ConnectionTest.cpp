#include "ConnectionTest.hpp"

#include "Connection.hpp"
#include "ConnectionFactory.hpp"
#include "Segment.hpp"

#include "../util/contract.hpp"

void ConnectionTest::createFinished()
{
  Connection connection(Connection::Mode::Finished);
  CPPUNIT_ASSERT_EQUAL(Connection::Mode::Finished, connection.getMode());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getIntermediatePoints().size());
  CPPUNIT_ASSERT_EQUAL(Point(0,0), connection.getStart().getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(0,0), connection.getEnd().getPosition());
}

void ConnectionTest::createBuild()
{
  Connection connection(Connection::Mode::Build);
  CPPUNIT_ASSERT_EQUAL(Connection::Mode::Build, connection.getMode());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(0), connection.getIntermediatePoints().size());
  CPPUNIT_ASSERT_EQUAL(Point(0,0), connection.getStart().getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(0,0), connection.getEnd().getPosition());
}

void ConnectionTest::createBuildToEnd()
{
  Connection connection(Connection::Mode::BuildToEnd);

  CPPUNIT_ASSERT_EQUAL(Connection::Mode::BuildToEnd, connection.getMode());

  CPPUNIT_ASSERT_EQUAL(size_t(1), connection.getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection.getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection.getIntermediatePoints().size());
  CPPUNIT_ASSERT_EQUAL(Point(0,0), connection.getStart().getPosition());
  CPPUNIT_ASSERT_EQUAL(Point(0,0), connection.getEnd().getPosition());

  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&connection.getStart()), connection.getHorizontalSegment()[0]->getStart());
  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(connection.getIntermediatePoints()[0]), connection.getHorizontalSegment()[0]->getEnd());
  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(connection.getIntermediatePoints()[0]), connection.getVerticalSegment()[0]->getStart());
  CPPUNIT_ASSERT_EQUAL(static_cast<Endpoint*>(&connection.getEnd()), connection.getVerticalSegment()[0]->getEnd());

  ConnectionFactory::cleanup(connection);
}


void ConnectionTest::addHorizontalSegment()
{
  Connection connection(Connection::Mode::Build);
  HorizontalSegment *segment = new HorizontalSegment(&connection.getStart(), &connection.getEnd());

  connection.addHorizontalSegment(segment);
  CPPUNIT_ASSERT_EQUAL(segment, connection.getHorizontalSegment()[0]);

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::addVerticalSegment()
{
  Connection connection(Connection::Mode::Build);
  VerticalSegment *segment = new VerticalSegment(&connection.getStart(), &connection.getEnd());

  connection.addVerticalSegment(segment);
  CPPUNIT_ASSERT_EQUAL(segment, connection.getVerticalSegment()[0]);

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::addIntermediatePoint()
{
  Connection connection(Connection::Mode::Build);
  IntermediatePoint *ip = new IntermediatePoint(Point(0,0));

  connection.addIntermediatePoint(ip);
  CPPUNIT_ASSERT_EQUAL(ip, connection.getIntermediatePoints()[0]);

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::buildToEndAndAddSegment()
{
  Connection connection(Connection::Mode::BuildToEnd);

  CPPUNIT_ASSERT_EQUAL(size_t(1), connection.getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection.getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection.getIntermediatePoints().size());

  connection.addSegment();

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection.getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection.getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(2), connection.getIntermediatePoints().size());

  connection.addSegment();

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection.getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(2), connection.getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(3), connection.getIntermediatePoints().size());

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::buildToEndAndFinish()
{
  Connection connection(Connection::Mode::BuildToEnd);
  connection.buildFinished();

  CPPUNIT_ASSERT_EQUAL(Connection::Mode::Finished, connection.getMode());

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection.getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection.getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(2), connection.getIntermediatePoints().size());

  ConnectionFactory::cleanup(connection);
}

void ConnectionTest::buildToEndAddAndFinish()
{
  Connection connection(Connection::Mode::BuildToEnd);
  connection.addSegment();
  connection.buildFinished();

  CPPUNIT_ASSERT_EQUAL(Connection::Mode::Finished, connection.getMode());

  CPPUNIT_ASSERT_EQUAL(size_t(2), connection.getHorizontalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(1), connection.getVerticalSegment().size());
  CPPUNIT_ASSERT_EQUAL(size_t(2), connection.getIntermediatePoints().size());

  ConnectionFactory::cleanup(connection);
}


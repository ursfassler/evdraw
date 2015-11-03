// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "EndpointTest.hpp"


void EndpointTest::has_position()
{
  const Endpoint pp(Point(1, 2));

  CPPUNIT_ASSERT_EQUAL(Point(1,2), pp.getPosition().getAbsolutePosition());
}

void EndpointTest::is_movable_when_not_have_anchor()
{
  Endpoint pp(Point(1, 2));
  CPPUNIT_ASSERT(pp.freeMovable());
}

void EndpointTest::is_not_movable_when_have_anchor()
{
  RelativePosition p(Point(0,0));
  Endpoint pp(Point(1, 2));
  pp.getPosition().replaceAnchor(&p);
  CPPUNIT_ASSERT(!pp.freeMovable());
}

class EpObserver : public PositionObserver
{
  public:
    void absolutePositionChanged(const RelativePosition *sender)
    {
      lastSender = sender;
    }

    void offsetChanged(const RelativePosition *)
    {
    }

    RelativePosition const *lastSender = nullptr;
};

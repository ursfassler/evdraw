// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef SEGMENT_HPP
#define SEGMENT_HPP

#include "../util/Observer.hpp"
#include "Endpoint.hpp"

class Segment;

class SegmentObserver
{
  public:
    virtual ~SegmentObserver(){}
    virtual void positionChanged(const Segment *sender) = 0;
};

class Segment : public ObserverCollection<SegmentObserver>, public PositionObserver
{
  public:
    Segment(Endpoint *aStart, Endpoint *aEnd);
    Segment(const Segment &copy) = delete;
    virtual ~Segment();
    Segment & operator=(const Segment &L) = delete;

    Endpoint *getStart() const;
    void setStart(Endpoint *point);
    Endpoint *getEnd() const;
    void setEnd(Endpoint *point);

    bool moveable() const;

    void absolutePositionChanged(const RelativePosition *sender);
    void offsetChanged(const RelativePosition *sender);

  protected:
    Endpoint  *start;
    Endpoint  *end;
};

class HorizontalSegment : public Segment
{
  public:
    HorizontalSegment(Endpoint *aStart, Endpoint *aEnd);

    PaperUnit getY() const;
    void moveToY(PaperUnit value);

    void absolutePositionChanged(const RelativePosition *sender);
};

class VerticalSegment : public Segment
{
  public:
    VerticalSegment(Endpoint *aStart, Endpoint *aEnd);

    PaperUnit getX() const;
    void moveToX(PaperUnit value);

    void absolutePositionChanged(const RelativePosition *sender);
};

#endif // SEGMENT_HPP

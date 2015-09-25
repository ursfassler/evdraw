// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef POSITION_HPP
#define POSITION_HPP

#include "Base.hpp"
#include "../Point.hpp"
#include "../util/Observer.hpp"

class RelativePosition;

class PositionObserver
{
  public:
    virtual ~PositionObserver() {}
    virtual void absolutePositionChanged(const RelativePosition *sender) = 0;
    virtual void offsetChanged(const RelativePosition *sender) = 0;
};

class Position : public ObserverCollection<PositionObserver>
{
  public:
    Position();
    virtual ~Position();
    virtual Point getAbsolutePosition() const = 0;

};

class ZeroPosition : public Position
{
  public:
    Point getAbsolutePosition() const;

    static ZeroPosition *singleton();

};

class RelativePosition :
    public Position,
    public PositionObserver
{
  public:
    RelativePosition(const Point &offset);
    RelativePosition(RelativePosition *anchor, const Point &offset);
    virtual ~RelativePosition();

    RelativePosition(const RelativePosition &) = delete;
    RelativePosition operator=(const RelativePosition &) = delete;

    void replaceAnchor(Position *newAnchor);
    void removeAnchor();
    Position *getAnchor() const;
    bool hasAnchor() const;

    virtual const Point &getOffset() const;
    virtual void setOffset(const Point &value);
    virtual Point getAbsolutePosition() const;
    virtual void setAbsolutePosition(const Point &value);

    virtual void absolutePositionChanged(const RelativePosition *sender);
    virtual void offsetChanged(const RelativePosition *sender);

  private:
    Position *anchor;
    Point offset;
};

#endif

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

//TODO move observer aout of interface
class IPosition :
    public ObserverCollection<PositionObserver>
{
  public:
    virtual ~IPosition() = default;
    virtual Point getAbsolutePosition() const = 0;

};

class ZeroPosition final :
    public IPosition
{
  public:
    Point getAbsolutePosition() const override final;

    static ZeroPosition *singleton();

};

class RelativePosition final :
    public IPosition,
    private PositionObserver
{
  public:
    RelativePosition(const Point &offset);
    RelativePosition(RelativePosition *anchor, const Point &offset);
    virtual ~RelativePosition();

    RelativePosition(const RelativePosition &) = delete;
    RelativePosition operator=(const RelativePosition &) = delete;

    void replaceAnchor(IPosition *newAnchor);
    void removeAnchor();
    IPosition *getAnchor() const;
    bool hasAnchor() const;

    const Point &getOffset() const;
    void setOffset(const Point &value);
    Point getAbsolutePosition() const override final;
    void setAbsolutePosition(const Point &value);

  private:
    IPosition *anchor;
    Point offset;

    void absolutePositionChanged(const RelativePosition *sender) override final;
    void offsetChanged(const RelativePosition *sender) override final;
};

#endif

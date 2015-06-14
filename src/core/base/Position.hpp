#ifndef POSITION_HPP
#define POSITION_HPP

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
};

class RelativePosition : public Position, public PositionObserver
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
    ZeroPosition zeroAnchor;
    Position *anchor;
    Point offset;
};

#endif

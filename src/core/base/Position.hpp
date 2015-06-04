#ifndef POSITION_HPP
#define POSITION_HPP

#include "../Point.hpp"
#include "../util/Observer.hpp"

class RelativePosition;

class PositionObserver
{
  public:
    virtual ~PositionObserver()
    {
    }
    virtual void notify(const RelativePosition *sender) = 0;
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
    bool operator=(const RelativePosition &) = delete;

    void replaceAnchor(Position *newAnchor);
    void removeAnchor();
    Position *getAnchor() const;
    bool hasAnchor() const;

    virtual const Point &getOffset() const;
    virtual void setOffset(const Point &value);
    virtual Point getAbsolutePosition() const;

  protected:
    virtual void notify(const RelativePosition *subject);
    ZeroPosition zeroAnchor;

  private:
    Position *anchor;
    Point offset;
};

#endif

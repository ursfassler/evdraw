#ifndef BASE_HPP
#define BASE_HPP

#include "../Point.hpp"
#include "../util/Observer.hpp"

class Positionable;

class PositionableObserver
{
  public:
    virtual ~PositionableObserver()
    {
    }
    virtual void notify(const Positionable *sender) = 0;
};

class Positionable : public ObserverCollection<PositionableObserver>, public PositionableObserver
{
  public:
    Positionable(Positionable *anchor, const Point &offset);
    virtual ~Positionable();

    Positionable(const Positionable &) = delete;
    bool operator=(const Positionable &) = delete;

    void setAnchor(Positionable *value);
    Positionable *getAnchor() const;

    virtual const Point &getOffset() const;
    virtual void setOffset(const Point &value);
    virtual Point getAbsolutePosition() const;

  protected:
    virtual void notify(const Positionable *subject);

  private:
    Positionable  *anchor;
    Point offset;
};

#endif // BASE_HPP

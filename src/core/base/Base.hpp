#ifndef BASE_HPP
#define BASE_HPP

#include "../Point.hpp"
#include "../util/Observer.hpp"

class Base;

class BaseObserver
{
  public:
    virtual ~BaseObserver()
    {
    }
    virtual void notify(const Base *sender) = 0;
};

class Base : public ObserverCollection<BaseObserver>, public BaseObserver
{
  public:
    Base(Base *parent, const Point &offset);
    virtual ~Base();

    Base(const Base &) = delete;
    bool operator=(const Base &) = delete;

    virtual const Point &getOffset() const;
    virtual void setOffset(const Point &value);
    virtual Point getAbsolutePosition() const;

  protected:
    virtual void notify(const Base *subject);

  private:
    Base  * const parent;
    Point offset;
};

#endif // BASE_HPP

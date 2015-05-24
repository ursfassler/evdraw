#ifndef BASE_HPP
#define BASE_HPP

#include "../Point.hpp"
#include "../util/Observer.hpp"

class Base : public ObserverCollection<Base>, protected Observer<Base>
{
  public:
    Base(Base *parent, const Point &offset);
    virtual ~Base();

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

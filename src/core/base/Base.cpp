#include "Base.hpp"

Base::Base(Base *aParent, const Point &aOffset) :
  ObserverCollection(),
  parent(aParent),
  offset(aOffset)
{
  if (parent != nullptr) {
    parent->registerObserver(this);
  }
}

Base::~Base()
{
  if (parent != nullptr) {
    parent->unregisterObserver(this);
  }
}

const Point &Base::getOffset() const
{
  return offset;
}

void Base::setOffset(const Point &value)
{
  if (offset != value) {
    offset = value;
    notify(this);
  }
}

Point Base::getAbsolutePosition() const
{
  const Point parentPos = parent != nullptr ? parent->getAbsolutePosition() : Point(0,0);
  return offset + parentPos;
}

void Base::notify(const Base *)
{
  ObserverCollection<BaseObserver>::notify(&BaseObserver::notify, static_cast<const Base*>(this));
}

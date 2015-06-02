#include "Base.hpp"

Positionable::Positionable(Positionable *aAnchor, const Point &aOffset) :
  ObserverCollection(),
  anchor(aAnchor),
  offset(aOffset)
{
  if (anchor != nullptr) {
    anchor->registerObserver(this);
  }
}

Positionable::~Positionable()
{
  if (anchor != nullptr) {
    anchor->unregisterObserver(this);
  }
}

void Positionable::setAnchor(Positionable *value)
{
  if (anchor != nullptr) {
    anchor->unregisterObserver(this);
  }
  anchor = value;
  if (anchor != nullptr) {
    anchor->registerObserver(this);
  }
}

Positionable *Positionable::getAnchor() const
{
  return anchor;
}

const Point &Positionable::getOffset() const
{
  return offset;
}

void Positionable::setOffset(const Point &value)
{
  if (offset != value) {
    offset = value;
    notify(this);
  }
}

Point Positionable::getAbsolutePosition() const
{
  const Point parentPos = anchor != nullptr ? anchor->getAbsolutePosition() : Point(0,0);
  return offset + parentPos;
}

void Positionable::notify(const Positionable *)
{
  ObserverCollection<PositionableObserver>::notify(&PositionableObserver::notify, static_cast<const Positionable*>(this));
}

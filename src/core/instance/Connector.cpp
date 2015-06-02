#include "Connector.hpp"

#include "../component/InstanceAppearance.hpp"

Connector::Connector(Positionable *parent, const Point &aOffset) :
  Positionable(parent, aOffset),
  points()
{
}

void Connector::addPoint(Positionable *point)
{
  points.push_back(point);
  point->setAnchor(this);
  updateConnectionPosition();
}

const std::vector<Positionable *> &Connector::getPoints() const
{
  return points;
}

void Connector::setOffset(const Point &value)
{
  //TODO necessary?
  if (getOffset() != value) {
    Positionable::setOffset(value);
    updateConnectionPosition();
  }
}

void Connector::notify(const Positionable *subject)
{
  Positionable::notify(subject);
  updateConnectionPosition();
}

void Connector::updateConnectionPosition() const
{
  for (size_t i = 0; i < points.size(); i++) {
    Point offset = calcLocalConnectorOffset(i);
    points[i]->setOffset(offset);
  }
}

Point Connector::calcLocalConnectorOffset(size_t idx) const
{
  const PaperUnit height = InstanceAppearance::portDimension().y;
  const PaperUnit offset = (idx+1) * height / (points.size()+1);
  const PaperUnit pos = offset - height / 2;
  return Point(0, pos);
}


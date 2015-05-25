#include "Connector.hpp"

#include "../component/InstanceAppearance.hpp"

Connector::Connector(Base *parent, const Point &aOffset) :
  Base(parent, aOffset),
  points()
{
}

void Connector::addPoint(PortPoint *point)
{
  points.push_back(point);
  updateConnectionPosition();
}

const std::vector<PortPoint *> &Connector::getPoints() const
{
  return points;
}

void Connector::setOffset(const Point &value)
{
  //TODO necessary?
  if (getOffset() != value) {
    Base::setOffset(value);
    updateConnectionPosition();
  }
}

void Connector::notify(const Base *subject)
{
  Base::notify(subject);
  updateConnectionPosition();
}

void Connector::updateConnectionPosition() const
{
  for (size_t i = 0; i < points.size(); i++) {
    Point offset = calcLocalConnectorOffset(i);
    PortPoint *pp = points[i];
    pp->setPosition(getAbsolutePosition() + offset);
  }
}

Point Connector::calcLocalConnectorOffset(size_t idx) const
{
  const PaperUnit height = InstanceAppearance::portDimension().y;
  const PaperUnit offset = (idx+1) * height / (points.size()+1);
  const PaperUnit pos = offset - height / 2;
  return Point(0, pos);
}


#include "Connector.hpp"

#include "../component/InstanceAppearance.hpp"

Connector::Connector(const Point &aOffset) :
  offset(aOffset),
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

const Point &Connector::getOffset() const
{
  return offset;
}

void Connector::setOffset(const Point &value)
{
  if (offset != value) {
    offset = value;
    updateConnectionPosition();
  }
}



void Connector::updateConnectionPosition() const
{
  for (size_t i = 0; i < points.size(); i++) {
    PaperUnit y = calcLocalConnectorY(i);
    PortPoint *pp = points[i];
    pp->setPosition(Point(offset.x, offset.y + y));
  }
}

PaperUnit Connector::calcLocalConnectorY(size_t idx) const
{
  const PaperUnit height = InstanceAppearance::portHeight();
  const PaperUnit offset = (idx+1) * height / (points.size()+1);
  const PaperUnit pos = offset - height / 2;
  return pos;
}


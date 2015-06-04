#include "Connector.hpp"

#include "../component/InstanceAppearance.hpp"

Connector::Connector(const Point &aOffset) :
  RelativePosition(aOffset),
  points()
{
}

void Connector::addPoint(RelativePosition *point)
{
  points.push_back(point);
  point->replaceAnchor(this);
  updateConnectionPosition();
}

const std::vector<RelativePosition *> &Connector::getPoints() const
{
  return points;
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


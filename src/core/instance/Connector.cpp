// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "Connector.hpp"

#include "../component/InstanceAppearance.hpp"

Connector::Connector(const Point &aOffset) :
  RelativePosition(aOffset),
  points()
{
}

Connector::~Connector()
{
  precondition(points.empty());
}

void Connector::addPoint(RelativePosition *point)
{
  points.push_back(point);
  point->replaceAnchor(this);
  updateConnectionPosition();
}

void Connector::removePoint(RelativePosition *point)
{
  const auto idx = std::find(points.begin(), points.end(), point);
  precondition(idx != points.end());

  points.erase(idx);
  point->removeAnchor();
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


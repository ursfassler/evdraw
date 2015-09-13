// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef CONNECTOR_HPP
#define CONNECTOR_HPP

#include "../base/Position.hpp"

#include "../types.hpp"

class Connector final : public RelativePosition
{
  public:
    Connector(const Point &offset);
    ~Connector();

    void addPoint(RelativePosition *point);
    void removePoint(RelativePosition *point);
    const std::vector<RelativePosition *> &getPoints() const;

  private:
    std::vector<RelativePosition*> points;

    void updateConnectionPosition() const;
    Point calcLocalConnectorOffset(size_t idx) const;
};

#endif // CONNECTOR_HPP

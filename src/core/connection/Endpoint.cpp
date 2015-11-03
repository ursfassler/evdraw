// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "Endpoint.hpp"

Endpoint::Endpoint(const Point &aPosition) :
  position{aPosition}
{
}

bool Endpoint::freeMovable() const
{
  return !position.hasAnchor();
}

RelativePosition &Endpoint::getPosition()
{
  return position;
}

const RelativePosition &Endpoint::getPosition() const
{
  return position;
}

std::ostream &operator<<(std::ostream &stream, const Endpoint &endpoint)
{
  stream << endpoint.getPosition().getAbsolutePosition();
  return stream;
}


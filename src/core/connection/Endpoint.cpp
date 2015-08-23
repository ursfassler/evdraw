// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "Endpoint.hpp"

Endpoint::Endpoint(const Point &aPosition) :
  RelativePosition(aPosition)
{
}

bool Endpoint::freeMovable() const
{
  return !hasAnchor();
}

std::ostream &operator<<(std::ostream &stream, const Endpoint &endpoint)
{
  stream << endpoint.getAbsolutePosition();
  return stream;
}


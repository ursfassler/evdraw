// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "AlwaysSatisfiedSpecification.hpp"

AlwaysSatisfiedSpecification::AlwaysSatisfiedSpecification()
{
}

bool AlwaysSatisfiedSpecification::isSatisfiedBy(const Base *) const
{
  return true;
}


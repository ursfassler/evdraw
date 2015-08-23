// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "OrSpecification.hpp"

OrSpecification::OrSpecification() :
  specs()
{
}

OrSpecification::~OrSpecification()
{
  for (const Specification *itr : specs)
  {
    delete itr;
  }
  specs.clear();
}

bool OrSpecification::isSatisfiedBy(const Base *candidate) const
{
  for (const Specification *itr : specs)
  {
    if (itr->isSatisfiedBy(candidate))
    {
      return true;
    }
  }
  return false;
}

void OrSpecification::add(const Specification *spec)
{
  specs.push_back(spec);
}


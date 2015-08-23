// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "DefaultSpecification.hpp"

#include <core/specification/OrSpecification.hpp>

Specification *DefaultSpecification::or_(const Specification *right) const
{
  OrSpecification *spec = new OrSpecification();
  spec->add(this);
  spec->add(right);
  return spec;
}

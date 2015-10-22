// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "NullImplementation.hpp"

#include "../visitor/ConstVisitor.hpp"

NullImplementation::NullImplementation()
{
}

ImplementationType NullImplementation::getType() const
{
  return ImplementationType::Empty;
}

void NullImplementation::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

void NullImplementation::accept(ConstVisitor &visitor) const
{
  visitor.visit(*this);
}

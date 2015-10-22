// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ImplementationMock.hpp"

ImplementationMock::ImplementationMock(bool *aDeleted) :
  deleted(aDeleted)
{
}

ImplementationMock::~ImplementationMock()
{
  if (deleted != nullptr) {
    *deleted = true;
  }
}

ImplementationType ImplementationMock::getType() const
{
  return type;
}

void ImplementationMock::accept(Visitor &)
{
}

void ImplementationMock::accept(ConstVisitor &) const
{
}


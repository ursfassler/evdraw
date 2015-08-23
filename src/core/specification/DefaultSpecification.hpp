// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef DEFAULTSPECIFICATION_HPP
#define DEFAULTSPECIFICATION_HPP

#include "Specification.hpp"

class DefaultSpecification : public Specification
{
  public:
    Specification *or_(const Specification *right) const;

};

#endif // DEFAULTSPECIFICATION_HPP

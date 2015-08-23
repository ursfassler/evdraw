// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef SPECIFICATION_HPP
#define SPECIFICATION_HPP

#include "../base/Base.hpp"

class Specification
{
  public:
    virtual ~Specification(){}

    virtual bool isSatisfiedBy(const Base *candidate) const = 0;
    virtual Specification *or_(const Specification *right) const = 0;
};

#endif // SPECIFICATION_HPP

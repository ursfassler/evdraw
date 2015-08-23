// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef ABSTRACTIMPLEMENTATION_HPP
#define ABSTRACTIMPLEMENTATION_HPP

#include "../visitor/VisitorClient.hpp"

class AbstractImplementation : public VisitorClient
{
  public:
    virtual ~AbstractImplementation() {}
};

#endif // ABSTRACTIMPLEMENTATION_HPP

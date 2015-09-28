// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef IIMPLEMENTATION_HPP
#define IIMPLEMENTATION_HPP

#include "../visitor/VisitorClient.hpp"

class IImplementation :
    public VisitorClient
{
  public:
    virtual ~IImplementation() {}
};

#endif

// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef ABSTRACTINSTANCE_HPP
#define ABSTRACTINSTANCE_HPP

#include <string>
#include "../base/Position.hpp"
#include "../visitor/VisitorClient.hpp"

class AbstractInstance : public VisitorClient, public RelativePosition
{
  public:
    AbstractInstance(const Point &offset) :
      RelativePosition(offset)
    {
    }

    virtual ~AbstractInstance()
    {
    }

    virtual const std::string &getName() const = 0;
};

#endif // ABSTRACTINSTANCE_HPP

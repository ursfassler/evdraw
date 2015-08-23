// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef NULLIMPLEMENTATION_HPP
#define NULLIMPLEMENTATION_HPP

#include "../component/AbstractImplementation.hpp"

class NullImplementation : public AbstractImplementation
{
  public:
    NullImplementation();

    void accept(Visitor &visitor);
    virtual void accept(ConstVisitor &visitor) const;
};

#endif // NULLIMPLEMENTATION_HPP

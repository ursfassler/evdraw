// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef NULLIMPLEMENTATION_HPP
#define NULLIMPLEMENTATION_HPP

#include "../component/IImplementation.hpp"

class NullImplementation final :
    public IImplementation
{
  public:
    NullImplementation();

    ImplementationType getType() const override final;

    void accept(Visitor &visitor) override final;
    virtual void accept(ConstVisitor &visitor) const override final;
};

#endif // NULLIMPLEMENTATION_HPP

// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef NULLCONSTVISITOR_HPP
#define NULLCONSTVISITOR_HPP

#include "ConstVisitor.hpp"

class NullConstVisitor : public ConstVisitor
{
  public:
    void visit(const Slot &port);
    void visit(const Signal &port);
    void visit(const Component &component);
    void visit(const Instance &instance);
    void visit(const InstancePort &port);
    void visit(const Connection &connection);
    void visit(const Composition &composition);
    void visit(const NullImplementation &nullImplementation) ;
    void visit(const Library &library);
};

#endif

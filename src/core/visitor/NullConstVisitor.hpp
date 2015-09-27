// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef NULLCONSTVISITOR_HPP
#define NULLCONSTVISITOR_HPP

#include "ConstVisitor.hpp"

class NullConstVisitor : public ConstVisitor
{
  public:
    void visit(const ComponentPort &port) override;
    void visit(const Component &component) override;
    void visit(const Instance &instance) override;
    void visit(const CompositionInstance &instance) override;
    void visit(const InstancePort &port) override;
    void visit(const Connection &connection) override;
    void visit(const Composition &composition) override;
    void visit(const NullImplementation &nullImplementation) override;
    void visit(const Library &library) override;
};

#endif

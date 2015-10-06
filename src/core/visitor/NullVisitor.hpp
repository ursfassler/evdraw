// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef NULLVISITOR_HPP
#define NULLVISITOR_HPP

#include "Visitor.hpp"

class NullVisitor : public Visitor
{
  public:
    void visit(ComponentPort &port) override;
    void visit(Component &component) override;
    void visit(Instance &instance) override;
    void visit(CompositionInstance &instance) override;
    void visit(InstancePort &port) override;
    void visit(Connection &connection) override;
    void visit(Composition &composition) override;
    void visit(NullImplementation &nullImplementation) override;
    void visit(Library &library) override;
};

#endif

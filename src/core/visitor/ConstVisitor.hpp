// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef CONSTVISITOR_HPP
#define CONSTVISITOR_HPP

#include "VisitedPrototypes.hpp"

class ConstVisitor
{
  public:
    virtual ~ConstVisitor() {}
    virtual void visit(const ComponentPort &port) = 0;
    virtual void visit(const Component &component) = 0;
    virtual void visit(const Instance &instance) = 0;
    virtual void visit(const CompositionInstance &instance) = 0;
    virtual void visit(const InstancePort &port) = 0;
    virtual void visit(const Connection &connection) = 0;
    virtual void visit(const Composition &composition) = 0;
    virtual void visit(const NullImplementation &nullImplementation) = 0;
    virtual void visit(const Library &library) = 0;
};

#endif

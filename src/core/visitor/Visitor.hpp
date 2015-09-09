// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef VISITOR_HPP
#define VISITOR_HPP

#include "VisitedPrototypes.hpp"

class Visitor
{
  public:
    virtual ~Visitor() {}
    virtual void visit(ComponentPort &port) = 0;
    virtual void visit(Component &component) = 0;
    virtual void visit(Instance &instance) = 0;
    virtual void visit(InstancePort &port) = 0;
    virtual void visit(Connection &connection) = 0;
    virtual void visit(Composition &composition) = 0;
    virtual void visit(NullImplementation &nullImplementation) = 0;
    virtual void visit(Library &library) = 0;
};

#endif // VISITOR_HPP

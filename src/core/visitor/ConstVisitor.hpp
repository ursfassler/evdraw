#ifndef CONSTVISITOR_HPP
#define CONSTVISITOR_HPP

#include "VisitedPrototypes.hpp"

class ConstVisitor
{
  public:
    virtual ~ConstVisitor() {}
    virtual void visit(const Slot &port) = 0;
    virtual void visit(const Signal &port) = 0;
    virtual void visit(const Component &component) = 0;
    virtual void visit(const Instance &instance) = 0;
    virtual void visit(const InstancePort &port) = 0;
    virtual void visit(const Connection &connection) = 0;
    virtual void visit(const Composition &composition) = 0;
    virtual void visit(const NullImplementation &nullImplementation) = 0;
    virtual void visit(const Library &library) = 0;
};

#endif

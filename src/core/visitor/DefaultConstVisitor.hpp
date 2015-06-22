#ifndef DEFAULTCONSTVISITOR_HPP
#define DEFAULTCONSTVISITOR_HPP

#include "ConstVisitor.hpp"

class DefaultConstVisitor : public ConstVisitor
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

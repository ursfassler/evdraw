#ifndef NULLVISITOR_HPP
#define NULLVISITOR_HPP

#include "Visitor.hpp"

class NullVisitor : public Visitor
{
  public:
    void visit(Slot &port);
    void visit(Signal &port);
    void visit(Component &component);
    void visit(Instance &instance);
    void visit(InstancePort &port);
    void visit(Connection &connection);
    void visit(Composition &composition);
    void visit(NullImplementation &nullImplementation) ;
    void visit(Library &library);
};

#endif

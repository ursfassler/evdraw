#ifndef DEFAULTVISITOR_HPP
#define DEFAULTVISITOR_HPP

#include "Visitor.hpp"

class DefaultVisitor : public Visitor
{
  public:
    void visit(Slot &port);
    void visit(Signal &port);
    void visit(InstancePort &port);
    void visit(Instance &instance);
    void visit(Connection &connection);
    void visit(Composition &composition);
    void visit(NullImplementation &nullImplementation);
    void visit(Component &component);
    void visit(Library &library);

};

#endif // DEFAULTVISITOR_HPP

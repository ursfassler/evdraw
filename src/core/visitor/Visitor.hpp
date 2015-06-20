#ifndef VISITOR_HPP
#define VISITOR_HPP

class Slot;
class Signal;
class Component;
class Instance;
class InstancePort;
class Connection;
class Composition;
class NullImplementation;
class Library;

class Visitor
{
  public:
    virtual ~Visitor() {}
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

class VisitorClient
{
  public:
    virtual ~VisitorClient() {}
    virtual void accept(Visitor &visitor) const = 0;
};

#endif // VISITOR_HPP

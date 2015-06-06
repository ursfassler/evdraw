#ifndef VISITOR_HPP
#define VISITOR_HPP

class ComponentPort;
class Component;
class Instance;
class InstancePort;
class Connection;
class Sheet;

class Visitor
{
  public:
    virtual ~Visitor() {}
    virtual void visit(const ComponentPort &port) = 0;
    virtual void visit(const Component &component) = 0;
    virtual void visit(const Instance &instance) = 0;
    virtual void visit(const InstancePort &port) = 0;
    virtual void visit(const Connection &connection) = 0;
    virtual void visit(const Sheet &sheet) = 0;
};

class VisitorClient
{
  public:
    virtual ~VisitorClient() {}
    virtual void accept(Visitor &visitor) const = 0;
};

#endif // VISITOR_HPP

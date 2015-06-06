#ifndef RIZZLYPRINT_HPP
#define RIZZLYPRINT_HPP

#include "../core/sheet/Sheet.hpp"
#include "../core/visitor/Visitor.hpp"

#include <ostream>

class RizzlyPrint final : private Visitor
{
  public:
    RizzlyPrint(std::ostream &stream);

    void print(const Sheet &sheet);

  private:
    void visit(const ComponentPort &port);
    void visit(const Component &component);
    void visit(const Instance &instance);
    void visit(const InstancePort &port);
    void visit(const Connection &connection);
    void visit(const Sheet &sheet);

  private:
    std::ostream &stream;
};

#endif // RIZZLYPRINT_HPP

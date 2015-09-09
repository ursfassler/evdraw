// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef RIZZLYPRINT_HPP
#define RIZZLYPRINT_HPP

#include "../core/implementation/Composition.hpp"
#include "../core/visitor/ConstVisitor.hpp"

#include <ostream>

class RizzlyPrint final : private ConstVisitor
{
  public:
    RizzlyPrint(std::ostream &stream);

    void print(const Composition &sheet);

  private:
    void visit(const ComponentPort &port);
    void visit(const Component &component);
    void visit(const Instance &instance);
    void visit(const InstancePort &port);
    void visit(const Connection &connection);
    void visit(const Composition &composition);
    void visit(const NullImplementation &nullImplementation);
    void visit(const Library &library);

  private:
    std::ostream &stream;
};

#endif // RIZZLYPRINT_HPP

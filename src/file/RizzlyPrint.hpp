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
    void visit(const ComponentPort &port) override final;
    void visit(const Component &component) override final;
    void visit(const Instance &instance) override final;
    void visit(const CompositionInstance &instance) override final;
    void visit(const InstancePort &port) override final;
    void visit(const Connection &connection) override final;
    void visit(const Composition &composition) override final;
    void visit(const NullImplementation &nullImplementation) override final;
    void visit(const Library &library) override final;

  private:
    std::ostream &stream;
};

#endif // RIZZLYPRINT_HPP

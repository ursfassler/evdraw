// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef CONSTVISITORMOCK_HPP
#define CONSTVISITORMOCK_HPP

#include <core/visitor/ConstVisitor.hpp>

#include <vector>
#include <string>

class ConstVisitorMock final : public ConstVisitor
{
  public:
    ConstVisitorMock();

    void visit(const ComponentPort &port) override;
    void visit(const Component &component) override;
    void visit(const Instance &instance) override;
    void visit(const CompositionInstance &instance) override;
    void visit(const InstancePort &port) override;
    void visit(const Connection &) override;
    void visit(const Composition &) override;
    void visit(const NullImplementation &) override;
    void visit(const Library &) override;

    std::vector<std::string> visited;
};

#endif // CONSTVISITORMOCK_HPP

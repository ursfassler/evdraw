// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef DEFAULTVISITORMOCK_H
#define DEFAULTVISITORMOCK_H

#include "unittest/testtypes.hpp"

#include <core/visitor/DefaultVisitor.hpp>

#include <core/component/Library.hpp>
#include <core/component/Component.hpp>
#include <core/component/ComponentPort.hpp>
#include <core/instance/Instance.hpp>
#include <core/instance/InstancePort.hpp>
#include <core/implementation/Composition.hpp>
#include <core/connection/Connection.hpp>

class DefaultVisitorMock :
    public DefaultVisitor
{
  public:
    DefaultVisitorMock();

    void visit(ComponentPort &port) override;
    void visit(InstancePort &port) override;
    void visit(Instance &instance) override;
    void visit(CompositionInstance &instance) override;
    void visit(Connection &connection) override;
    void visit(Composition &composition) override;
    void visit(NullImplementation &nullImplementation) override;
    void visit(Component &component) override;
    void visit(Library &library) override;

    test::sl visited;

    bool hasVisited(const std::string &value) const;
};

#endif // DEFAULTVISITORMOCK_H

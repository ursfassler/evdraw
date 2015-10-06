// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#ifndef VISITORMOCK_H
#define VISITORMOCK_H

#include "../../testtypes.hpp"

#include <core/visitor/Visitor.hpp>

#include <core/component/Component.hpp>
#include <core/component/Library.hpp>
#include <core/component/ComponentFactory.hpp>
#include <core/instance/Instance.hpp>
#include <core/instance/InstanceFactory.hpp>
#include <core/instance/InstancePort.hpp>
#include <core/connection/Connection.hpp>
#include <core/connection/DrawPort.hpp>
#include <core/connection/ConnectionFactory.hpp>
#include <core/implementation/Composition.hpp>
#include <core/implementation/CompositionFactory.hpp>
#include <core/implementation/NullImplementation.hpp>

class VisitorMock :
    public Visitor
{
  public:
    VisitorMock(const VisitorMock &) = delete;
    VisitorMock *operator =(const VisitorMock &) = delete;

    VisitorMock();
    ~VisitorMock();

    void visit(ComponentPort &port) override;
    void visit(Component &component) override;
    void visit(Instance &instance) override;
    void visit(CompositionInstance &) override;
    void visit(InstancePort &port) override;
    void visit(Connection &connection) override;
    void visit(Composition &composition) override;
    void visit(NullImplementation &) override;
    void visit(Library &library) override;

    test::sl visited;

  private:
    Component *component;
};

#endif // VISITORMOCK_H

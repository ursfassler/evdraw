// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "ConstVisitorMock.hpp"

#include <core/component/ComponentPort.hpp>
#include <core/component/Component.hpp>
#include <core/instance/Instance.hpp>
#include <core/instance/InstancePort.hpp>

ConstVisitorMock::ConstVisitorMock() :
  visited()
{
}

void ConstVisitorMock::visit(const ComponentPort &port)
{
  visited.push_back("ComponentPort: " + port.getName());
}

void ConstVisitorMock::visit(const Component &component)
{
  visited.push_back("Component: " + component.getName());
}

void ConstVisitorMock::visit(const Instance &instance)
{
  visited.push_back("Instance: " + instance.getName());
}

void ConstVisitorMock::visit(const CompositionInstance &)
{
  visited.push_back("CompositionInstance");
}

void ConstVisitorMock::visit(const InstancePort &port)
{
  visited.push_back("InstancePort: " + port.getName());
}

void ConstVisitorMock::visit(const Connection &)
{
  visited.push_back("Connection");
}

void ConstVisitorMock::visit(const Composition &)
{
  visited.push_back("Composition");
}

void ConstVisitorMock::visit(const NullImplementation &)
{
  visited.push_back("NullImplementation");
}

void ConstVisitorMock::visit(const Library &)
{
  visited.push_back("Library");
}

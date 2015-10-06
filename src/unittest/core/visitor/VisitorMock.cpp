// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "VisitorMock.h"


VisitorMock::VisitorMock()
{
}

void VisitorMock::visit(ComponentPort &port)
{
  visited.push_back("ComponentPort:" + port.getName());
}

void VisitorMock::visit(Component &component)
{
  visited.push_back("Component:" + component.getName());
}

void VisitorMock::visit(Instance &instance)
{
  visited.push_back("Instance:" + instance.getName());
}

void VisitorMock::visit(CompositionInstance &)
{
  visited.push_back("CompositionInstance");
}

void VisitorMock::visit(InstancePort &port)
{
  visited.push_back("InstancePort:" + port.getName());
}

void VisitorMock::visit(Connection &connection)
{
  visited.push_back("Connection:" + connection.getStartPort()->getName() + "->" + connection.getEndPort()->getName());
}

void VisitorMock::visit(Composition &)
{
  visited.push_back("Composition");
}

void VisitorMock::visit(NullImplementation &)
{
  visited.push_back("NullImplementation");
}

void VisitorMock::visit(Library &)
{
  visited.push_back("Library");
}

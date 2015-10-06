// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "DefaultVisitorMock.h"



DefaultVisitorMock::DefaultVisitorMock() :
  visited()
{
}

void DefaultVisitorMock::visit(ComponentPort &port)
{
  visited.push_back("ComponentPort:" + port.getName());
  DefaultVisitor::visit(port);
}

void DefaultVisitorMock::visit(InstancePort &port)
{
  visited.push_back("InstancePort:" + port.getName());
  DefaultVisitor::visit(port);
}

void DefaultVisitorMock::visit(Instance &instance)
{
  visited.push_back("Instance:" + instance.getName());
  DefaultVisitor::visit(instance);
}

void DefaultVisitorMock::visit(CompositionInstance &instance)
{
  visited.push_back("CompositionInstance");
  DefaultVisitor::visit(instance);
}

void DefaultVisitorMock::visit(Connection &connection)
{
  visited.push_back("Connection:" + connection.getStartPort()->getName() + "->" + connection.getEndPort()->getName());
  DefaultVisitor::visit(connection);
}

void DefaultVisitorMock::visit(Composition &composition)
{
  visited.push_back("Composition");
  DefaultVisitor::visit(composition);
}

void DefaultVisitorMock::visit(NullImplementation &nullImplementation)
{
  visited.push_back("NullImplementation");
  DefaultVisitor::visit(nullImplementation);
}

void DefaultVisitorMock::visit(Component &component)
{
  visited.push_back("Component:" + component.getName());
  DefaultVisitor::visit(component);
}

void DefaultVisitorMock::visit(Library &library)
{
  visited.push_back("Library");
  DefaultVisitor::visit(library);
}

bool DefaultVisitorMock::hasVisited(const std::__cxx11::string &value) const
{
  for (const std::string &itr : visited)
  {
    if (itr == value)
    {
      return true;
    }
  }
  return false;
}

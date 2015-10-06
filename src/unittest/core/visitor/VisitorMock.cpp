// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "VisitorMock.h"


//TODO simplify, like DefaultVisitorMock

VisitorMock::VisitorMock() :
  visited{},
  component(ComponentFactory::produce("Component"))
{
}

VisitorMock::~VisitorMock()
{
  ComponentFactory::dispose(component);
}

void VisitorMock::visit(ComponentPort &port)
{
  port.setTopIndex(2*port.getTopIndex());
}

void VisitorMock::visit(Component &component)
{
  component.addPort(new ComponentPort("", PortType::Slot));
}

void VisitorMock::visit(Instance &instance)
{
  instance.setOffset(Point(42,57));
}

void VisitorMock::visit(CompositionInstance &)
{
  visited.push_back("CompositionInstance");
}

void VisitorMock::visit(InstancePort &port)
{
  port.setOffset(Point(100,200));
}

void VisitorMock::visit(Connection &connection)
{
  IPort *start = connection.getStartPort();
  IPort *end = connection.getEndPort();
  connection.replaceStartPort(end);
  connection.replaceEndPort(start);
}

void VisitorMock::visit(Composition &composition)
{
  composition.addInstance(new Instance("", Point(0,0), component));
}

void VisitorMock::visit(NullImplementation &)
{
}

void VisitorMock::visit(Library &library)
{
  library.addComponent(ComponentFactory::produce(""));
}

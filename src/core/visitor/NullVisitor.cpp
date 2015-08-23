// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "NullVisitor.hpp"


void NullVisitor::visit(Slot &)
{
}

void NullVisitor::visit(Signal &)
{
}

void NullVisitor::visit(Component &)
{
}

void NullVisitor::visit(Instance &)
{
}

void NullVisitor::visit(InstancePort &)
{
}

void NullVisitor::visit(Connection &)
{
}

void NullVisitor::visit(Composition &)
{
}

void NullVisitor::visit(NullImplementation &)
{
}

void NullVisitor::visit(Library &)
{
}

// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "NullConstVisitor.hpp"


void NullConstVisitor::visit(const Slot &)
{
}

void NullConstVisitor::visit(const Signal &)
{
}

void NullConstVisitor::visit(const Component &)
{
}

void NullConstVisitor::visit(const Instance &)
{
}

void NullConstVisitor::visit(const InstancePort &)
{
}

void NullConstVisitor::visit(const Connection &)
{
}

void NullConstVisitor::visit(const Composition &)
{
}

void NullConstVisitor::visit(const NullImplementation &)
{
}

void NullConstVisitor::visit(const Library &)
{
}

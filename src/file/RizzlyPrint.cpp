// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "RizzlyPrint.hpp"

RizzlyPrint::RizzlyPrint(std::ostream &aStream) :
  stream(aStream)
{
}

void RizzlyPrint::print(const Composition &sheet)
{
  sheet.accept(*this);
}

void RizzlyPrint::visit(const ComponentPort &)
{
}

void RizzlyPrint::visit(const Component &)
{
}

void RizzlyPrint::visit(const Instance &instance)
{
  stream << instance.getName();
  stream << ": ";
  stream << instance.getComponent()->getName();
  stream << ";" << std::endl;
}

void RizzlyPrint::visit(const InstancePort &port)
{
  stream << port.getInstance()->getName();
  stream << ".";
  stream << port.getName();
}

void RizzlyPrint::visit(const Connection &connection)
{
  connection.getStartPort()->accept(*this);
  stream << " -> ";
  connection.getEndPort()->accept(*this);
  stream << ";" << std::endl;
}

void RizzlyPrint::visit(const Composition &composition)
{
  for (const Instance *inst : composition.getInstances()) {
    inst->accept(*this);
  }
  for (const Connection *con : composition.getConnections()) {
    con->accept(*this);
  }
}

void RizzlyPrint::visit(const Library &)
{
}


void RizzlyPrint::visit(const NullImplementation &)
{
}

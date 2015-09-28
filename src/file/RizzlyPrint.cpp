// Copyright 2015 Urs Fässler, www.bitzgi.ch
// SPDX-License-Identifier:	GPL-3.0+

#include "RizzlyPrint.hpp"

#include "../core/visitor/NullConstVisitor.hpp"

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

void RizzlyPrint::visit(const CompositionInstance &)
{
}

class InstancePrefixPrinter :
    public NullConstVisitor
{
  public:
    InstancePrefixPrinter(std::ostream &aStream) :
      stream(aStream)
    {
    }

    void visit(const Instance &instance) override
    {
      stream << instance.getName();
      stream << ".";
    }

    void visit(const CompositionInstance &) override
    {
    }

  private:
    std::ostream &stream;
};

void RizzlyPrint::visit(const InstancePort &port)
{
  InstancePrefixPrinter prefixer(stream);

  port.getInstance()->accept(prefixer);
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

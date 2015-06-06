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

void RizzlyPrint::visit(const Composition &sheet)
{
  for (const Instance *inst : sheet.getInstances()) {
    inst->accept(*this);
  }
  for (const Connection *con : sheet.getConnections()) {
    con->accept(*this);
  }
}

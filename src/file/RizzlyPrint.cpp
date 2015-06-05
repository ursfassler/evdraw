#include "RizzlyPrint.hpp"

RizzlyPrint::RizzlyPrint(std::ostream &aStream) :
  stream(aStream)
{
}

void RizzlyPrint::print(const Sheet &sheet)
{
  for (const Instance *inst : sheet.getInstances()) {
    print(inst);
  }
  for (const Connection *con : sheet.getConnections()) {
    print(con);
  }
}

void RizzlyPrint::print(const Instance *instance)
{
  stream << instance->getName() << ": " << instance->getComponent()->getName() << ";" << std::endl;
}

void RizzlyPrint::print(const Connection *connection)
{
  print(connection->getStartPort());
  stream << " -> ";
  print(connection->getEndPort());
  stream << ";" << std::endl;
}

void RizzlyPrint::print(const AbstractPort *port)
{
  const InstancePort *ip = dynamic_cast<const InstancePort*>(port);
  if (ip == nullptr) {
    return;
  }

  stream << ip->getInstance()->getName();
  stream << ".";
  stream << ip->getName();
}

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
//  stream << connection->getStartPort()->name()
  (void)(connection);
}

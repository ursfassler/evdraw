#include "RizzlyPrint.hpp"

RizzlyPrint::RizzlyPrint(std::ostream &aStream) :
  stream(aStream)
{
}

void RizzlyPrint::print(const Sheet &)
{
  stream << "";
}

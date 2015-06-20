#include "NullImplementation.hpp"

#include "../visitor/Visitor.hpp"

NullImplementation::NullImplementation()
{
}

void NullImplementation::accept(Visitor &visitor) const
{
  visitor.visit(*this);
}

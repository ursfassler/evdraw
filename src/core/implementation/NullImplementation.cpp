#include "NullImplementation.hpp"

#include "../visitor/ConstVisitor.hpp"

NullImplementation::NullImplementation()
{
}

void NullImplementation::accept(Visitor &visitor)
{
  visitor.visit(*this);
}

void NullImplementation::accept(ConstVisitor &visitor) const
{
  visitor.visit(*this);
}

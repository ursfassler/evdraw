#include "DefaultSpecification.hpp"

#include <core/specification/OrSpecification.hpp>

Specification *DefaultSpecification::or_(const Specification *right) const
{
  OrSpecification *spec = new OrSpecification();
  spec->add(this);
  spec->add(right);
  return spec;
}

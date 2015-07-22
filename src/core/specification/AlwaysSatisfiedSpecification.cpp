#include "AlwaysSatisfiedSpecification.hpp"

AlwaysSatisfiedSpecification::AlwaysSatisfiedSpecification()
{
}

bool AlwaysSatisfiedSpecification::isSatisfiedBy(const Base *) const
{
  return true;
}


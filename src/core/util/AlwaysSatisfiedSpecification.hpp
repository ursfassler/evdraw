#ifndef ALWAYSSATISFIEDSPECIFICATION_HPP
#define ALWAYSSATISFIEDSPECIFICATION_HPP

#include "Specification.hpp"

class AlwaysSatisfiedSpecification : public Specification
{
  public:
    AlwaysSatisfiedSpecification();

    bool isSatisfiedBy(const Base *) const;

};

#endif // ALWAYSSATISFIEDSPECIFICATION_HPP

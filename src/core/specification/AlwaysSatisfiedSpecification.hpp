#ifndef ALWAYSSATISFIEDSPECIFICATION_HPP
#define ALWAYSSATISFIEDSPECIFICATION_HPP

#include "DefaultSpecification.hpp"

class AlwaysSatisfiedSpecification : public DefaultSpecification
{
  public:
    AlwaysSatisfiedSpecification();

    bool isSatisfiedBy(const Base *) const;

};

#endif // ALWAYSSATISFIEDSPECIFICATION_HPP
